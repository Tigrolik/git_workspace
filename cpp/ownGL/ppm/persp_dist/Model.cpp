#include "Model.h"
#include <iostream>
#include <cmath>
#include <stdexcept>

/*
 * ------------------ Model vector implementation ------------------
 */
template <class T>
Model_vector<T>::Model_vector(const std::vector<T> &v): v_{v} {
}

template <class T>
Model_vector<T>::Model_vector(const Model_vector<T> &mv): v_{mv.v_} {
}

template <class T>
Model_vector<T> &Model_vector<T>::operator=(const Model_vector<T> &mv) {
    if (this != &mv)
        v_ = mv.v_;
    return *this;
}

template <class T>
const T &Model_vector<T>::operator[](const int i) const {
    return (i >= 0 && i < size()) ? v_[i] : v_[0];
}

template <class T>
T &Model_vector<T>::operator[](const int i) {
    return (i >= 0 && i < size()) ? v_[i] : v_[0];
}

template <class T>
const Model_vector<T> Model_vector<T>::operator+(const Model_vector<T> &mv)
    const {
    const int n {mv.size()};
    std::vector<T> w(n);
    if (n != mv.size())
        throw std::runtime_error("error: vectors sizes do not match");
    else
        for (int i {0}; i < n; ++i)
            w[i] = v_[i] + mv[i];
    return w;
    }

template <class T>
Model_vector<T> Model_vector<T>::operator+(const Model_vector<T> &mv) {
    const int n {mv.size()};
    std::vector<T> w(n);
    if (n != mv.size())
        throw std::runtime_error("error: vectors sizes do not match");
    else
        for (int i {0}; i < n; ++i)
            w[i] = v_[i] + mv[i];
    return w;
}

template <class C>
std::ostream& operator<<(std::ostream &os, const Model_vector<C> &mv) {
    for (int i {0}; i < mv.size(); ++i)
        os << mv[i] << ' ';
    return os;
}

/*
 * ------------------ Vertex implementation ------------------
 */
Vertex::Vertex(const std::vector<double> &v): Model_vector{v} {
}

Vertex::Vertex(const Model_vector<double> &mv): Model_vector{mv} {
}

Vertex::Vertex(const double a, const double b, const double c): Model_vector() {
    v_ = std::vector<double>{a, b, c};
}

Vertex Vertex::operator+(const Model_vector<double> &mv) {
    return Vertex {Model_vector<double>::operator+(mv)};
}

const Vertex Vertex::operator+(const Model_vector<double> &mv) const {
    return Vertex {Model_vector<double>::operator+(mv)};
}

std::ostream& operator<<(std::ostream &os, const Vertex &v) {
    return os << (Model_vector<double>&)v;
}

std::istream& operator>>(std::istream &is, Vertex &v) {
    std::vector<double> vd(3);
    for (auto &x: vd)
        if (!(is >> x))
            return is;
    v = Vertex {vd};
    return is;
}

/*
 * ------------------ Normal implementation ------------------
 */
Normal::Normal(const std::vector<double> &v): Vertex{v} {
}

Normal::Normal(const Model_vector<double> &mv): Vertex{mv} {
}

Normal::Normal(const double a, const double b, const double c): Vertex{a,b,c} {
}

/*
 * ------------------ Point3 implementation ------------------
 */
Point3::Point3(const int a, const int b, const int c): Model_vector{} {
    v_ = std::vector<int>{a, b, c};
}

Point3::Point3(const std::vector<int> &v): Model_vector{v} {
}

//Point3::Point3(const std::vector<double> &v):
//    Point3(round(v[0]), round(v[1]), round(v[2])) {
//}

Point3::Point3(const Model_vector<int> &mv): Model_vector{mv} {
}

//Point3::Point3(const Model_vector<double> &mv):
//    Point3(round(mv[0]), round(mv[1]), round(mv[2])) {
//}

Point3::Point3(const Vertex &v):
    Point3(round(v.x()), round(v.y()), round(v.z())) {
    }

Point3 Point3::operator+(const Model_vector<int> &mv) {
    return Point3 {Model_vector<int>::operator+(mv)};
}

const Point3 Point3::operator+(const Model_vector<int> &mv) const {
    return Point3 {Model_vector<int>::operator+(mv)};
}

//Point3 Point3::operator+(const Model_vector<double> &mv) {
//    return Point3 {Model_vector<double>::operator+(mv)};
//}

//const Point3 Point3::operator+(const Model_vector<double> &mv) const {
//    return Point3 {Model_vector<double>::operator+(mv)};
//}

std::ostream& operator<<(std::ostream &os, const Point3 &p) {
    return os << (Model_vector<int>&)p;
}

/*
 * ------------------ Model implementation ------------------
 */
Model::Model(const std::string &fn): verts_{}, faces_{}, norms_{}, texverts_{} {
    std::ifstream ifs {fn};
    if (!ifs)
        throw std::runtime_error("cannot open file " + fn);
    ifs.exceptions(ifs.exceptions() | std::ios_base::badbit);

    for (std::string s; ifs >> s;) {
        if (s == "v") {
            Vertex v; ifs >> v;
            verts_.push_back(v);
        }
        if (s == "f") {
            // reading the triples: (vertex / texvertex / normal)
            std::vector<std::vector<int>> v(3);
            for (auto &x: v) {
                int i; char c;
                ifs >> i; x.push_back(--i); ifs >> c;
                ifs >> i; x.push_back(--i); ifs >> c;
                ifs >> i; x.push_back(--i);
            }
            faces_.push_back(v);
        }
        if (s == "vn") {
            // reading vertex normals
            Normal nv; ifs >> nv;
            norms_.push_back(nv);
        }
        if (s == "vt") {
            // reading texture vertices
            Vertex texv; ifs >> texv;
            texverts_.push_back(texv);
        }
        if (ifs.fail()) {
            ifs.unget();
            ifs.clear(std::ios_base::failbit);
        }
    }
}

