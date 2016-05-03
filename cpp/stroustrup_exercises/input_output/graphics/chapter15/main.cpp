#include "../std_lib_facilities.h"
#include "../Point.h"
#include "../fltk.h"
#include "../Graph.h"
#include "../GUI.h"
#include "../Simple_window.h"

using namespace Graph_lib;

constexpr double one(const double) { return 1; }
constexpr double slope(const double x) { return x * 0.5; }
constexpr double square(const double x) { return x * x; }
constexpr double sloping_cos(const double x) { return cos(x) + slope(x); }
constexpr long long fac(const int n) {
    return (n > 1) ? n * fac(n - 1) : 1;
}
constexpr double term(const double x, const int n) {
    return pow(x, n) / fac(n);
}
constexpr double exp_approx(const double x, const int n) {
    return (n > 1) ? term(x, n) + exp_approx(x, n - 1) : x * n;
}
static int exp_approx_idx {0};
double expe(const double x) {
    return exp_approx(x, exp_approx_idx);
}
//double exp_approx(const double x, const int n) {
//    double s {0.0};
//    for (int i {0}; i < n; ++i)
//        s += term(x, i);
//    return s;
//}

void drills() {
    constexpr int xmax {600}, ymax {400}, xorig {xmax >> 1}, yorig {ymax >> 1};
    const Point orig {xorig, yorig};
    constexpr int rmin {-10}, rmax {11}, npoints {400}, xscale{30}, yscale{30};

    Simple_window win {Point{100,100}, xmax, ymax, "Functions"};

    Function s1 {one, rmin, rmax, orig, npoints, xscale, yscale};
    Text ts1 {Point{100, yorig - 40}, "one"};
    win.attach(s1); win.attach(ts1);

    Function s2 {slope, rmin, rmax, orig, npoints, xscale, yscale};
    Text ts2 {Point{100, yorig + (yorig >> 1)- 20}, "x/2"};
    win.attach(s2); win.attach(ts2);

    Function s3 {square, rmin, rmax, orig, npoints, xscale, yscale};
    Text ts3 {Point{xorig - 100, 20}, "x^2"};
    win.attach(s3); win.attach(ts3);

    Function s4 {cos, rmin, rmax, orig, npoints, xscale, yscale};
    s4.set_color(Color::blue);
    win.attach(s4);

    Function s5 {sloping_cos, rmin, rmax, orig, npoints, xscale, yscale};
    win.attach(s5);

    Function f1 {log, 0.0000001, rmax, orig, 200, xscale, yscale};
    f1.set_color(Color::yellow);
    win.attach(f1);

    Function f2 {sin, rmin, rmax, orig, 200, xscale, yscale};
    f2.set_color(Color::green);
    win.attach(f2);

    Function f3 {exp, rmin, rmax, orig, 200, xscale, yscale};
    f3.set_color(Color::white);
    win.attach(f3);

    constexpr int xlen {xmax - 40}, ylen {ymax - 40};
    Axis x {Axis::x, Point{20, yorig}, xlen, xlen / xscale, "x"};
    Axis y {Axis::y, Point{xorig, ylen + 20}, ylen, ylen / yscale, "y"};
    x.label.move(-160, 0);
    x.notches.set_color(Color::dark_red);
    win.attach(x); win.attach(y);

    win.wait_for_button();
}

void draw_approx_exp() {
    constexpr int xmax {600}, ymax {400}, xorig {xmax >> 1}, yorig {ymax >> 1};
    const Point orig {xorig, yorig};
    constexpr int rmin {-10}, rmax {11}, npoints {400}, xscale{30}, yscale{30};
    Simple_window win {Point{100,100}, xmax, ymax, "Functions"};

    Function real_exp {exp, rmin, rmax, orig, 200, xscale, yscale};
    real_exp.set_color(Color::green);
    win.attach(real_exp);

    for (int i {0}; i < 50; ++i) {
        win.set_label("exp approximation; i == " + to_string(i));
        exp_approx_idx = i;
        Function e {expe, rmin, rmax, orig, npoints, xscale, yscale};
        win.attach(e);
        win.wait_for_button();
        win.detach(e);
    }
    win.wait_for_button();
}

void exercises() {
    Simple_window win {Point{100,100}, 800, 800, "Canvas"};
    win.wait_for_button();
}

int main() {

    //drills();
    draw_approx_exp();
    //exercises();

    return 0;
}
