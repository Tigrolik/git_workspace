#include <iostream>
#include <vector>
#include <random>
#include <functional> // std::bind

void test_bind() {
    constexpr size_t n {15};
    auto gen = std::bind(std::normal_distribution<double> {n, 4.0},
            std::default_random_engine {});
    std::vector<int> hist(n << 1);
    for (size_t i {0}; i < 500; ++i)
        ++hist[int(round(gen()))];
    for (size_t i {0}; i < hist.size(); ++i) {
        std::cout << i << '\t';
        for (int j {0}; j < hist[i]; ++j)
            std::cout << '*';
        std::cout << '\n';
    }
}

int main () {

    test_bind();

    return 0;
}

