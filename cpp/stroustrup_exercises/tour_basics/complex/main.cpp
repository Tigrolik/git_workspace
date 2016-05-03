#include "myComplex.h"
#include <iostream>

using namespace std;

myComplex operator+(myComplex a, myComplex b) {
    return a += b;
}

myComplex operator-(myComplex a, myComplex b) {
    return a -= b;
}

myComplex operator-(myComplex a) {
    return {-a.real(), -a.imag()};
}

myComplex operator*(myComplex a, myComplex b) {
    return a *= b;
}

myComplex operator/(myComplex a, myComplex b) {
    return a /= b;
}

int main()
{

    myComplex z(3);
    myComplex w(4, 7);
    z = z / w;

    cout << z.real() << " + i" << z.imag() << endl;

    myComplex a(4, 2), b(3, -1), c;
    c = a / b;

    cout << c.real() << " + i" << c.imag() << endl;

    myComplex d {1 / b};
    cout << b.real() << " + i" << b.imag() << endl;

    return 0;
}
