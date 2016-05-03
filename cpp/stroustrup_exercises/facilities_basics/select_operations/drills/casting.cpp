#include <iostream>
#include <stdexcept>

using namespace std;

template<class Target, class Src>
Target narrow_cast(Src v) {
    auto r = static_cast<Target>(v);
    if (static_cast<Src>(r) != v)
        throw runtime_error("narrow_cast<>() failed");
    return r;
}

void test_narrow_cast() {
    auto c1 = narrow_cast<char>(64);
    auto c3 = narrow_cast<char>(264);
    auto d1 = narrow_cast<double>(1/3.0F); // OK
    auto f1 = narrow_cast<float>(1/3.0);
    int i {37};
    auto c4 = narrow_cast<char>(i);
    double d {-1234.2083};
    auto f2 = narrow_cast<float>(d); // may throw
    auto d2 = narrow_cast<double>(i);
    auto i2 = narrow_cast<int>(d); // may throw (but probably will not)
    cout << c1 << c3 << d1 << f1 << c4 << f2 << d2 << i2 << endl;
}

int main() {

    test_narrow_cast();

    return 0;
}
