#include "vector.h"
#include "vector2.h"
#include "vector_container.h"
#include <iostream>
#include <stdexcept>
#include <string>

using namespace std;

#if 0
double read_and_sum(const size_t s) {
    Vector v(s);

    double sum = 0;
    for (size_t i = 0; i < v.size(); ++i) {
        cin >> v[i];
        sum += v[i];
    }

    return sum;
}

void f(Vector& v) {
    try {
        v[v.size()] = 5.3;
    } catch (out_of_range) {
        cerr << "Index out of range\n";
    }
}

void test() {
    try {
        Vector v(-23);
    } catch (length_error) {
        cerr << "Negative size\n";
    } catch (bad_alloc) {
        cerr << "Bad allocation\n";
    }
}

void use(Container &c) {
    const size_t sz = c.size();
    for (size_t i = 0; i != sz; ++i)
        cout << c[i] << endl;
}
#endif

void write(const Vector2<string>& vs) {
    for (int i = 0; i < vs.size(); ++i)
        cout << vs[i] << endl;
}

void f2(const Vector2<string>& vs) {
    for (auto& s : vs)
        cout << s << endl;
}

int main()
{

    // const double s = read_and_sum(5);
    // cout << s << endl;
    // Vector v(4);
    // f(v);
    //test();
    //Vector_container vc{10, 9, 7, 6, 2};
    //use(vc);


    return 0;
}
