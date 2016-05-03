#ifndef _VECTOR_H_
#define _VECTOR_H_

#include <iostream>
#include <algorithm> // std::copy

class Vector {
    /*
     * invariant:
     * if 0 <= n < sz, elem[n] is element n
     * sz <= space
     * if sz < space there is space for (space - sz) doubles after elem[sz - 1]
     */
public:
    // ctors
    Vector(): sz {0}, elem {nullptr}, space {0} {
    }
    explicit Vector(int s): sz {s}, elem {new double[s]}, space {sz} {
        for (int i {0}; i < s; ++i)
            elem[i] = 0;
    }
    // ctor with initializer_list
    Vector(std::initializer_list<double> lst):
        sz (lst.size()), elem {new double[sz]}, space{sz} {
            std::copy(begin(lst), end(lst), elem);
        }
    // copy ctor
    Vector(const Vector&);
    // move ctor
    Vector(Vector&&v);
    // assignment ctor (copy assignment)
    Vector &operator=(const Vector&);
    // move assignment
    Vector &operator=(Vector&&v);

    ~Vector() {
        delete [] elem;
    }

    int size() const { return sz; }
    int capacity() const { return space; }

    double &operator[](int n) { return elem[n]; }
    double operator[](int n) const { return elem[n]; }

    void reserve(int);
    void resize(int);
    void push_back(double);

    friend std::ostream &operator<<(std::ostream &os, const Vector &v) {
        for (int i {0}; i < v.size(); ++i)
            std::cout << v[i] << ' ';
        return os;
    }

    double get(int n) const { return elem[n]; }
    void set(int n, double v) { elem[n] = v; }

private:
    int sz;
    double *elem;
    int space;
};

Vector::Vector(const Vector &v): sz {v.size()}, elem {new double[sz]},
    space {sz} {
        std::copy(v.elem, v.elem + sz, elem);
    }

// move ctor: copy v's size and elements, then make an empty vector
Vector::Vector(Vector &&v): sz {v.size()}, elem {v.elem}, space {sz} {
    std::cout << "move ctor called\n";
    v.sz = 0;
    v.elem = nullptr;
}

Vector &Vector::operator=(const Vector &v) {
    if (this != &v) {
        if (v.sz <= space) { // enough space, no need for new allocation
            sz = v.sz;
            for (int i {0}; i < sz; ++i)
                elem[i] = v.elem[i];
        } else {
            sz = space = v.size();
            double *p = new double[sz]; // allocate new space
            for (int i {0}; i < sz; ++i)
                p[i] = v.elem[i];
            //std::copy(v.elem, v.elem + sz, p);
            delete [] elem; // deallocate old space
            elem = p;
        }
    }
    return *this;
}

Vector &Vector::operator=(Vector &&v) {
    std::cout << "move assignment called\n";
    delete [] elem; // deallocate old space
    sz = space = v.size();
    elem = v.elem; // copy v's size and elements
    v.sz = 0; // make en empty vector
    v.elem = nullptr;
    return *this;
}

void Vector::reserve(int newalloc) {
    if (newalloc <= space) // never decrease allocation
        return;
    double *p {new double[newalloc]}; // allocate new space
    for (int i {0}; i < sz; ++i) // copy old elements
        p[i] = elem[i];
    delete [] elem; // deallocate old space
    elem = p;
    space = newalloc;
}

void Vector::resize(int newsize) {
    reserve(newsize);
    for (int i {sz}; i < newsize; ++i)
        elem[i] = 0;
    sz = newsize;
}

void Vector::push_back(double d) {
    if (space == 0)
        reserve(8); // start with space for 8 elements
    else if (sz == space)
        reserve(space << 1); // get more space (double it)
    elem[sz] = d; // add d at the end
    ++sz; // one element has been added
}

#endif

