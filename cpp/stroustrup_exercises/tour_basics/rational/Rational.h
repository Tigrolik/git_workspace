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

class Rational {
    public:
        class Invalid { };
        // default numerator is zero and default denominator is one to make the
        // constructor able to present integers with one argument
        Rational(const int = 0, const int = 1);
        Rational(const Rational&);
        Rational &operator=(const Rational&);

        int numer() const;
        int denom() const;

        Rational operator+(const Rational&);
        Rational operator-(const Rational&);
        Rational operator*(const Rational&);
        Rational operator/(const Rational&);

        friend std::ostream &operator<<(std::ostream&, Rational const&);

        Rational &simplify();

    private:
        int numer_;
        int denom_;
};

bool operator==(const Rational&, const Rational&);

// greatest common divisor of two ints
constexpr int gcd(const int a, const int b) {
    return (a == b || b == 0) ? a :
        (a == 0) ? b :
        (~a & 1) ? // a is even
        (b & 1) ? gcd(a >> 1, b) : gcd(a >> 1, b >>1) << 1
        : // a is odd
        (~b & 1) ? gcd(a, b >> 1) :
        (a > b) ? gcd((a - b) >> 1, b) : gcd((b - a) >> 1, a);
}

// least common multiple
constexpr int lcm(const int a, const int b) {
    return (a != 0 || b != 0) ? (a * b) / gcd(a, b) : 0;
}

double to_double(const Rational&);

#endif

