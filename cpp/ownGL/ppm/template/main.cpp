#include "PPM_Image.h"
#include "Geometry.h"
#include <iostream>
#include <iterator>
#include <thread>
#include <chrono>

using namespace std;

void draw_square(PPM_Image &img, const int x, const int y,
        const PPM_Color &c = PPM_Color{255}) {
    const int s {min(img.width() >> 1, img.height() >> 1) >> 2};
    for (int i {-s}; i < s; ++i)
        for (int j {-s}; j < s; ++j)
            img.pixel_color(x + i, y + j, c);
}

void test_color() {
    //PPM_Color clr{127};
    //PPM_Color clr{34, 139, 34};
    const PPM_Color c{"228b22"};
    const PPM_Color c1 {c};
    PPM_Color clr;
    clr = c1;
    cout << "hex value: " << hex << clr.color() << dec << ", red: " <<
       +clr.red() << ", green: " << +clr.green() << ", blue: " <<
       +clr.blue() << endl;
    //PPM_Color clr {"faebd7"};
    //PPM_Image img {200, 100, clr};

    //PPM_Image img {200, 100, PPM_Color{"0xffe4c4"}};
    //PPM_Image img {200, 100, Color_name::darkviolet};

    //write_ppm_image(img, "output.ppm");
}

void test_image() {
    constexpr int w {250}, h {150};
    //const PPM_Color clr{"228b22"};
    //const PPM_Color clr{127};
    //const PPM_Color clr{Color_name::red};
    //PPM_Image img {w, h, clr};
    PPM_Image img {w, h, Color_name::khaki};
    draw_square(img, w >> 1, h >> 1, PPM_Color{"FFFF00"});
    img.pixel_color(w >> 1, h >> 1, PPM_Color{"FFFF00"});
    PPM_Image I {img};
    I.pixel_color(25, 25);
    draw_square(I, 25, 25);
    PPM_Image J;
    J = I;
    draw_square(J, 100, 100, Color_name::red);
    J.pixel_color(100, 100, Color_name::white);

    write_ppm_image(J, "output.ppm");
}

void test_points() {
    constexpr int w {250}, h {150};
    PPM_Image img {w, h, Color_name::blue};
    const Point p1 {w >> 1, h >> 1};
    p1.draw(img);
    cout << "p1 length: " << p1.length() << ", area: " << p1.area() << endl;
    Point p2 {p1};
    p2 = Point{25, 50};
    p2.draw(img, Color_name::red);
    Point p3 = Point{100, 10};
    p3.draw(img, PPM_Color{101, 240, 201});

    write_ppm_image(img, "output.ppm");
}

void test_lines() {
    constexpr int w {300}, h {200};
    PPM_Image img {w, h, Color_name::blue};
    const Line l1 {Point{10, 10}, Point{20, 20}};
    Line l2 {l1};
    Line l3 {w >> 1, h >> 1, 200, 125};
    PPM_Color clr {img.get_color(w >> 1, h >> 1)};
    cout << "hex value: " << hex << clr.color() << dec << ", red: " <<
       +clr.red() << ", green: " << +clr.green() << ", blue: " <<
       +clr.blue() << endl;
    const Point p1 {200, 10}, p2 {10, 100};
    Line l4 = Line{p1, p2};

    //using namespace std::chrono;
    //auto t = high_resolution_clock::now();
    //for (int i {0}; i < 100000; ++i) {
    //    l1.draw(img, PPM_Color{127});
    //    l2.draw(img, PPM_Color{127});
    //    l3.draw(img);
    //    l4.draw(img, Color_name::red);
    //}
    //cout << duration<double>(high_resolution_clock::now() - t).count() << endl;

    l1.draw(img, PPM_Color{127});
    l2.draw(img, PPM_Color{127});
    l3.draw(img);
    l4.draw(img, Color_name::red);
    cout << "l4 length: " << l4.length() << ", area: " << l4.area() << endl;

    write_ppm_image(img, "output.ppm");
}

void test_cases() {
    //test_color();
    //test_image();
    //test_points();
    test_lines();
}

int main() {

    test_cases();

    return 0;
}

