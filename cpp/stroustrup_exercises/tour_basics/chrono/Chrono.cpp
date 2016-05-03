#include "Chrono.h"

namespace Chrono {
// member functions definitions:

Date::Date(const int yy, const Month mm, const int dd): y{yy}, m{mm}, d{dd} {
    if (!is_date(yy, mm, dd))
            throw Invalid{};
}

const Date &default_date() {
    static Date dd {2001, Month::jan, 1};
    return dd;
}

Date::Date(): y{default_date().year()}, m{default_date().month()},
    d{default_date().day()} {
    }

void Date::add_day(const int n) {
    // ...
    d += n;
}

void Date::add_month(const int n) {
    m = static_cast<Month>(static_cast<int>(m) + n);
}

void Date::add_year(const int n) {
    if (m == Month::feb && d == 29 && !leapyear(y + n)) {
        m = Month::mar;
        d = 1;
    }
    y += n;
}

// helper functions:

bool is_date(const int y, const Month m, const int d) {
    // assume that y is valid
    if (d <= 0)
        return false;
    if (m < Month::jan || m > Month::dec)
        return false;

    int days_in_month {31};

    switch (m) {
        case Month::feb:
            days_in_month = (leapyear(y)) ? 29 : 28;
            break;
        case Month::apr: case Month::jun: case Month::sep: case Month::nov:
            days_in_month = 30;
            break;
        default:
            break;
    }

    if (days_in_month < d)
        return false;

    return true;
}

constexpr bool leapyear(const int y) {
    return (y > 1000) ? true : false;
    // ex10
}

bool operator==(const Date &a, const Date &b) {
    return a.year() == b.year() && a.month() == b.month() && a.day() == b.day();
}

bool operator!=(const Date &a, const Date &b) {
    return !(a == b);
}

std::ostream &operator<<(std::ostream &os, const Date &d) {
    return os << '(' << d.year() << ',' << static_cast<int>(d.month())
        << ',' << d.day() << ')';
}

std::istream &operator>>(std::istream &is, Date &dd) {
    int y, m, d;
    char ch1, ch2, ch3, ch4;
    is >> ch1 >> y >> ch2 >> m >> ch3 >> d >> ch4;
    if (!is)
        return is;
    if (ch1 != '(' || ch2 != ',' || ch3 != ',' || ch4 != ')') {
        is.clear(std::ios_base::failbit);
        return is;
    }

    dd = Date{y, Month(m), d};
    //dd {Date{y, Month {m}, d}};

    return is;
}

enum class Day {
    sunday, monday, tuesday, wednesday, thursday, friday, saturday
};

//Day day_of_week(const Date &d) {
//    // ...
//}

} // Chrono
