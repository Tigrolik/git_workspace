#include "geometry.h"

// Point functions impementation
Point::Point(int a, int b): x(a), y(b) { }

Point::Point(const Point &other) {
    if (this != &other) {
        x = other.getX();
        y = other.getY();
    }
}

Point &Point::operator = (const Point &other) {
    if (this == &other)
        return *this;
    x = other.getX();
    y = other.getY();
    return *this;
}

int Point::getX() const {
    return x;
}

int Point::getY() const {
    return y;
}

void Point::setX(const int a) {
    x = a;
}

void Point::setY(const int b) {
    y = b;
}

void Point::print() {
    cout << "(" << x << ", " << y << ")" << endl;
}

// PointArray functions impementation
PointArray::PointArray(): size(0), points(new Point[0]) { }

PointArray::PointArray(const Point pts[], const int n) {
    size = n;
    points = new Point[n];
    for (int i = 0; i < n; ++i)
        points[i] = pts[i];
}

PointArray::PointArray(const PointArray &pv) {
    size = pv.getSize();
    // could use size = pv.size since code in PointArray class has access to
    // private variables
    points = new Point[size];
    for (int i = 0; i < size; ++i)
        points[i] = pv.points[i];
}

void PointArray::resize(int n) {
    Point *parr = new Point[n];
    int newsize = (n > size ? size : n);
    for (int i = 0; i < newsize; ++i)
        parr[i] = points[i];
    delete [] points;
    size = n;
    points = parr;
}

void PointArray::push_back(const Point &p) {
    resize(size + 1);
    points[size - 1] = p;
}

void PointArray::insert(const int pos, const Point &p) {
    if (pos >= 0 && pos < size) {
        resize(size + 1);
        for (int i = size - 1; i > pos; --i)
            points[i] = points[i - 1];
        points[pos] = p;
    }
}

void PointArray::remove(const int pos) {
    if (pos >= 0 && pos < size) {
        for (int i = pos; i < size - 2; ++i)
            points[i] = points[i + 1];
        resize(size - 1);
    }
}

void PointArray::clear() {
    resize(0);
}

Point *PointArray::get(const int pos) {
    return pos >= 0 && pos < size ? points + pos: NULL;
}

const Point *PointArray::get(const int pos) const {
    return pos >= 0 && pos < size ? points + pos: NULL;
}

const int PointArray::getSize() const {
    return size;
}

void PointArray::print() const {
    cout << "Array of size " << size << " and elements:" << endl;
    for (int i = 0; i < size; ++i)
        points[i].print();
}

PointArray::~PointArray() {
    cout << "PointArray destructor invoked\n";
    delete [] points;
}

// Polygon functions impementation
int Polygon::numPolygons = 0;

Polygon::Polygon(const Point pa[], const int nPoints): points(pa, nPoints) {
    ++numPolygons;
}

Polygon::Polygon(const PointArray &pa): points(pa) {
    ++numPolygons;
}

int Polygon::getNumPolygons() {
    return numPolygons;
}

const int Polygon::getNumSides() {
    return points.getSize();
}

const PointArray *Polygon::getPoints() const {
    return &points;
}

void Polygon::print() const {
    cout << "Area of the polygon: " << area() << " and points:" << endl;
    points.print();
}

Polygon::~Polygon() {
    --numPolygons;
}

Point constructorPoints[4];

Point *updateConstructorPoints(const Point &p1, const Point &p2,
        const Point &p3, const Point &p4 = Point(0,0)) {
    constructorPoints[0] = p1;
    constructorPoints[1] = p2;
    constructorPoints[2] = p3;
    constructorPoints[3] = p4;
    return constructorPoints;
}

const int square(int x) {
    return x * x;
}

const double point_dist(const Point &p1, const Point &p2) {
    return sqrt(square(p1.getX() - p2.getX()) + square(p1.getY() - p2.getY()));
}

// Rectangle functions impementation
Rectangle::Rectangle(const Point &p1, const Point &p2):
    Polygon(updateConstructorPoints(p1, Point(p1.getX(), p2.getY()),
               p2, Point(p2.getX(), p1.getY())), 4) { }

Rectangle::Rectangle(const int x1, const int y1, const int x2, const int y2):
Polygon(updateConstructorPoints(Point(x1, y1), Point(x1, y2), Point(x2, y2),
            Point(x2, y1)), 4) { }

double Rectangle::area() const {
    int length = points.get(1)->getY() - points.get(0)->getY();
    int width = points.get(2)->getX() - points.get(1)->getX();

    return abs((double) length * width);
}

// Triangle functions impementation
Triangle::Triangle(const Point &p1, const Point &p2, const Point &p3):
    Polygon(updateConstructorPoints(p1, p2, p3), 3) { }

double Triangle::area() const {
    Point p1 = *points.get(0), p2 = *points.get(1), p3 = *points.get(2);

    double a = point_dist(p1, p2), b = point_dist(p2, p3),
           c = point_dist(p3, p1);

    double s = 0.5 * (a + b + c);
    return sqrt(s * (s - a) * (s - b) * (s - c));
}

