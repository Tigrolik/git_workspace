#include "../std_lib_facilities.h"
#include "../Point.h"
#include "../fltk.h"
#include "../Graph.h"
#include "../GUI.h"
#include "../Simple_window.h"

using namespace Graph_lib;

class B1 {
public:
    virtual void pvf() = 0;
    virtual void vf() const { cout << "B1::vf()\n"; }
    void f() { cout << "B1::f()\n"; }
};

class D1: public B1 {
public:
    void pvf() { cout << "D1::pvf()\n"; }
    void vf() const override { cout << "D1::vf()\n"; }
    void f() { cout << "D1::f()\n"; }
};

class D2: public D1 {
public:
    void pvf() override { cout << "D2::pvf()\n"; }
};

class B2 {
public:
    virtual void pvf() const = 0;
};

class D21: public B2 {
public:
    D21(const string &s): s_{s} { }
    void pvf() const override { cout << s_ << endl; }
private:
    string s_;
};

class D22: public B2 {
public:
    D22(const int i): i_{i} { }
    void pvf() const override { cout << i_ << endl; }
private:
    int i_;
};

void f(const B2& b) {
    b.pvf();
}

struct Smiley: public Circle {
public:
    Smiley(Point p, int rr): Circle(p, rr), r {rr} { }
    void draw_lines() const {
        Circle::draw_lines();
        if (color().visibility()) {
            fl_color(color().as_int());
            fl_arc(point(0).x + (r >> 2),point(0).y + (r >> 1),
                    r >> 1,r >> 1,0,360);
            fl_arc(point(0).x + r + (r >> 2),point(0).y + (r >> 1),
                    r >> 1,r >> 1,0,360);
            fl_arc(point(0).x+r-(r >> 2),point(0).y + r,r >> 1,r >> 1,180,360);
        }

    }
private:
    int r;
};

class Smiley_hat: public Smiley {
    using Smiley::Smiley;
    void draw_lines() const {
        Smiley::draw_lines();
        const int rr {radius()};
        if (color().visibility()) {
            fl_line(point(0).x, point(0).y + (rr >> 2), point(0).x + (rr << 1),
                    point(0).y + (rr >> 2));
            fl_line(point(0).x + (rr << 1), point(0).y + (rr >> 2),
                    point(0).x + rr, point(0).y - (rr >> 3));
            fl_line(point(0).x + rr, point(0).y - (rr >> 3),
                    point(0).x, point(0).y + (rr >> 2));
        }
    }
};

struct Frowney: public Circle {
public:
    Frowney(Point p, int rr): Circle(p, rr), r {rr} { }
    void draw_lines() const {
        Circle::draw_lines();
        if (color().visibility()) {
            fl_color(color().as_int());
            fl_arc(point(0).x + (r >> 2),point(0).y + (r >> 1),
                    r >> 1,r >> 1,0,360);
            fl_arc(point(0).x + r + (r >> 2),point(0).y + (r >> 1),
                    r >> 1,r >> 1,0,360);
            fl_arc(point(0).x+r-(r >> 2),point(0).y + r,r >> 1,r >> 1,0,180);
        }

    }
private:
    int r;
};

void drills() {
    //B1 b1;
    //b1.vf(); b1.f();

    D1 d1;
    d1.vf(); d1.f();
    D2 d2;
    d2.vf(); d2.f(); d2.pvf();

    //B1& b_ref = d1;
    //b_ref.vf(); b_ref.f();

    D21 d21 {"Sample string"};
    D22 d22 {37};
    f(d21);
    f(d22);
}

void exercises() {
    Simple_window win {Point{100,100}, 800, 800, "Canvas"};
    Smiley_hat s1 {Point{200, 200}, 100};
    s1.set_color(Color::green);
    win.attach(s1);

    Frowney f1 {Point{400, 200}, 50};
    win.attach(f1);

    win.wait_for_button();
}

int main() {

    //drills();
    exercises();

    return 0;
}
