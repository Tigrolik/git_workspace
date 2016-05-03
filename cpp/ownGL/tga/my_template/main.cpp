#include <iostream>
#include <fstream>
#include <stdexcept>
#include <vector>
#include <cstring>
#include "TGA_Image.h"

using namespace std;
using uchar_t = unsigned char;

const TGA_Color red {TGA_Color(255, 0, 0, 255)};
//void read_tga_image(const string &fn) {
//    ifstream ifs {fn};
//    if (!ifs)
//        throw runtime_error("cannot open file " + fn);
//    ifs.exceptions(ifs.exceptions() | ios_base::badbit);
//    TGA_Header header;
//    ifs.read((char *)&header, sizeof(header));
//    cout << header.width << endl;
//}

void write_ppm_image(const string &fn) {
    try {
        ofstream ofs {fn, ios_base::binary};
        ofs.exceptions(ofs.exceptions() | ios_base::badbit);
        const int w {120}, h {80}, nbytes {w * h * 3};
        vector<uchar_t> v (nbytes, 200);
        ofs << "P6\n" << w << ' ' << h << "\n255\n"; // header
        for (int i {0}; i < nbytes; i += 3) {
            ofs << v[i] << v[i + 1] << v[i + 2];
            //const unsigned char c {static_cast<unsigned char>(100)};
            //ofs << c << c << c;
        }
    } catch (exception &e) {
        cerr << "error: " << e.what() << endl;
    } catch (...) {
        cerr << "error: unknown exception\n";
    }
}

int main() {

    write_ppm_image("test.ppm");
    //const string fn {"zbuffer.tga"};
    //read_tga_image(fn);
    //TGA_Image img (100, 100, TGA_Format::RGB);
    //TGA_Image img (100, 100, 3);
    //img.set_color(52, 41, red);
    //img.flip_vertically();
    //img.write_tga_image("output.tga");

    return 0;
}

