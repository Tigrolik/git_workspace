#include "myComplex.h"
#include <stdexcept>
#include <exception>

myComplex::myComplex(double r, double i): re(r), im(i) {
}

double myComplex::real() const {
    return re;
}

double myComplex::imag() const {
    return im;
}

void myComplex::real(const double d) {
    re = d;
}

void myComplex::imag(const double d) {
    im = d;
}

double myComplex::norm() {
    return re * re + im * im;
}

myComplex &myComplex::operator+=(myComplex z) {
    re += z.real();
    im += z.imag();
    return *this;
}

myComplex &myComplex::operator-=(myComplex z) {
    re -= z.real();
    im -= z.imag();
    return *this;
}

myComplex &myComplex::operator*=(myComplex z) {
    const double re_this = re, z_re = z.real(), z_im = z.imag();
    re = re * z_re - im * z_im;
    im = re_this * z_im + im * z_re;
    return *this;
}

myComplex &myComplex::operator/=(myComplex z) {
    const myComplex z_conj(z.real(), -z.imag());
    const double z_norm = z.norm();

    *this *= z_conj;
    re /= z_norm;
    im /= z_norm;
    return *this;
}

