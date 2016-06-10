#include <iostream>
#include <chrono>
#include "Date.h"
#include "Tool.h"
#include "Matrix.h"

// modify the standart output for C-style strings
std::ostream& operator<<(std::ostream& os, const char * const s) {
    return os << "Initialize\n" + std::string(s) + "Clean up\n";
}

void test_date() {
    const Chrono::Date d {};
    std::cout << d << '\n';
}

void test_output() {
    std::cout << "Hello, World!\n";
}

/*
 * testing class Tool
 */
void test_tool() {
    constexpr Tool t1;
    std::cout << t1.strength() << ' ' << t1.type() << '\n';
    constexpr Tool t2 {2, 'p'};
    std::cout << t2.strength() << ' ' << t2.type() << '\n';
    Tool t3 = t1;
    t3 = t2;
    std::cout << t3.strength() << ' ' << t3.type() << '\n';
}

Matrix<int> sum_int_mat(const Matrix<int>& M1, const Matrix<int>& M2) {
    return Matrix<int> {M1 + M2};
}

void test_matrix() {
    constexpr int r {1000}, c {1000};
    const Matrix<int> M1 {r, c}, M2 {r, c};

    constexpr int n = {900}; // number of repetitions
    using namespace std::chrono;
    auto t = high_resolution_clock::now();
    for (int i {0}; i < n; ++i)
        const Matrix<int> M {M1 + M2};
    std::cout << duration<double>(high_resolution_clock::now() - t).count() <<
        '\n';

    t = high_resolution_clock::now();
    for (int i {0}; i < n; ++i)
        auto M = sum_int_mat(M1, M2);
    std::cout << duration<double>(high_resolution_clock::now() - t).count() <<
        '\n';
}

int main() {

    //test_date();
    //test_output();
    //test_tool();
    test_matrix();

    return 0;
}

