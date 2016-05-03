/*
 * class Money from Stroustrup book exercises (part 9)
 * Design and implement a Money class
 * Represent a monetary amount as a number of cents in a long int
 * but input and output as dollars and cents, e.g., $123.45.
 * Refine the Money class by adding a currency (given as a constructor argument)
 */

#ifndef _MONEY_H_
#define _MONEY_H_

#include <iostream>
#include <algorithm>

class Money {
    public:
        class Invalid { };
        // arg1 = dollars, arg2 = cents
        Money(const double = 0);
        Money(const Money&);
        Money &operator=(const Money&);

        long int cents() const { return cents_; } // return sum in cents

        Money operator+(const Money&);
        Money operator-(const Money&);
        Money operator*(const Money&);
        Money operator/(const Money&);

        friend std::ostream &operator<<(std::ostream&, Money const&);
        friend std::istream &operator>>(std::istream&, Money&);

    private:
        long int cents_;
};

#endif

