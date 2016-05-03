#include "Vector.h"
#include "Link.h"
#include <iostream>
#include <chrono>

using namespace std;

void test_vector() {
    Vector v(5);
    for (int i {0}; i < v.size(); ++i) {
        v.set(i, 1.1 * i);
        std::cout << "v{" << i << "]==" << v.get(i) << '\n';
    }

    Vector v2 {1.302, 20.003, 5.95};
    Vector v3 {v2};
    v3.set(1, 7.2890);
    Vector v4 = v3;
    v4.set(0, 0.327);
    v4 = v4;
    for (int i {0}; i < v2.size(); ++i)
        std::cout << v2.get(i) << ' ';
    std::cout << '\n';
    for (int i {0}; i < v3.size(); ++i)
        std::cout << v3.get(i) << ' ';
    std::cout << '\n';
    for (int i {0}; i < v4.size(); ++i)
        std::cout << v4.get(i) << ' ';
    std::cout << '\n';
    //Vector v5 = 10;
    //for (int i {0}; i < v5.size(); ++i)
    //    std::cout << v5.get(i) << ' ';
    //std::cout << '\n';
}

Vector fill() {
    constexpr int n {1000000};
    Vector res(n);
    for (int i {0}; i < n; ++i)
        res.set(i, i * 0.5);
    return std::move(res);
}

void test_move() {
    using namespace std::chrono;
    auto t = high_resolution_clock::now();
    for (int i {0}; i < 1; ++i)
        Vector v = std::move(fill());
    std::cout << duration<double>(high_resolution_clock::now() - t).count() <<
        '\n';
}

void test_index_operator() {
    Vector v(10);
    //double x = v[2];
    v[3] = 5;
    for (int i {0}; i < v.size(); ++i)
        std::cout << v[i] << ' ';
    std::cout << '\n';
    //cout << v << endl;
    const Vector v2 {v};
    cout << v2 << endl;
}

void test_link() {
    Link *norse_gods = new Link {"Thor", nullptr, nullptr};
    norse_gods = new Link{"Odin", nullptr, norse_gods};
    norse_gods->next->prev = norse_gods;
    norse_gods = new Link{"Freia", nullptr, norse_gods};
    norse_gods->next->prev = norse_gods;
}

int main() {

    //test_vector();
    //test_move();
    test_index_operator();
    //test_link();

    return 0;
}

