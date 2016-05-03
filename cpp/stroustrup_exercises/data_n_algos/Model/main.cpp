#include <iostream>
#include "Model.h"

using namespace std;

void test_init() {
    //constexpr int n {3};
    constexpr array<size_t, 3> arr1 {1, 2, 3};
    Vec_base<size_t, 3> vb1 {arr1};
    cout << arr1[1] << '\n';
    cout << vb1[1] << '\n';
}

int main() {

    test_init();

    return 0;
}

