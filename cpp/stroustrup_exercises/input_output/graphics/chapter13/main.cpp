#include "std_lib_facilities.h"
#include "Point.h"
#include "fltk.h"
#include "Graph.h"
#include "GUI.h"
#include "Simple_window.h"
#include "exercises.h"

using namespace Graph_lib;

void test_grid(Simple_window &win) {
    static const int x_size {win.x_max()}, y_size {win.y_max()};
    constexpr int x_grid {80}, y_grid {40};
    Lines grid;
    for (int x {x_grid}; x < x_size; x += x_grid)
        grid.add(Point{x, 0}, Point{x, y_size});
    for (int y {y_grid}; y < y_size; y += y_grid)
        grid.add(Point{0, y}, Point{x_size, y});
    grid.set_color(Color::yellow);
    grid.set_style(Line_style{Line_style::dash, 2});

    win.attach(grid);
    win.wait_for_button();
}

void test_rects(Simple_window &win) {
    Rectangle r00 {Point{150, 100}, 200, 100};
    Rectangle r11 {Point{50, 50}, Point{250, 150}};
    Rectangle r12 {Point{50, 150}, Point{250, 250}};
    Rectangle r21 {Point{250, 50}, 200, 100};
    Rectangle r22 {Point{250, 150}, 200, 100};
    r00.set_color(Color::invisible);
    r11.set_color(Color::invisible);
    r12.set_color(Color::invisible);
    r21.set_color(Color::invisible);
    //r22.set_color(Color::invisible);

    r00.set_fill_color(Color::yellow);
    r11.set_fill_color(Color::blue);
    r12.set_fill_color(Color::red);
    r21.set_fill_color(Color::green);
    r11.move(400, 0);
    r11.set_fill_color(Color::white);

    win.attach(r00);
    win.attach(r11);
    win.attach(r12);
    win.attach(r21);
    win.attach(r22);
    win.put_on_top(r00);
    win.wait_for_button();
}

void show_palette(Simple_window &win) {
    Vector_ref<Rectangle> vr;
    for (int i {0}; i < 16; ++i)
        for (int j {0}; j < 16; ++j) {
            vr.push_back(new Rectangle{Point{i * 20, j * 20}, 20, 20});
            vr[vr.size() - 1].set_fill_color(Color{i * 16 + j});
            win.attach(vr[vr.size() - 1]);
        }
    win.wait_for_button();
}

void drill(Simple_window &win) {
    static const int x_size {win.x_max()}, y_size {win.y_max()};
    constexpr int num_x {8}, num_y {8};
    const int x_grid {x_size / num_x}, y_grid {y_size / num_y};
    Lines grid;
    for (int x {x_grid}; x < x_size; x += x_grid)
        grid.add(Point{x, 0}, Point{x, y_size});
    for (int y {y_grid}; y < y_size; y += y_grid)
        grid.add(Point{0, y}, Point{x_size, y});
    Vector_ref<Rectangle> vr;
    for (int i {0}; i < num_x; ++i) {
        vr.push_back(new Rectangle{Point{x_grid * i, y_grid * i},
                x_grid, y_grid});
        vr[vr.size() - 1].set_fill_color(Color::red);
        win.attach(vr[vr.size() - 1]);
    }
    grid.set_color(Color::yellow);
    grid.set_style(Line_style{Line_style::dash, 2});
    win.attach(grid);

    Image img1 {Point{x_grid * 2, 0}, "../snow_cpp.gif", Suffix::gif};
    img1.set_mask(Point{0, 0}, 200, 200);
    Image img2 {Point{0, y_grid * 4}, "../snow_cpp.gif", Suffix::gif};
    img2.set_mask(Point{0, 0}, 200, 200);
    Image img3 {Point{x_grid * 3, y_grid * 6}, "../snow_cpp.gif", Suffix::gif};
    img3.set_mask(Point{0, 0}, 200, 200);

    win.attach(img1);
    win.attach(img2);
    win.attach(img3);

    for (int i {0}; i < num_x; ++i) {
        for (int j {0}; j < num_y; ++j) {
            Image img4 {Point{x_grid * i, y_grid * j}, "img.jpg", Suffix::jpg};
            img4.set_mask(Point{0, 0}, 100, 100);
            win.attach(img4);
            win.wait_for_button();
        }
    }

    win.wait_for_button();
}

void exercises(Simple_window &win) {
    Arc a1 {Point{200, 100}, 100, 50, 45, 210};
    Ellipse c1 {Point{200, 100}, 100, 50};
    a1.set_color(Color::green);

    const Point p1 {500, 10}, p2 {300, 700};
    Arrow arr1 {p1, p2, 30, 11}; Arrow arr2 {p2, p1};
    arr1.set_color(Color::blue);
    const Point p3 {400, 100}, p4 {600, 200};
    Arrow arr3 {p3, p4}; Arrow arr4 {p4, p3, 30, 90};
    const Point p5 {200, 500}, p6 {600, 500};
    Arrow arr5 {p5, p6, 15, 17}; Arrow arr6 {p6, p5};
    const Point p7 {700, 200}, p8 {700, 400};
    Arrow arr7 {p7, p8}; Arrow arr8 {p8, p7, 50, 198};
    arr7.set_color(Color::red);

    Box b1 {Point{200, 100}, 100, 50, 0, 0};
    b1.set_color(Color::red);
    win.attach(b1);
    Box b2 {Point{50, 400}, 200, 150, 80, 30};
    b2.set_color(Color::red);
    win.attach(b2);

    Rectangle r {Point{50, 200}, 50, 80};
    win.attach(r);
    Point pnw {nw(r)}; Mark m1 {pnw, '0'}; win.attach(m1);
    Point pn {n(r)}; Mark m11 {pn, '1'}; win.attach(m11);
    Point pne {ne(r)}; Mark m2 {pne, '2'}; win.attach(m2);
    Point ps {s(r)}; Mark m21 {ps, '3'}; win.attach(m21);
    Point psw {sw(r)}; Mark m3 {psw, '4'}; win.attach(m3);
    Point pw {w(r)}; Mark m31 {pw, '5'}; win.attach(m31);
    Point pse {se(r)}; Mark m4 {pse, '6'}; win.attach(m4);
    Point pe {e(r)}; Mark m41 {pe, '7'}; win.attach(m41);
    Point pc {center(r)}; Mark m5 {pc, '9'}; win.attach(m5);

    constexpr int x0 {70}, y0 {300}, rad {50};
    Vector_ref<Regular_polygon> v;
    for (int i {0}; i < 8; ++i) {
        v.push_back(new Regular_polygon{Point{x0 + i * (rad + rad / 2),
                y0 + static_cast<int>(0.5 * rad * pow(-1, i % 2))}, 6, rad});
        v[v.size() - 1].set_color(Color::blue);
        v[v.size() - 1].set_fill_color(Color::blue);
        win.attach(v[v.size() - 1]);
    }
    Regular_polygon rp1 {Point{150, 600}, 6, 50};
    rp1.set_color(Color::cyan);
    rp1.set_fill_color(Color::magenta);
    win.attach(rp1);
    Regular_polygon rp2 {Point{450, 600}, 9, 70};
    rp2.set_color(Color::yellow);
    rp2.set_fill_color(Color::blue);
    win.attach(rp2);

    win.attach(c1);
    win.attach(a1);
    win.attach(arr1); win.attach(arr2); win.attach(arr3); win.attach(arr4);
    win.attach(arr5); win.attach(arr6); win.attach(arr7); win.attach(arr8);
    win.wait_for_button();
}

void draw_rgb_chart(Simple_window &win) {
    constexpr int num {16}, sq_size {20};
    Vector_ref<Rectangle> v;
    for (int i {0}; i < num; ++i)
        for (int j {0}; j < num; ++j) {
            v.push_back(new Rectangle{Point{i * sq_size, j * sq_size},
                    sq_size, sq_size});
            v[v.size() - 1].set_color(Color::invisible);
            v[v.size() - 1].set_fill_color(Color{i * num + j});
            win.attach(v[v.size() - 1]);
        }
    win.wait_for_button();
}

int main() {

    Simple_window win {Point{100,100}, 800, 800, "Canvas"};
    //test_grid(win);
    //test_rects(win);
    //show_palette(win);
    //drill(win);
    draw_rgb_chart(win);
    //exercises(win);

    return 0;
}
