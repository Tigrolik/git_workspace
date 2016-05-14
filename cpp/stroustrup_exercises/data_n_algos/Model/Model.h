#ifndef _MODEL_H_
#define _MODEL_H_

#include <fstream>
#include <array>
#include <vector>

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
//protected:
public:
    Vec_base();
    Vec_base(const std::array<T,N>&);
    Vec_base(const Vec_base&);

    virtual ~Vec_base() { }

    friend std::ostream& operator<< <> (std::ostream&, const Vec_base&);

    T operator[](const int i) { return a_[i]; }
    const T& operator[](const int i) const { return a_[i]; }

    size_t size() const { return N; }

protected:
    std::array<T, N> a_;
};

template <class T, class U, size_t N>
Vec_base<typename std::common_type<T, U>::type, N> operator+(const
        Vec_base<T, N> &lhs, const Vec_base<U, N> &rhs) {
    std::array<typename std::common_type<T, U>::type, N> a;
    for (size_t i {0}; i < N; ++i)
        a[i] = lhs[i] + rhs[i];
    return Vec_base<typename std::common_type<T, U>::type, N> {a};
}

class Vertex: public Vec_base<double, 3> {
public:
    Vertex();
    Vertex(const double, const double, const double);
    Vertex(const Vec_base<double, 3>&);

    friend std::istream& operator>>(std::istream&, Vertex&);

    double x() const { return a_[0]; }
    double y() const { return a_[1]; }
    double z() const { return a_[2]; }
};

/*
 * class Normal
 * Basically this class copies Vertex, the reason to have it is merely for a
 * name and with possible addition of specific methods
 */
class Normal: public Vertex { };

class Point3: public Vec_base<int, 3> {
public:
    Point3();
    Point3(const int, const int, const int);
    Point3(const Vec_base<int, 3>&);
    Point3(const Vec_base<double, 3>&);

    friend std::istream& operator>>(std::istream&, Point3&);

    int x() const { return a_[0]; }
    int y() const { return a_[1]; }
    int z() const { return a_[2]; }
};

class Facet {
public:
    Facet();
    Facet(const Point3&, const Point3&, const Point3&);

    Point3 operator[](const int i) { return f_[i]; }
    const Point3& operator[](const int i) const { return f_[i]; }

    friend std::istream& operator>>(std::istream&, Facet&);

private:
    std::array<Point3, 3> f_;
};

class Model {
public:
    Model(const std::string &);

    ~Model() = default;

    const Vertex vertex(const int i) const { return verts_[i]; }
    Point3 face(const int idx) const {
        return {faces_[idx][0][0], faces_[idx][1][0], faces_[idx][2][0]};
    }
    Vertex texvertex(const int, const int) const;
    const Normal normal(const int i) const { return norms_[i]; }

    size_t num_vertices() const { return verts_.size(); }
    size_t num_faces() const { return faces_.size(); }
    size_t num_normals() const { return norms_.size(); }
    size_t num_texvertices() const { return texverts_.size(); }

private:
    std::vector<Vertex> verts_;
    std::vector<Facet> faces_;
    std::vector<Normal> norms_;
    std::vector<Vertex> texverts_; // texture vertices
};

#endif

