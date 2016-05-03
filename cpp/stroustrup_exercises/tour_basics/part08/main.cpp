#include "my_lib_facilities.h"

// using std::string;
// using std::vector;
// using std::cout;
// using std::endl;

int my_find(const vector<string> vs, const string &s, const int = 0) {
    for (size_t i = 0; i < vs.size(); ++i)
        if (vs[i] == s)
            return i;
    return -1;
}

constexpr double abs(const double a) {
    return (a < 0) ? -a : a;
}

// const Date default_date() {
//     return Date(1970, 1, 1);
// }

constexpr double max(const double a, const double b) {
    return (a > b) ? a : b;
}

int f(int& x) {
    return x++;
}

void test_my_find() {
    const vector<string> vs {"testing", "string", "with", "sample", "words"};
    const int k = my_find(vs, "with");
    cout << k << endl;
    cout << my_find(vs, "With") << endl;
}

void test_functions() {
    constexpr double m = -5.02;
    cout << "abs(" << m << ") = " << abs(m) << endl;
    cout << max(3.03, -23.308) << endl;
    int x = 7;
    cout << "x = " << x << endl;
    cout << "f(x) = " << f(x) << endl;
    cout << "again x = " << x << endl;
}

void test_swap() {
    int x {7}, y {9};
    cout << x << ' ' << y << endl;
    swap_v(x, y);
    cout << x << ' ' << y << endl;
    swap_r(x, y);
    cout << x << ' ' << y << endl;
}

int main() {

    // test_my_find();
    // test_functions();
    test_swap();

    return 0;
}
