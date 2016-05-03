#include "Rational.h"
#include "Money.h"
#include <algorithm>

using namespace std;

void test_rat() {
    Rational r1 {-3, -4}, r2 {5, -6};
    cout << r1 << ' ' << r2 << endl;
    cout << r1 + r2 << endl;
    cout << r1 - r2 << endl;
    cout << (r1 * r2).simplify() << endl;
    cout << (r1 / r2).simplify() << endl;
    cout << (r1 == r2) << endl;
    cout << (r1 == Rational{3, 4}) << endl;
    cout << to_double(r2) << endl;
    Rational r {3, -4};
    cout << r << endl;
    r = r1 + Rational{2, 7} - Rational{r2};
    cout << r << endl;
    r = Rational{-2, -9};
    cout << r << endl;
    // r = Rational{-2, -0};
}

void test_gcd() {
    int a {4}, b {18};
    cout << gcd(a, b) << ' ' << lcm(a, b) << endl;
    a = abs(-3), b = 5;
    cout << gcd(a, b) << ' ' << lcm(a, b) << endl;
    a = 0, b = 5;
    cout << gcd(a, b) << ' ' << lcm(a, b) << endl;
    a = 0, b = 0;
    cout << gcd(a, b) << ' ' << lcm(a, b) << endl;
}

long int to_int(const double d) {
    return static_cast<long int>(d * 100 + 0.5);
}

void test_money() {
    Money m {2.30};
    cout << m << endl;
    cout << Money{0} << endl;
    cout << Money{129.3439} << endl;
    const double d {1034.3452};
    cout << Money{d} << endl;
    cout << to_int(d) << endl;
    cin >> m;
    cout << m << endl;
}

int main() {

    //test_gcd();
    //test_rat();
    test_money();

    return 0;
}
