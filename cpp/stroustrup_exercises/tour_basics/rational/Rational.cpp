#include "Rational.h"

Rational::Rational(const int n, const int d): numer_{n}, denom_{d} {
    if (d == 0) {
        std::cerr << "error: denominator cannot be zero\n";
        throw Invalid {};
    }
    // make sure that the denom is always positive
    if (denom_ < 0) {
        denom_ = -denom_;
        numer_ = -numer_;
    }
}

Rational::Rational(const Rational &o): numer_{o.numer()}, denom_{o.denom()} {}

Rational &Rational::operator=(const Rational &o) {
    if (this == &o)
        return *this;
    numer_ = o.numer();
    denom_ = o.denom();
    return *this;
}

inline int Rational::numer() const {
    return numer_;
}

inline int Rational::denom() const {
    return denom_;
}

std::ostream &operator<<(std::ostream &os, Rational const &r) {
    return os << r.numer() << '/' << r.denom();
}

Rational Rational::operator+(const Rational &o) {
    int lcm_val {lcm(denom_, o.denom())};
    return Rational {(lcm_val / denom_) * numer_ +
        (lcm_val / o.denom()) * o.numer(), lcm_val};
}

Rational Rational::operator-(const Rational &o) {
    int lcm_val {lcm(denom_, o.denom())};
    return Rational {(lcm_val / denom_) * numer_ -
        (lcm_val / o.denom()) * o.numer(), lcm_val};
}

Rational Rational::operator*(const Rational &o) {
    return Rational {numer_ * o.numer(), denom_ * o.denom()};
}

Rational Rational::operator/(const Rational &o) {
    return Rational {numer_ * o.denom(), denom_ * o.numer()};
}

bool operator==(const Rational &r1, const Rational &r2) {
    return (r1.numer() == r2.numer() && r1.denom() == r2.denom());
}

Rational &Rational::simplify() {
    const int g {gcd(abs(numer_), denom_)};
    numer_ /= g;
    denom_ /= g;
    return *this;
}

double to_double(const Rational &r) {
    return static_cast<double>(r.numer()) / r.denom();
}

