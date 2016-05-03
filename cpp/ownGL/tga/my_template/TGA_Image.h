#ifndef _TGA_IMAGE_H_
#define _TGA_IMAGE_H_

#include <iostream>
//#include <vector>

struct TGA_Header {
    char  idlength;
    char  colormaptype;
    char  datatypecode;
    short colormaporigin;
    short colormaplength;
    char  colormapdepth;
    short x_origin;
    short y_origin;
    short width;
    short height;
    char  bitsperpixel;
    char  imagedescriptor;
};

enum class TGA_Format {
    GRAYSCALE = 1, RGB = 3, RGBA = 4
};

class TGA_Color {
    public:
        TGA_Color();
        TGA_Color(const unsigned char, const unsigned char,
                const unsigned char, const unsigned char);
        TGA_Color(const unsigned int, const int);
        TGA_Color(const TGA_Color&);
        TGA_Color(const unsigned char*, const int);
        TGA_Color &operator=(const TGA_Color&);

        unsigned int value() const { return val_; }
        int bytespp() const { return bytespp_; }
        union {
            //std::vector<unsigned char> rgba_(4);
            //struct {
            //    unsigned char b_, g_, r_, a_;
            //};
            unsigned char raw_[4];
            unsigned int val_;
        };
        int bytespp_;
};

class TGA_Image {
    public:
        TGA_Image();
        TGA_Image(int, int, int);
        TGA_Image(int, int, TGA_Format);
        TGA_Image(const TGA_Image&);
        TGA_Image &operator=(const TGA_Image&);

        ~TGA_Image();

        int width() const { return width_; }
        int height() const { return height_; }
        int bytespp() const { return bytespp_; }
        unsigned char *buffer() const { return data_; }

        bool read_tga_image(const std::string&);
        bool write_tga_image(const std::string&, bool = true);

        bool flip_horizontally();
        bool flip_vertically();
        bool scale(int, int);

        TGA_Color get_color(int, int);
        bool set_color(int, int, const TGA_Color&);

        void clear();

    protected:
        bool load_rle_data(std::ifstream&);
        bool unload_rle_data(std::ofstream&);

        unsigned char *data_;
        int width_;
        int height_;
        int bytespp_;
};

#endif

