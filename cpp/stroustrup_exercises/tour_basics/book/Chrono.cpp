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
    d += n;
    while (true) {
        int f {};
        switch (m) {
            case Month::feb:
                f = leapyear(y) ? 29 : 28;
                break;
            case Month::apr: case Month::jun: case Month::sep: case Month::nov:
                f = 30;
                break;
            default:
                f = 31;
                break;
        }
        if (d > f) {
            d -= f;
            add_month(1);
        } else {
            break;
        }
    }
}

void Date::add_month(const int n) {
    int m_val = static_cast<int>(m) + n - 1;
    if (m_val >= 12)
        add_year(m_val / 12);
    m = Month(m_val % 12 + 1);
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
    return ((y % 4 == 0 && y % 100 != 0) || (y % 400 == 0));
}

bool operator==(const Date &a, const Date &b) {
    return a.year() == b.year() && a.month() == b.month() && a.day() == b.day();
}

bool operator!=(const Date &a, const Date &b) {
    return !(a == b);
}

std::ostream &operator<<(std::ostream &os, const Date &d) {
    return os << '(' << d.year() << ',' << d.month()
        << ',' << d.day() << "): " << day_of_week(d);
}

std::ostream &operator<<(std::ostream &os, const Month &m) {
    switch (m) {
        case Month::jan:
            return os << "Jan";
        case Month::feb:
            return os << "Feb";
        case Month::mar:
            return os << "Mar";
        case Month::apr:
            return os << "Apr";
        case Month::may:
            return os << "May";
        case Month::jun:
            return os << "Jun";
        case Month::jul:
            return os << "Jul";
        case Month::aug:
            return os << "Aug";
        case Month::sep:
            return os << "Sep";
        case Month::oct:
            return os << "Oct";
        case Month::nov:
            return os << "Nov";
        case Month::dec:
            return os << "Dec";
        default:
            return os << "unknown month";
    }
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

std::ostream &operator<<(std::ostream &os, const Day &d) {
    switch (d) {
        case Day::sunday:
            return os << "sunday";
        case Day::monday:
            return os << "monday";
        case Day::tuesday:
            return os << "tuesday";
        case Day::wednesday:
            return os << "wednesday";
        case Day::thursday:
            return os << "thursday";
        case Day::friday:
            return os << "friday";
        case Day::saturday:
            return os << "saturday";
        default:
            return os << "unknown day";
    }
}

Day day_of_week(const Date &d) {
    int m {static_cast<int>(d.month())}, y {d.year() - (m < 3)};
    static int t[] {0, 3, 2, 5, 0, 3, 5, 1, 4, 6, 2, 4};
    return Day((y + y / 4 - y / 100 + y / 400 + t[m - 1] + d.day()) % 7);
}

Day &operator++(Day &d) {
    d = (d == Day::saturday) ? Day::sunday : Day(static_cast<int>(d) + 1);
    return d;
}

Date next_workday(const Date &d) {
    Day wd {day_of_week(d)};
    Date nd {d};
    do {
        nd.add_day(1);
        ++wd;
    } while (wd == Day::saturday || wd == Day::sunday);
    return nd;
}

} // Chrono
