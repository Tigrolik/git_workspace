#include "Model.h"
#include <iostream>

//using namespace std;

void test_init() {
    //constexpr int n {3};
    //constexpr std::array<int, n> arr1 {1, 2, 3};
    //const Vec_base<int, n> vb1;
    //const Vec_base<int, n> vb1 {arr1};
    //std::cout << vb1[1] << '\n';
    Vertex vx1 {1.05, 2.5, 3.4};
    Vertex vx2 {vx1};
    std::cout << vx1[1] << '\n';
    std::cout << vx1.x() << '\n';
    std::cout << vx1 + vx2 << '\n';
    Point3 p1 {1, 2, 3};
    std::cout << p1 + Point3 {4, 5, 6} << '\n';
    std::cout << p1 + vx1 << '\n';
    Point3 p2 = p1 + vx1;
    std::cout << p2 << '\n';
    //std::array<int, 3> a1 = std::array<int, 3> {1, 2, 3};
    Point3 p3;
    std::cout << p3 << '\n';
    Vertex v3;
    std::cout << v3 << '\n';
    std::cout << v3.size() << '\n';
    Normal n1;
    std::cout << n1 << '\n';
}

void test_model() {
    using namespace std;
    Model m {"african_head.obj"};
    cout << "Verts: " << m.num_vertices() << ", v[1]: " << m.vertex(1) << endl;
    cout << "Norms: " << m.num_normals() << ", n[1]: " << m.normal(1) << endl;
    cout << "Texture vertices: " << m.num_texvertices() <<
        ", texv[1][1]: " << m.texvertex(1, 1) << endl;
    cout << "Faces: " << m.num_faces() << ", f[1]: " << m.face(1) << endl;
    Normal v {m.normal(1)}, v2 {m.normal(2)};
    cout << v + v2 << endl;
}

int main() {

    //test_init();
    test_model();

    return 0;
}

