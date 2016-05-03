#include "Vector.h"
#include <iostream>
#include <chrono>

using namespace std;

void test_vector() {
    Vector<double> v(5);
    for (int i {0}; i < v.size(); ++i) {
        v[i] = 1.1 * i;
        std::cout << "v{" << i << "]==" << v[i] << '\n';
    }

    Vector<double> v2 {1.302, 20.003, 5.95};
    Vector<double> v3 {v2};
    v3[1] = 7.2890;
    Vector<double> v4 = v3;
    v4[0] = 0.327;
    v4 = v4;
    for (int i {0}; i < v2.size(); ++i)
        std::cout << v2[i] << ' ';
    std::cout << '\n';
    for (int i {0}; i < v3.size(); ++i)
        std::cout << v3[i] << ' ';
    std::cout << '\n';
    for (int i {0}; i < v4.size(); ++i)
        std::cout << v4[i] << ' ';
    std::cout << '\n';
    //Vector<double> v5 = 10;
    //for (int i {0}; i < v5.size(); ++i)
    //    std::cout << v5[i] << ' ';
    //std::cout << '\n';
}

Vector<double> fill() {
    constexpr int n {1000000};
    Vector<double> res(n);
    for (int i {0}; i < n; ++i)
        res[i] = i >> 1;
    return std::move(res);
}

void test_move() {
    using namespace std::chrono;
    auto t = high_resolution_clock::now();
    for (int i {0}; i < 1; ++i)
        Vector<double> v = std::move(fill());
    std::cout << duration<double>(high_resolution_clock::now() - t).count() <<
        '\n';
}

void test_index_operator() {
    Vector<double> v(10);
    //double x = v[2];
    v[3] = 5;
    for (int i {0}; i < v.size(); ++i)
        std::cout << v[i] << ' ';
    std::cout << '\n';
    //cout << v << endl;
    const Vector<double> v2 {v};
    cout << v2 << endl;
}

int main() {

    //test_vector();
    //test_move();
    test_index_operator();

    return 0;
}

