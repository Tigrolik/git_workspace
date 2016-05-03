#include<iostream>
#include<cmath>

using namespace std;

class Point
{
    private:
        int x;
        int y;

    public:
        Point(int = 0, int = 0);
        Point(const Point &other);
        Point &operator = (const Point &other);

        int getX() const;
        int getY() const;

        void setX(const int);
        void setY(const int);

        void print();
};

class PointArray
{
    private:
        int size;
        Point *points;

    protected:
        void resize(int);

    public:
        PointArray();
        PointArray(const Point [], const int);
        PointArray(const PointArray&); // copy ctor

        void push_back(const Point&);
        void insert(const int, const Point&);
        void remove(const int);
        const int getSize() const;
        void clear();
        Point *get(const int);
        const Point *get(const int) const;

        void print() const;
        ~PointArray();
};

class Polygon
{
    protected:
        static int numPolygons;
        PointArray points;

    public:
        Polygon(const Point [], const int);
        Polygon(const PointArray&);

        virtual double area() const = 0;

        static int getNumPolygons();
        const int getNumSides();
        const PointArray *getPoints() const;
        void print() const;

        ~Polygon();

};

class Rectangle: public Polygon
{
    public:
        Rectangle(const Point&, const Point&);
        Rectangle(const int, const int, const int, const int);

        virtual double area() const;
};

class Triangle: public Polygon
{
    public:
        Triangle(const Point&, const Point&, const Point&);

        virtual double area() const;
};
