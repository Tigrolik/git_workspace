#include "Geometry.h"

// ------- POINT -------
Point::Point(): x_{0}, y_{0} { }

Point::Point(const int xx, const int yy): x_{xx}, y_{yy} {
}

Point::Point(const Point &o): x_{o.x()}, y_{o.y()} {
}

Point &Point::operator=(const Point &o) {
    if (this != &o) {
        x_ = o.x();
        y_ = o.y();
    }
    return *this;
}

void Point::draw(PPM_Image &img, const PPM_Color &c) const {
    img.pixel_color(x_, y_, c);
}

// ------- LINE -------
Line::Line(const Point &p1, const Point &p2): p1_{p1}, p2_{p2} {
}

Line::Line(const int x1, const int y1, const int x2, const int y2):
    p1_{Point{x1, y1}}, p2_{Point{x2, y2}} {
    }

Line::Line(const Line &o): p1_{o.p1_}, p2_{o.p2_} {
}

Line &Line::operator=(const Line &o) {
    if (this != &o) {
        p1_ = o.p1_;
        p2_ = o.p2_;
    }
    return *this;
}

void Line::draw(PPM_Image &img, const PPM_Color &c) const {
    int x1 {p1_.x()}, y1 {p1_.y()}, x2 {p2_.x()}, y2 {p2_.y()};
    int dx {std::abs(x1- x2)}, dy {std::abs(y1 - y2)};
    const bool steep {dy > dx};
    if (steep) {
        std::swap(x1, y1);
        std::swap(x2, y2);
        std::swap(dx, dy);
    }
    if (x1 > x2) {
        std::swap(x1, x2);
        std::swap(y1, y2);
    }
    const int incdy {dy << 1}, incdx {dx << 1}, ystep {y1 < y2 ? 1 : -1};
    int e {dx};
    for (int x {x1}; x <= x2; ++x) {
        steep ? img.pixel_color(y1, x, c) : img.pixel_color(x, y1, c);
        if ((e -= incdy) < 0) {
            y1 += ystep;
            e += incdx;
        }
    }
}
