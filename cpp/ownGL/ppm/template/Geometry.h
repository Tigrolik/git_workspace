#ifndef _GEOMETRY_H_
#define _GEOMETRY_H_

#include <algorithm>
#include "PPM_Image.h"

constexpr int sqr_fun(const int val) {
    return val * val;
}

class Shape {
public:
    virtual double length() const = 0; // length, perimeter...
    virtual double area() const = 0;
    virtual void draw(PPM_Image&, const PPM_Color&) const = 0;
};

class Point: public Shape {
public:
    Point();
    Point(const int, const int);
    Point(const Point&);
    Point &operator=(const Point&);

    ~Point() = default;

    int x() const { return x_; }
    int y() const { return y_; }

    double length() const override { return 0.0; }
    double area() const override { return 0.0; }
    void draw(PPM_Image&, const PPM_Color& = PPM_Color{255}) const override;
private:
    int x_;
    int y_;
};

class Line: public Shape {
public:
    Line(const Point&, const Point&);
    Line(const int, const int, const int, const int);
    Line(const Line&);
    Line &operator=(const Line&);

    ~Line() = default;

    double length() const override { return sqrt(sqr_fun(p1_.x() - p2_.x()) +
            sqr_fun(p1_.y() - p2_.y())); }
    double area() const override { return 0.0; }
    void draw(PPM_Image&, const PPM_Color& = PPM_Color{255}) const override;

private:
    Point p1_;
    Point p2_;
};

#endif

