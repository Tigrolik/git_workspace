#include <iostream>

constexpr unsigned short middle(const int a) {
    static_assert(sizeof(int) == 4, "unexpected int size");
    static_assert(sizeof(short) == 2, "unexpected short size");
    return (a >> 8) & 0xFFFF;
}

void test_mid() {
    using namespace std;
    constexpr unsigned int x {0xFFA3FF00};
    constexpr unsigned short y {middle(x)};
    cout << showbase << hex << y << dec << endl;
}


int main() {
    using namespace std;
    cout << ~0 << endl;

    test_mid();

    return 0;
}
