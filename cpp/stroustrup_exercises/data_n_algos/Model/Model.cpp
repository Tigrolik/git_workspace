#include <algorithm>
#include "Model.h"

/*
 * ------------------ Vec_base implementation ------------------
 */
template <class T, size_t N>
Vec_base<T, N>::Vec_base(): a_() {
}

template <class T, size_t N>
Vec_base<T, N>::Vec_base(const std::array<T,N> &a): a_(a) {
    /* note: init with the regular brackets (not curved) */
}

template <class T, size_t N>
Vec_base<T, N>::Vec_base(const Vec_base &v): a_(v.a_) {
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
Vertex::Vertex(): Vec_base {} { }

Vertex::Vertex(const double a, const double b, const double c):
    Vec_base {std::array<double, 3> {a, b, c}} {
    }

Vertex::Vertex(const Vec_base<double, 3> &v): Vec_base {v} { }

std::istream& operator>>(std::istream &is, Vertex &v) {
    double a, b, c;
    is >> a >> b >> c;
    if (is) v = Vertex {a, b, c};
    return is;
}

std::ostream& operator<<(std::ostream &os, const Vertex &v) {
    return os << (Vec_base<double, 3>&)v;
}

/*
 * ------------------ Point3 implementation ------------------
 */
Point3::Point3(): Vec_base {} { }

Point3::Point3(const int a, const int b, const int c):
    Vec_base {std::array<int, 3> {a, b, c}} {
    }

Point3::Point3(const Vec_base<int, 3> &v): Vec_base {v} { }

Point3::Point3(const Vec_base<double, 3> &v): Vec_base {} {
    for (int i {0}; i < 3; ++i)
        a_[i] = round(v[i]);
}

std::istream& operator>>(std::istream &is, Point3 &p) {
    int a, b, c;
    char ch;
    is >> a >> ch >> b >> ch >> c;
    if (is) p = Point3 {--a, --b, --c};
    return is;
}


std::ostream& operator<<(std::ostream &os, const Point3 &p) {
    return os << (Vec_base<int, 3>&)p;
}

/*
 * ------------------ Point3 implementation ------------------
 */
Facet::Facet(): f_() { }

Facet::Facet(const Point3 &p1, const Point3 &p2, const Point3 &p3):
    f_(std::array<Point3, 3> {p1, p2, p3}) {
}

std::istream& operator>>(std::istream &is, Facet &f) {
    Point3 p1, p2, p3;
    is >> p1 >> p2 >> p3;
    if (is) f = Facet {p1, p2, p3};
    return is;
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
            Facet f; ifs >> f;
            faces_.push_back(f);
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

Vertex Model::texvertex(const int iface, const int ivert) const {
    const int idx {faces_[iface][ivert][1]};
    return Vertex {texverts_[idx][0], texverts_[idx][1], texverts_[idx][2]};
}

