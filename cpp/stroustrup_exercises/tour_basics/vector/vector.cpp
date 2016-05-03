#include "vector.h"
#include <iostream>
#include <stdexcept>
#include <exception>

Vector::Vector(std::size_t s): elem{new double[s]}, sz{s} {
//    if (s < 0)
//        throw std::length_error(0);
    elem = new double[s];
    sz = s;
}

Vector::Vector(std::initializer_list<double> lst): elem{new double[lst.size()]},
    sz{lst.size()}
{
    std::copy(lst.begin(), lst.end(), elem);
}

Vector::Vector(const Vector& other): elem{new double[sz]}, sz{other.sz} {
    sz = other.sz;
    elem = new double[sz];
    for (std::size_t i = 0; i < sz; ++i)
        elem[i] = other.elem[i];
}

// && means rvalue ref: ref to which we can bind an rvalue
Vector::Vector(Vector&& a): elem{a.elem}, sz{a.sz} { // move constructor
    a.elem = nullptr;
    a.sz = 0;
}

Vector& Vector::operator=(const Vector& other) {
    sz = other.sz;
    double *p = new double[sz];
    for (std::size_t i = 0; i < sz; ++i)
        p[i] = other.elem[i];
    delete [] elem; // delete old elements
    elem = p;
    return *this;
}

Vector::~Vector() {
    std::cout << "Calling destructor\n";
    delete [] elem;
}

double &Vector::operator[](std::size_t i) {
    if (i >= size())
        throw std::out_of_range{"Vector::operator[]"};
    return elem[i];
}

std::size_t Vector::size() {
    return sz;
}

