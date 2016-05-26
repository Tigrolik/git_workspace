#include <iostream>
#include <iomanip>

void test_precision() {
    constexpr int n {10};
    constexpr float x {1.0 / n};
    float sum {0};
    for (int i {0}; i < n; ++i)
        sum += x;
    std::cout << std::setprecision(15) << sum << '\n';
    constexpr short int y {4000};
    constexpr unsigned int i {1000000};
    std::cout << y << ' ' << i * i << '\n';
}

int main() {

    test_precision();

    return 0;
}

