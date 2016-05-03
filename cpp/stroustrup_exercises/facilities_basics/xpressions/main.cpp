#include <iostream>

template<typename T> constexpr T max_val(const T a, const T b) {
    return a < b ? b : a;
}

int main() {

    int y {3}, z{2};
    int x = y = z = 5;

    using namespace std;

    int *q = &++x;

    cout << x << ' ' << y << ' ' << z  << ' ' << q << endl;

    int v[4];
    int i {1};
    // v[i] = i++;
    v[i] = i;
    cout << v[i] << endl;

    const int x1 = 7;
    constexpr int x2 = x1;

    cout << max_val(x2, 8) << endl;

    return 0;
}
