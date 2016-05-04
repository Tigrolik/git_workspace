#include "Model.h"

/*
 * ------------------ Vec_base implementation ------------------
 */
template <class T, size_t N>
Vec_base<T, N>::Vec_base(const std::array<T,N> &a): a_(a) {
/* note: init with the regular brackets (not curved) */
}

template <class T, size_t N>
Vec_base<T, N>::Vec_base(const Vec_base &v): a_(v.a_) {
}

template <class T, size_t N>
Vec_base<T, N> Vec_base<T, N>::operator+(const Vec_base<T, N> &v) {
    std::array<T, N> a;
    for (size_t i {0}; i < N; ++i)
        a[i] = a_[i] + v[i];
    return a;
}

template <class T, size_t N>
std::ostream& operator<<(std::ostream &os, const Vec_base<T, N> &v) {
    os << "{ ";
    for (size_t i {0}; i < N; ++i)
        os << v[i] << ' ';
    return os << '}';
}

/*
 * ------------------ Vertex implementation ------------------
 */
Vertex::Vertex(const double a, const double b, const double c):
    Vec_base {std::array<double, 3> {a, b, c}} {
    }

Vertex::Vertex(const Vec_base<double, 3> &v): Vec_base {v} { }

Vertex  Vertex::operator+(const Vertex &v) {
    return Vertex {Vec_base<double, 3>::operator+(v)};
}

std::ostream& operator<<(std::ostream &os, const Vertex &v) {
    return os << (Vec_base<double, 3>&)v;
}

