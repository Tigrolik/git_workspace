#include "PPM_Image.h"

void test_PPM_Image() {
    constexpr int w {800}, h {800};
    const std::string fn {"output.ppm"};
    PPM_Image I {w, h};
    I.set_color(w >> 1, h >> 1, Color_name::red);

    write_ppm_image(I, fn);
    PPM_Image J {"building.ppm"};
    J.write_to("test.ppm");
}

void test_BW_Image() {
    constexpr int w {400}, h {350};
    const std::string fn {"bw.ppm"};
    BW_Image I {w, h};
    I.write_to(fn);
}

int main() {

    //test_PPM_Image();
    test_BW_Image();

    return 0;
}
