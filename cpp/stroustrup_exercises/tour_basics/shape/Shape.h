#ifndef _SHAPE_H_
#define _SHAPE_H_

class Shape {
    public:
        // delete = eliminate default definitions
        Shape (const Shape&) = delete;
        Shape& operator=(const Shape&) = delete;
        Shape (Shape&&) = delete;
        Shape& operator=(Shape&&) = delete;

        virtual Point center() const = 0; // pure virtual
        virtual void move(Point to) = 0;

        virtual void draw() const = 0;
        virtual void rotate(int angle) = 0;

        virtual ~Shape() {}
};

class Circle: public Shape {
    public:
        Circle(Point p, int rr);

        Point center() const { return x; }
        void move(Point to) { x = to; }

        void draw() const;
        void rotate(int) {}
    private:
        Point x; // center
        int r; // radius
};

class Smiley: public Circle {
    public:
        Smiley(Point p, int r): Circle{p, r}, mouth{nullptr} { }

        ~Smiley() {
            delete mouth;
            for (auto p : eyes)
                delete p;
        }

        void move(Point to);

        void draw() const {
            Circle::draw();
            for (auto p : eyes)
                p->draw();
            mouth->draw();
        }

        void rotate(int);

        void add_eye(Shape *s) { eyes.push_back(s); }
        void set_mouth(Shape *s);
        virtual void wink(int i);

    private:
        vector<Shape *> eyes;
        Shape* mouth;
};

#endif
