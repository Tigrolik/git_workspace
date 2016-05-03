#include <png.h>
#include <cstdio>
#include <string>
#include <iostream>

using namespace std;

png_byte *loadImage(const string filename, int &width, int &height)
{
    // header for testing if file is .png
    png_byte header[8];

    // open file as binary
    FILE *fp = fopen(filename.c_str(), "rb");
    if (!fp)
        return nullptr;

    // read the header
    fread(header, 1, 8, fp);

    // test if png
    int is_png = !png_sig_cmp(header, 0, 8);
    if (!is_png) {
        fclose(fp);
        return nullptr;
    }

    // create png struct
    png_structp png_ptr = png_create_read_struct(PNG_LIBPNG_VER_STRING,
            nullptr, nullptr, nullptr);

    if (!png_ptr) {
        fclose(fp);
        return nullptr;
    }

    // create png info struct
    png_infop info_ptr = png_create_info_struct(png_ptr);
    if (!info_ptr) {
        png_destroy_read_struct(&png_ptr, (png_infopp)nullptr,
                (png_infopp)nullptr);
        fclose(fp);
        return nullptr;
    }

    // create png info struct
    png_infop end_info = png_create_info_struct(png_ptr);
    if (!end_info) {
        png_destroy_read_struct(&png_ptr, &info_ptr, (png_infopp)nullptr);
        fclose(fp);
        return nullptr;
    }

    // png error stuff, not sure libpng man suggests this
    if (setjmp(png_jmpbuf(png_ptr))) {
        png_destroy_read_struct(&png_ptr, &info_ptr, &end_info);
        fclose(fp);
        return nullptr;
    }

    // init png reading
    png_init_io(png_ptr, fp);

    // let libpng know you already read the first 8 bytes
    png_set_sig_bytes(png_ptr, 8);

    // read all the info up to the image data
    png_read_info(png_ptr, info_ptr);

    // variables to pass to get info
    int bit_depth, color_type;
    png_uint_32 twidth, theight;

    // get info about png
    png_get_IHDR(png_ptr, info_ptr, &twidth, &theight, &bit_depth, &color_type,
            nullptr, nullptr, nullptr);

    // update width and height based on png info
    width = twidth;
    height = theight;

    // update the png info struct
    png_read_update_info(png_ptr, info_ptr);

    // row size in bytes
    int rowbytes = png_get_rowbytes(png_ptr, info_ptr);

    // allocate the image_data as a big block, to be given to opengl
    png_byte *image_data = new png_byte[rowbytes * height];

    if (!image_data) {
        // clean up memory and close stuff
        png_destroy_read_struct(&png_ptr, &info_ptr, &end_info);
        fclose(fp);
        return nullptr;
    }

    // row_pointers is for pointing to image_data for reading png with libpng
    png_bytep *row_pointers = new png_bytep[height];
    if (!row_pointers) {
        // clean up memory and close stuff
        png_destroy_read_struct(&png_ptr, &info_ptr, &end_info);
        delete [] image_data;
        fclose(fp);
        return nullptr;
    }

    // set the indivdual row_pointers to point at correct offsets of image_data
    for (int i = 0; i < height; ++i)
        row_pointers[height - 1 - i] = image_data + i * rowbytes;

    // read the png into image_data through row_pointers
    png_read_image(png_ptr, row_pointers);

    // check the remainder of the image for correctness
    png_read_end(png_ptr, nullptr);

    // clean up memory and close stuff
    png_destroy_read_struct(&png_ptr, &info_ptr, &end_info);
    fclose(fp);

    return image_data;
}

int main()
{
    int img_w = 0, img_h = 0;
    png_byte *img = loadImage("building.png", img_w, img_h);
    png_byte I[img_w * img_h] = img;
    // unsigned int array[img_w][img_h] = reinterpret_cast<unsigned int *>(img);
    cout << img_h << endl;

    return 0;
}
