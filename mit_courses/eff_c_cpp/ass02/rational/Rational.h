/*
 * class Rational from Stroustrup book exercises (part 9)
 * Design and implement a rational number class, Rational.
 * A rational number has two parts: a numerator and a denominator.
 * Provide assignment, addition, subtraction, multiplication, division, and
 * equality operators. Also, provide a conversion to double
 */

#ifndef _RATIONAL_H_
#define _RATIONAL_H_

#include <iostream>
#include <stdexcept>

class Bad_rational: public std::domain_error {
public:
    explicit Bad_rational():
        std::domain_error("Bad rational: zero denominator") {
    }
};

class Rational {
    public:
        // default numerator is zero and default denominator is one to make the
        // constructor able to present integers with one argument
        Rational(const intmax_t = 0, const intmax_t = 1);
        Rational(const Rational&);
        Rational &operator=(const Rational&);

        intmax_t numer() const { return numer_; }
        intmax_t denom() const { return denom_; }

        Rational operator+(const Rational&);
        Rational operator-(const Rational&);
        Rational operator*(const Rational&);
        Rational operator/(const Rational&);
        const Rational inverse() const;

        friend std::ostream &operator<<(std::ostream&, Rational const&);

        Rational &simplify();
        void normalize();
        float to_float() const;
        double to_double() const;

    private:
        intmax_t numer_;
        intmax_t denom_;
};

inline bool operator==(const Rational &r1, const Rational &r2) {
    return r1.numer() * r2.denom() == r2.numer() * r1.denom();
}

inline bool operator<(const Rational &r1, const Rational &r2) {
    return r1.numer() * r2.denom() < r2.numer() * r1.denom();
}

// greatest common divisor of two ints (note: ignoring b being zero)
constexpr intmax_t gcd(const intmax_t a, const intmax_t b) {
    return (a == b || a == 0) ? b :
        (~a & 1) ? // a is even
        (b & 1) ? gcd(a >> 1, b) : gcd(a >> 1, b >>1) << 1
        : // a is odd
        (~b & 1) ? gcd(a, b >> 1) :
        (a > b) ? gcd((a - b) >> 1, b) : gcd((b - a) >> 1, a);
}

// least common multiple
constexpr intmax_t lcm(const intmax_t a, const intmax_t b) {
    return (a * b) / gcd(a, b);
}

double to_double(const Rational&);

inline Rational operator+(const Rational &r1, const Rational &r2) {
    const intmax_t lcm_val {lcm(r1.denom(), r2.denom())};
    return Rational {(lcm_val / r1.denom()) * r1.numer() +
        (lcm_val / r2.denom()) * r2.numer(), lcm_val};
}

inline Rational operator-(const Rational &r1, const Rational &r2) {
    const intmax_t lcm_val {lcm(r1.denom(), r2.denom())};
    return Rational {(lcm_val / r1.denom()) * r1.numer() -
        (lcm_val / r2.denom()) * r2.numer(), lcm_val};
}

inline Rational operator*(const Rational &r1, const Rational &r2) {
    return Rational {r1.numer() * r2.numer(), r1.denom() * r2.denom()};
}

inline Rational operator/(const Rational &r1, const Rational &r2) {
    return Rational {r1.numer() * r2.denom(), r1.denom() * r2.numer()};
}

#endif

