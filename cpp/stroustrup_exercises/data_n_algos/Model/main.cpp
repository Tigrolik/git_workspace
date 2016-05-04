#include "Model.h"
#include <iostream>

//using namespace std;

void test_init() {
    //constexpr int n {3};
    //constexpr std::array<int, n> arr1 {1, 2, 3};
    //const Vec_base<int, n> vb1;
    //const Vec_base<int, n> vb1 {arr1};
    //std::cout << vb1[1] << '\n';
    Vertex vx1 {1, 2, 3};
    Vertex vx2 {vx1};
    //std::cout << vx1[1] << '\n';
    std::cout << vx1 + vx2 << '\n';
}


int main() {

    test_init();

    return 0;
}

