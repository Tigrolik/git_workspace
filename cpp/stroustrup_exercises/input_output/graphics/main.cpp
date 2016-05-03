#include "std_lib_facilities.h"
#include "Point.h"
#include "fltk.h"
#include "Graph.h"
#include "GUI.h"
#include "Simple_window.h"

void test_point() {
    using namespace Graph_lib;

    Point p1 {3, 5};
    Point p2 {3, 5};
    cout << (p1 == p2) << endl;
}

void draw_things(Simple_window &win) {
    // Axis is a Shape
    // starting at Point{20, 300}
    // 280 pixels long, 10 "notches"
    Axis xa {Axis::x, Point{20, 300}, 280, 10, "x axis"};
    win.attach(xa);
    Axis ya {Axis::y, Point{20, 300}, 280, 10, "y_axis"};
    ya.set_color(Color::cyan);
    ya.label.set_color(Color::dark_red);
    win.attach(ya);
    Text t {Point{150, 150}, "Hello, the World of Graphics!"};
    t.set_font(Graph_lib::Font::times_bold);
    t.set_font_size(20);
    win.attach(t);
    Function sine {sin, 0, 100, Point {20,150}, 1000, 50, 50}; // sine
    // plot sin() in range [0: 100) with (0, 0) at (20, 150)
    // using 1000 points, scale x (and y) values * 50
    sine.set_color(Color::white);
    win.attach(sine);
    Polygon poly;
    poly.add(Point{300, 200});
    poly.add(Point{350, 100});
    poly.add(Point{400, 200});
    poly.set_color(Color::red);
    poly.set_style(Line_style(Line_style::dash, 4));
    win.attach(poly);
    Rectangle r {Point{200, 200}, 100, 50};
    r.set_fill_color(Color::yellow);
    win.attach(r);
    Closed_polyline poly_rect;
    poly_rect.add(Point{100, 50});
    poly_rect.add(Point{200, 50});
    poly_rect.add(Point{200, 100});
    poly_rect.add(Point{100, 100});
    poly_rect.add(Point{50, 75});
    poly_rect.set_style(Line_style(Line_style::dot, 2));
    poly_rect.set_fill_color(Color::green);
    win.attach(poly_rect);
    Image ii {Point{350, 150}, "img.jpg", Suffix::jpg};
    win.attach(ii);
    Circle c {Point{100, 200}, 50};
    win.attach(c);
    Ellipse e {Point{100, 200}, 75, 25};
    e.set_color(Color::dark_red);
    win.attach(e);
    Mark m {Point{100, 200}, 'x'};
    win.attach(m);
    ostringstream oss;
    oss << "screen size: " << x_max() << " * " << y_max() << "; window size: "
        << win.x_max() << " * " << win.y_max();
    Text sizes {Point{100, 20}, oss.str()};
    win.attach(sizes);
    Image cal {Point{225, 250}, "snow_cpp.gif", Suffix::gif};
    cal.set_mask(Point{40, 40}, 200, 150); // display center part of image
    win.attach(cal);

    win.set_label("Canvas #2");
    win.wait_for_button();
}

void exercises(Simple_window &win) {
    Rectangle r {Point{100, 100}, 73, 29};
    r.set_color(Color::red);
    Text t {Point{110, 120}, "Howdy!"};
    Polygon p_r;
    p_r.add(Point{200, 100});
    p_r.add(Point{280, 100});
    p_r.add(Point{280, 80});
    p_r.add(Point{200, 80});
    p_r.set_color(Color::blue);

    win.attach(r);
    win.attach(t);
    win.attach(p_r);

    Line in2a {Point{10, 200}, Point{10, 360}};
    in2a.set_color(Color::cyan);
    in2a.set_style(Line_style(Line_style::solid, 3));
    Line in2b {Point{10, 360}, Point{50, 200}};
    in2b.set_color(Color::cyan);
    in2b.set_style(Line_style(Line_style::solid, 3));
    Line in2c {Point{50, 200}, Point{50, 360}};
    in2c.set_color(Color::cyan);
    in2c.set_style(Line_style(Line_style::solid, 3));
    win.attach(in2a);
    win.attach(in2b);
    win.attach(in2c);

    Line in3a {Point{60, 200}, Point{60, 360}};
    in3a.set_color(Color::magenta);
    in3a.set_style(Line_style(Line_style::solid, 3));
    Line in3b {Point{60, 200}, Point{90, 270}};
    in3b.set_color(Color::magenta);
    in3b.set_style(Line_style(Line_style::solid, 3));
    Line in3b2 {Point{120, 200}, Point{90, 270}};
    in3b2.set_color(Color::magenta);
    in3b2.set_style(Line_style(Line_style::solid, 3));
    Line in3c {Point{120, 200}, Point{120, 360}};
    in3c.set_color(Color::magenta);
    in3c.set_style(Line_style(Line_style::solid, 3));
    win.attach(in3a);
    win.attach(in3b);
    win.attach(in3b2);
    win.attach(in3c);

    constexpr int b_x {300}, b_y {10}, b_w {90}, b_h {90};
    Rectangle board {Point{b_x, b_y}, b_w, b_h};
    Rectangle sq11 {Point{300, 10}, 30, 30};
    sq11.set_color(Color::white);
    sq11.set_fill_color(Color::white);
    Rectangle sq12 {Point{330, 10}, 30, 30};
    sq12.set_color(Color::red);
    sq12.set_fill_color(Color::red);
    Rectangle sq13 {Point{360, 10}, 30, 30};
    sq13.set_color(Color::white);
    sq13.set_fill_color(Color::white);
    Rectangle sq21 {Point{300, 40}, 30, 30};
    sq21.set_color(Color::red);
    sq21.set_fill_color(Color::red);
    Rectangle sq22 {Point{330, 40}, 30, 30};
    sq22.set_color(Color::white);
    sq22.set_fill_color(Color::white);
    Rectangle sq23 {Point{360, 40}, 30, 30};
    sq23.set_color(Color::red);
    sq23.set_fill_color(Color::red);
    Rectangle sq31 {Point{300, 70}, 30, 30};
    sq31.set_color(Color::white);
    sq31.set_fill_color(Color::white);
    Rectangle sq32 {Point{330, 70}, 30, 30};
    sq32.set_color(Color::red);
    sq32.set_fill_color(Color::red);
    Rectangle sq33 {Point{360, 70}, 30, 30};
    sq33.set_color(Color::white);
    sq33.set_fill_color(Color::white);

    win.attach(sq11); win.attach(sq12); win.attach(sq13);
    win.attach(sq21); win.attach(sq22); win.attach(sq23);
    win.attach(sq31); win.attach(sq32); win.attach(sq33);
    win.attach(board);

    Rectangle big {Point{10, 10}, x_max() / 3 * 2, y_max() / 4 * 3};
    win.attach(big);

    win.set_label("Exercises");
    win.wait_for_button();
}

void create_poly(Simple_window &win, Polygon &p, const double a, const int n) {
    static const int x_c {win.x_max() / 2}, y_c {win.y_max() / 2};
    static constexpr double pi {std::acos(-1)};
    const double ang_step {pi * 2.0 / n};
    //const double angle {(n & 1) ? pi * 0.5 : -ang_step * 0.5};
    const double angle {pi * 0.5};
    const double R {a / (2 * sin(pi / n))};
    //const double R {a};
    for (int i = 0; i < n; ++i) {
        const double ang_temp {angle + i * ang_step};
        p.add(Point{static_cast<int>(x_c + R * cos(ang_temp)),
                static_cast<int>(y_c - R * sin(ang_temp))});
    }
}

void add_polygon(Simple_window &win, Polygon &p, const double a,
        const int y_p, const int n, const Color c) {
    static const int x_c {win.x_max() / 2};// y_c {win.y_max() / 2};
    static constexpr double pi {std::acos(-1)}, angle {pi * 0.5};
    //const double ang_step {pi * 2.0 / n};
    const double ang_step {pi * 2.0 / n};
    const double R {a / (2 * sin(pi / n))};
    const double y_c {win.y_max() / 2.0 - a / sqrt(3) + y_p * 0};
    //const int yy {y_p + static_cast<int>(R)};
    for (int i = 0; i < n; ++i) {
        const double ang_temp {angle + i * ang_step};
        p.add(Point{static_cast<int>(x_c + R * cos(ang_temp)),
                static_cast<int>(y_c - R * sin(ang_temp))});
    }
    p.set_color(c);
    win.attach(p);
}

constexpr double get_inner_angle(const int num_sides) {
    return (num_sides - 2.0) / num_sides * acos(-1);
}

constexpr double get_side_length(const double a, const double angle_alpha,
        const double angle_beta) {
    return a * (sin(acos(-1) - angle_beta - (angle_beta - angle_alpha) * 0.5)
        / sin(angle_beta));
}

void draw_polygons2(Simple_window &win) {
    const int y_c {win.y_max() / 2};
    constexpr double a {100.0};
    const int yy {y_c - static_cast<int>(a / sqrt(3))};
    double ang1 {get_inner_angle(3)};
    Polygon p_triangle;
    add_polygon(win, p_triangle, a, yy, 3, Color::green);

//    double pi {std::acos(-1)};// deg_to_rad {pi / 180};
    int num_sides {4};
    double ang2 {get_inner_angle(num_sides)};
    Polygon p_square;
    add_polygon(win, p_square, get_side_length(a, ang1, ang2), yy, num_sides,
                Color::yellow);

    ang1 = ang2; ang2 = get_inner_angle(++num_sides);
    Polygon p_pentagon;
    add_polygon(win, p_pentagon, get_side_length(a, ang1, ang2), yy, num_sides,
            Color::red);

    ang1 = ang2; ang2 = get_inner_angle(++num_sides);
    Polygon p_hexagon;
    add_polygon(win, p_hexagon, get_side_length(a, ang1, ang2), yy, num_sides,
            Color::blue);

    win.wait_for_button();
}

void draw_polygons(Simple_window &win) {
    const int x_c {win.x_max() / 2}, y_c {win.y_max() / 2}, a {50};
    const int x_l {x_c - a}, x_r {x_c + a}, y_b {y_c + a}, y_t {y_c - a};
    Closed_polyline triangle;
    triangle.add(Point{x_l, y_b});
    triangle.add(Point{x_r, y_b});
    triangle.add(Point{x_c, y_t});
    triangle.set_color(Color::green);

    //Closed_polyline square;
    Polygon square;
    //square.add(Point{x_l, y_b});
    //square.add(Point{x_r, y_b});
    //square.add(Point{x_r, y_t});
    //square.add(Point{x_l, y_t});

    create_poly(win, square, a * sqrt(2), 4);
    square.set_color(Color::yellow);

    Polygon pentagon;
    //create_poly(win, pentagon, 5, 5);
    const double pi {std::acos(-1)}, deg_to_rad {pi / 180};
    const double ang_a {72 * deg_to_rad}, ang_b {108 * deg_to_rad};
    //const double ang_b {108 * deg_to_rad};
    const double ang_g {36 * deg_to_rad}, ang_e {18 * deg_to_rad};
    const double aux1 {sin(ang_b)}, aux2 {sin(ang_g)};
    const double aux3 {sin(ang_a)}, aux4 {cos(ang_a)};
    // pentagon's side
    double d {(a << 1) * (aux2 / aux1 + sin(ang_e) / aux1)};
    //const double d {a * 2 * (sin(ang_g) / sin(ang_b) + sin(ang_e) / sin(ang_b))};
    //create_poly(win, pentagon, d, 5);

    int x {x_c}, y {y_c - a - static_cast<int>(a * tan(ang_g))};
    pentagon.add(Point{x, y});
    x += static_cast<int>(d * cos(ang_g));
    y += static_cast<int>(d * aux2);
    pentagon.add(Point{x, y});
    x -= static_cast<int>(d * aux4);
    y += static_cast<int>(d * aux3);
    pentagon.add(Point{x, y});
    x -= static_cast<int>(d);
    pentagon.add(Point{x, y});
    x -= static_cast<int>(d * aux4);
    y -= static_cast<int>(d * aux3);
    pentagon.add(Point{x, y});
    pentagon.set_color(Color::red);

    Polygon p2;
    //create_poly(win, p2, a + (a * tan(ang_g)), 5);
    //const double R {a / (2 * sin(pi / n))};
    d = a * (1 + tan(ang_g));
    create_poly(win, p2, d / (2 * sin(pi / 5)), 5);
    p2.set_color(Color::blue);

    Polygon hexagon;
    create_poly(win, hexagon, d, 6);
    hexagon.set_color(Color::magenta);

    win.attach(triangle);
    win.attach(square);
    win.attach(pentagon);
    win.attach(hexagon);
    win.attach(p2);

    win.wait_for_button();
}

void draw_superellipse(Simple_window &win, const double a, const double b,
        const double m, const double n, const int num) {

    const double pi {acos(-1)};
    const int x_c {win.x_max() / 2}, y_c {win.y_max() / 2}, scale {100};
    Closed_polyline p;
    for (int i = 0; i < num; ++i) {
        const double arg {static_cast<double>(i) / num * (pi * 2.0)};
        const double t1 {cos(arg)};
        const double t2 {sin(arg)};
        const int x {static_cast<int>(((t1 < 0) ? (-a * pow(-t1, 2.0 / m)) :
                (a * pow(t1, 2.0 / m))) * scale)};
        const int y {static_cast<int>(((t2 < 0) ? (-b * pow(-t2, 2.0 / n)) :
                (b * pow(t2, 2.0 / n))) * scale)};
        p.add(Point{x_c + x, y_c + y});
    }
    p.set_color(Color::blue);
    p.set_style(Line_style(Line_style::solid, 3));
    p.set_fill_color(Color::yellow);

    win.attach(p);
    win.wait_for_button();
}

void draw_Gielis_superellipse(Simple_window &win, const double a,
        const double b, const double m, const double n1, const double n2,
        const double n3, const int num) {

    const double pi {acos(-1)}, m_{m * 0.25};
    const int x_c {win.x_max() / 2}, y_c {win.y_max() / 2}, scale {50};
    Closed_polyline p;
    for (int i = 0; i < num; ++i) {
        const double arg0 {static_cast<double>(i) / num * pi * 2.0};
        const double arg {arg0 * m_};
        const double t1 {cos(arg)};
        const double t2 {sin(arg)};
        const double r {pow(pow(abs(t1/a), n2) + pow(abs(t2/b), n3), -1.0/n1)};
        p.add(Point{x_c + static_cast<int>(r * cos(arg0) * scale), y_c +
                static_cast<int>(r * sin(arg0) * scale)});
    }
    p.set_color(Color::blue);
    p.set_style(Line_style(Line_style::solid, 3));
    p.set_fill_color(Color::yellow);

    win.attach(p);
    win.wait_for_button();
}

void test_win() {
    using namespace Graph_lib;

    Point tl {100, 100};
    Simple_window win {tl, 600, 400, "Canvas"};
    //Rectangle r {tl, 1200, 1200};
    //win.attach(r);
    //win.wait_for_button();
    //draw_things(win);
    //exercises(win);
    //draw_polygons(win);
    draw_polygons2(win);
    //draw_superellipse(win, 3, 2, 2.0 / 3, 2.0 / 3, 10); // squashed astroid
    //draw_superellipse(win, 3, 2, 1, 1, 10); // squashed diamond
    //draw_superellipse(win, 3, 2, 2, 2, 50); // ellipse
    //draw_superellipse(win, 3, 2, 2.5, 2.5, 50); // Piet Hein's "superellipse"
    //draw_superellipse(win, 3, 2, 4, 4, 50); // rectellipse
    //draw_superellipse(win, 3, 2, 0.5, 0.5, 50);
    //draw_Gielis_superellipse(win, 1, 1, 5, 2, 9, 9, 10); // star
    //draw_Gielis_superellipse(win, 0.9, 0.9, 4, 10, 19, 19, 10);
    //draw_Gielis_superellipse(win, 1, 1, 6, 100, 100, 100, 50); // snowflake
    //Polygon p;
    //create_poly(win, p, 50, 5);
    //p.set_color(Color::red);
    //win.attach(p);
    //win.wait_for_button();

}

int main() {

    //test_point();
    test_win();

    return 0;
}
