#include "TGA_Image.h"
#include <cstring>
#include <fstream>
#include <stdexcept>

TGA_Color::TGA_Color(): val_{0}, bytespp_{1} { }

TGA_Color::TGA_Color(const unsigned char r, const unsigned char g,
        const unsigned char b, const unsigned char a):
    bytespp_{4} {
        raw_[0] = b, raw_[1] = g, raw_[2] = r, raw_[3] = a;
    //b_{b}, g_{g}, r_{r}, a_{a}, bytespp_{4} {
    }

TGA_Color::TGA_Color(const unsigned int v, const int bpp): val_{v},
    bytespp_{bpp} {
    }

TGA_Color::TGA_Color(const TGA_Color &other):
    val_{other.value()}, bytespp_{other.bytespp()} {
    }

TGA_Color::TGA_Color(const unsigned char *p, const int bpp):
    val_{0}, bytespp_{bpp} {
        for (int i {0}; i < bpp; ++i)
            raw_[i] = p[i];
    }

TGA_Color &TGA_Color::operator=(const TGA_Color &other) {
    if (this != &other) {
        val_ = other.value();
        bytespp_ = other.bytespp();
    }
    return *this;
}
//unsigned char *data_;
//int width_;
//int height_;
//int bytespp_;
//TGA_Image();
//TGA_Image(int, int, int);
//TGA_Image(const TGA_Image&);
//TGA_Image &operator=(const TGA_Image&);
//~TGA_Image();


TGA_Image::TGA_Image(): data_{nullptr}, width_{0}, height_{0}, bytespp_{0} {
}

TGA_Image::TGA_Image(int w, int h, int bpp): data_{nullptr}, width_{w},
    height_{h}, bytespp_{bpp} {
        unsigned long nbytes = width_ * height_ * bytespp_;
        data_ = new unsigned char[nbytes];
        memset(data_, 0, nbytes);
    }

TGA_Image::TGA_Image(int w, int h, TGA_Format f): data_{}, width_{w},
    height_{h}, bytespp_{0} {
        bytespp_ = static_cast<int>(f);
        unsigned long nbytes = width_ * height_ * bytespp_;
        data_ = new unsigned char[nbytes];
        memset(data_, 0, nbytes);
    }

TGA_Image::TGA_Image(const TGA_Image &img): data_{}, width_ {img.width()},
    height_ {img.height()}, bytespp_ {img.bytespp()} {
        const unsigned long nbytes = width_ * height_ * bytespp_;
        data_ = new unsigned char[nbytes];
        memcpy(data_, img.data_, nbytes);
    }

TGA_Image &TGA_Image::operator=(const TGA_Image &img) {
    if (this != &img) {
        if (data_)
            delete [] data_;
        width_ = img.width();
        height_ = img.height();
        bytespp_ = img.bytespp();
        const unsigned long nbytes = width_ * height_ * bytespp_;
        data_ = new unsigned char[nbytes];
        memcpy(data_, img.data_, nbytes);
    }
    return *this;
}

TGA_Image::~TGA_Image() {
    if (data_)
        delete [] data_;
}

bool TGA_Image::write_tga_image(const std::string &fn, bool rle) {
    std::ofstream ofs {fn, std::ios::binary};
    if (!ofs) {
        throw std::runtime_error("cannot open file " + fn);
        return false;
    }
    ofs.exceptions(ofs.exceptions() | std::ios_base::badbit);

    TGA_Header header;
    memset((void*)&header, 0, sizeof(header));
    header.bitsperpixel = bytespp_ << 3;
    header.width = width_;
    header.height = height_;
    header.datatypecode = (bytespp_ == static_cast<int>(TGA_Format::GRAYSCALE)
            ? (rle ? 11 : 3) : (rle ? 10 : 2));
    header.imagedescriptor = 0x20; // top-left origin
    ofs.write((char*)&header, sizeof(header));
    if (!ofs.good()) {
        std::cerr << "Cannot dump the tga image\n";
        return false;
    }
    if (!rle) {
        ofs.write((char*)data_, width_ * height_ * bytespp_);
        if (!ofs.good()) {
            std::cerr << "Cannot unload raw data\n";
            return false;
        }
    } else if (!unload_rle_data(ofs)) {
        std::cerr << "Cannot unload rle data\n";
        return false;
    }
    return false;

    // writing footer info
    unsigned char dev_area_ref[4] {0, 0, 0, 0};
    ofs.write((char*)dev_area_ref, sizeof(dev_area_ref));
    if (!ofs.good()) {
        std::cerr << "Cannot dump the tga image\n";
        return false;
    }
    unsigned char ext_area_ref[4] {0, 0, 0, 0};
    ofs.write((char*)ext_area_ref, sizeof(ext_area_ref));
    if (!ofs.good()) {
        std::cerr << "Cannot dump the tga image\n";
        return false;
    }
    unsigned char footer[18] {'T', 'R', 'U', 'E', 'V', 'I', 'S', 'I',
        'O', 'N', '-',   'X', 'F', 'I', 'L', 'E', '.', '\0'};
    ofs.write((char*)footer, sizeof(footer));
    if (!ofs.good()) {
        std::cerr << "Cannot dump the tga image\n";
        return false;
    }
    return true;
}

bool TGA_Image::unload_rle_data(std::ofstream &ofs) {
    const unsigned char max_chunk_len {128};
    unsigned long npix = width_ * height_, curpix {0};
    while (curpix < npix) {
        unsigned long chunkstart {curpix * bytespp_};
        unsigned long curbyte {curpix * bytespp_};
        unsigned char run_len {1};
        bool raw {true};
        while ((curpix + run_len < npix) && (run_len < max_chunk_len)) {
            bool succ_eq {true};
            for (int t {0}; succ_eq && t < bytespp_; ++t)
                succ_eq = (data_[curbyte + t] == data_[curbyte + t + bytespp_]);
            curbyte += bytespp_;
            if (run_len == 1)
                raw = !succ_eq;
            if (raw && succ_eq) {
                --run_len;
                break;
            }
            if (!raw && !succ_eq)
                break;
            ++run_len;
        }
        curpix += run_len;
        ofs.put(raw ? run_len - 1 : run_len + 127);
        if (!ofs.good()) {
            std::cerr << "Cannot dump the tga image\n";
            return false;
        }
        ofs.write((char*)(data_+chunkstart), (raw?run_len*bytespp_:bytespp_));
        if (!ofs.good()) {
            std::cerr << "Cannot dump the tga image\n";
            return false;
        }
    }
    return true;
}

TGA_Color TGA_Image::get_color(int x, int y) {
    if (!data_ || x < 0 || y < 0 || x >= width_ || y >= height_)
        return TGA_Color();
    return TGA_Color(data_ + (x + y * width_) * bytespp_, bytespp_);
}

bool TGA_Image::set_color(int x, int y, const TGA_Color &c) {
    if (!data_ || x < 0 || y < 0 || x >= width_ || y >= height_)
        return false;
    memcpy(data_ + (x + y * width_) * bytespp_, c.raw_, bytespp_);
    return true;
}

bool TGA_Image::flip_horizontally() {
    if (!data_)
        return false;
    int half {width_ >> 1};
    for (int i {0}; i < half; ++i) {
        for (int j {0}; j < height_; ++j) {
            TGA_Color c1 {get_color(i, j)};
            TGA_Color c2 {get_color(width_ - 1 - i, j)};
            set_color(i, j, c2);
            set_color(width_ - 1 - i, j, c1);
        }
    }
    return true;
}

bool TGA_Image::flip_vertically() {
    if (!data_)
        return false;
    unsigned long bytes_per_line = width_ * bytespp_;
    unsigned char *line = new unsigned char[bytes_per_line];
    int half {height_ >> 1};
    for (int j {0}; j < half; ++j) {
        unsigned long l1 = j * bytes_per_line;
        unsigned long l2 = (height_ - 1 - j) * bytes_per_line;
        memmove((void*)line, (void*)(data_ + l1), bytes_per_line);
        memmove((void*)(data_ + l1), (void*)(data_ + l2), bytes_per_line);
        memmove((void*)(data_ + l2), (void*)line, bytes_per_line);
    }
    delete [] line;
    return true;
}

