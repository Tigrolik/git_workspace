#include "Rational.h"

Rational::Rational(const intmax_t n, const intmax_t d): numer_{n}, denom_{d} {
    if (d == 0)
        throw Bad_rational {};
    // make sure that the denom is always positive
    if (denom_ < 0) {
        denom_ = -denom_;
        numer_ = -numer_;
    }
    normalize();
}

Rational::Rational(const Rational &o): numer_{o.numer()}, denom_{o.denom()} {}

Rational &Rational::operator=(const Rational &o) {
    if (this == &o)
        return *this;
    numer_ = o.numer();
    denom_ = o.denom();
    return *this;
}

std::ostream &operator<<(std::ostream &os, Rational const &r) {
    return os << r.numer() << '/' << r.denom();
}

Rational Rational::operator+(const Rational &o) {
    const intmax_t lcm_val {lcm(denom_, o.denom())};
    return Rational {(lcm_val / denom_) * numer_ +
        (lcm_val / o.denom()) * o.numer(), lcm_val};
}

Rational Rational::operator-(const Rational &o) {
    const intmax_t lcm_val {lcm(denom_, o.denom())};
    return Rational {(lcm_val / denom_) * numer_ -
        (lcm_val / o.denom()) * o.numer(), lcm_val};
}

Rational Rational::operator*(const Rational &o) {
    return Rational {numer_ * o.numer(), denom_ * o.denom()};
}

Rational Rational::operator/(const Rational &o) {
    return Rational {numer_ * o.denom(), denom_ * o.numer()};
}

const Rational Rational::inverse() const {
    return Rational {denom_, numer_};
}

Rational &Rational::simplify() {
    const intmax_t g {gcd(abs(numer_), denom_)};
    numer_ /= g;
    denom_ /= g;
    return *this;
}

void Rational::normalize() {
    const intmax_t g {gcd(abs(numer_), denom_)};
    numer_ /= g;
    denom_ /= g;
}

float Rational::to_float() const {
    return static_cast<float>(numer_) / denom_;
}

double Rational::to_double() const {
    return static_cast<double>(numer_) / denom_;
}

double to_double(const Rational &r) {
    return static_cast<double>(r.numer()) / r.denom();
}

