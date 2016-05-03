#include "Money.h"

Money::Money(const double d): cents_{static_cast<long int>(d * 100 + 0.5)} {
    if (d < 0) {
        std::cerr << "error: negative amount of money\n";
        throw Invalid{};
    }
}

Money::Money(const Money &m): cents_{m.cents()} {}

Money &Money::operator=(const Money &m) {
    if (this == &m)
        return *this;
    cents_ = m.cents();
    return *this;
}

std::ostream &operator<<(std::ostream &os, Money const &m) {
    const long int d {m.cents() / 100}, c {m.cents() % 100};
    os << '$' << d << '.' << c;
    return (c) ? os : os << '0';
}

std::istream &operator>>(std::istream &is, Money &m) {
    char c;
    double d;
    is >> c >> d;
    if (!is)
        return is;
    if (c != '$') {
        is.clear(std::ios_base::failbit);
        return is;
    }
    m = Money{d};
    return is;
}
