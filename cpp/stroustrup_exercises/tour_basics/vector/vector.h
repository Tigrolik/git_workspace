#ifndef _VECTOR_H_
#define _VECTOR_H_

#include <initializer_list>

class Vector {
    private:
        double *elem;
        std::size_t sz;
    public:
        Vector(std::size_t s);
        Vector(std::initializer_list<double>);
        Vector(const Vector&);
        Vector(Vector&&); // move constructor
        Vector &operator=(const Vector&);

        ~Vector();

        double &operator[](std::size_t i);
        std::size_t size();
};

#endif
