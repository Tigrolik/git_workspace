#include "Rational.h"
#include <algorithm>
#include <iomanip>
#include <cassert>

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
    //r = Rational{-2, -0};
    auto s = Rational {1, 3} + Rational {2, 15};
    assert(s.numer() == 7);
    assert(s.denom() == 15);
}

double golden_ratio(const intmax_t num_iter) {
    Rational phi {1};
    for (auto i = 0; i < num_iter; ++i)
        phi = 1 / (phi + 1);
    cout << setprecision(15) << "phi = " << (1 + phi).to_double() << endl;
    return (1 + phi).to_double();
}

long int to_int(const double d) {
    return static_cast<long int>(d * 100 + 0.5);
}

void test_new() {
    auto a = Rational{ 1, 3 }; // the number 1/3
    auto b = Rational{ -6, 7 }; // the number -6/7
    std::cout << a << " * " << b << " = " << a * b << "\n";
    std::cout << "Now for something more complicated...\n";
    std::cout << "a / ( a + b / a ) = " << a / ( a + b / a ) << "\n";

    auto phi = Rational{ 1 };

    for( int i = 0; i < 40; ++i ) {
        phi = 1 / ( 1 + phi );
    }
    std::cout << std::setprecision( 15 );
    std::cout << "phi = " << ( 1 + phi ).to_double() << "\n";
}

int main() {

    test_rat();
    test_new();
    golden_ratio(50);

    return 0;
}
