#ifndef _MODEL_H_
#define _MODEL_H_

#include <fstream>
#include <vector>

template <class T>
class Model_vector {
protected: // fields and ctors
    std::vector<T> v_;
    Model_vector<T>(const std::vector<T>& = {});
    Model_vector<T>(const Model_vector<T>&);
    Model_vector<T> &operator=(const Model_vector<T>&);

public: // methods
    virtual ~Model_vector<T>() { }

    const T &operator[](const int) const;
    T &operator[](const int);

    Model_vector<T> operator+(const Model_vector<T>&);
    const Model_vector<T> operator+(const Model_vector<T>&) const;

    template <class C>
        friend std::ostream& operator<<(std::ostream&, const Model_vector<C>&);

    int size() const { return v_.size(); }
    std::vector<T> values() const { return v_; }
};

class Vertex: public Model_vector<double> {
public:
    Vertex(const std::vector<double>& = {});
    Vertex(const Model_vector<double>&);
    Vertex(const double, const double, const double);

    Vertex operator+(const Model_vector<double>&);
    const Vertex operator+(const Model_vector<double>&) const;

    friend std::ostream& operator<<(std::ostream&, const Vertex&);
    friend std::istream& operator>>(std::istream&, Vertex&);

    double x() const { return v_[0]; }
    double y() const { return v_[1]; }
    double z() const { return v_[2]; }
};

class Normal: public Vertex {
public:
    Normal(const std::vector<double>& = {});
    Normal(const Model_vector<double>&);
    Normal(const double, const double, const double);
};

class Point3: public Model_vector<int> {
public:
    Point3(const int, const int, const int);
    Point3(const std::vector<int>& = {});
    //Point3(const std::vector<double>&);
    Point3(const Model_vector<int>&);
    //Point3(const Model_vector<double>&);
    Point3(const Vertex&);

    Point3 operator+(const Model_vector<int>&);
    const Point3 operator+(const Model_vector<int>&) const;
    //Point3 operator+(const Model_vector<double>&);
    //const Point3 operator+(const Model_vector<double>&) const;

    friend std::ostream& operator<<(std::ostream&, const Point3&);

    int x() const { return v_[0]; }
    int y() const { return v_[1]; }
    int z() const { return v_[2]; }
};



class Model {
public:
    Model(const std::string &);

    ~Model() = default;

    const Vertex vertex(const int i) const { return verts_[i]; }
    const Normal normal(const int i) const { return norms_[i]; }

    int num_vertices() const { return verts_.size(); }
    int num_faces() const { return faces_.size(); }
    int num_normals() const { return norms_.size(); }
    int num_texvertices() const { return texverts_.size(); }

private:
    std::vector<Vertex> verts_;
    std::vector<std::vector<std::vector<int>>> faces_;
    std::vector<Normal> norms_;
    std::vector<Vertex> texverts_;
};

#endif

