#include "Model.h"
#include <iostream>

using namespace std;

void test_model_vectors() {
    const Vertex vx1 {1, 2, 3}, vx2 {4, 6, 8};
    const Vertex vx = vx1 + vx2;
    cout << vx << endl;
    const Normal n1 {7.5, 8.3, 9.2};
    cout << n1 + vx1 << endl;
    const Point3 p1 {0, 5, 10};
    cout << p1 << endl;
    //cout << p1 + vx1 << endl;
}

void test_model() {
    Model m {"../obj/african_head.obj"};
    cout << "Verts: " << m.num_vertices() << ", v[1]: " << m.vertex(1) << endl;
    cout << "Norms: " << m.num_normals() << ", n[1]: " << m.normal(1) << endl;
    cout << "Texture vertices: " << m.num_texvertices() << endl;
        //", texv[1]: " << m.normal(1) << endl;
    Normal v {m.normal(1)}, v2 {m.normal(2)};
    cout << v + v2 << endl;
}

int main() {

    test_model_vectors();
    //test_model();

    return 0;
}
