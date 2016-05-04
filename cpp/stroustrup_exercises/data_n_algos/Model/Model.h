#ifndef _MODEL_H_
#define _MODEL_H_

#include <fstream>
#include <vector>
#include <array>

/*
 * Base class for arrays of fixed size.
 * The purpose is to create classes for 2-3 element arrays of int or double
 * Note: without classes which explicitly define template parameters (like
 * Vertex with 3 doubles) the design would require to put explicit type
 * declarations in the class' .cpp file
 */
template <class T, size_t N> class Vec_base; // forward declaration
template <class T, size_t N>
std::ostream& operator<<(std::ostream&, const Vec_base<T, N>&);

template <class T, size_t N>
class Vec_base {
public:
    Vec_base(const std::array<T,N>&);
    Vec_base(const Vec_base&);

    virtual ~Vec_base() { }

    Vec_base operator+(const Vec_base&);

    friend std::ostream& operator<< <> (std::ostream&, const Vec_base&);

    T operator[](const int i) { return a_[i]; }
    const T& operator[](const int i) const { return a_[i]; }

private:
    std::array<T, N> a_;
};

class Vertex: public Vec_base<double, 3> {
public:
    Vertex(const double, const double, const double);
    Vertex(const Vec_base<double, 3>&);

    Vertex operator+(const Vertex&);

    friend std::ostream& operator<<(std::ostream&, const Vertex&);
};

#endif

