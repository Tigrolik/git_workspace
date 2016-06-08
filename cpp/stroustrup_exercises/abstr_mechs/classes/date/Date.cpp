#include "Date.h"

namespace Chrono {

/*
 * ------- Date implementation -------
 */
Date::Date(const int d, const Month m, const int y): d_{d}, y_{y}, m_{m} {
    if (y_ == 0)
        y_ = default_date().year();
    if (m_ == Month{})
        m_ = default_date().month();
    if (d_ == 0)
        d_ = default_date().day();
    if (!is_valid())
        throw Bad_date{};
}

Date& Date::add_day(const int n) {
    if (n == 0)
        return *this;
    d_ += n;
    while (true) {
        int f {31};
        switch (m_) {
            case Month::feb:
                f = is_leapyear(y_) ? 29 : 28;
                break;
            case Month::apr: case Month::jun: case Month::sep: case Month::nov:
                f = 30;
                break;
            case Month::jan: case Month::mar: case Month::may: case Month::jul:
            case Month::aug: case Month::oct: case Month::dec: default:
                break;
        }
        if (d_ > f) {
            d_ -= f;
            *this = add_month(1);
        } else {
            break;
        }
    }
    return *this;
}

Date& Date::add_month(const int n) {
    if (n == 0)
        return *this;
    int m_val = static_cast<int>(m_) + n - 1;
    if (m_val >= 12)
        *this = add_year(m_val / 12);
    m_ = Month(m_val % 12 + 1);
    return *this;
}

Date& Date::add_year(const int n) {
    if (n == 0)
        return *this;
    if (m_ == Month::feb && d_ == 29 && !is_leapyear(y_ + n)) {
        m_ = Month::mar;
        d_ = 1;
    }
    y_ += n;
    return *this;
}

bool Date::is_valid() const {
    return is_date(d_, m_, y_);
}

bool is_date(const int d, const Month m, const int y) {
    if (d < 1)
        return false;
    // assume that y is valid
    int days_in_month {31};

    switch (m) {
        case Month::feb:
            days_in_month = (is_leapyear(y)) ? 29 : 28;
            break;
        case Month::apr: case Month::jun: case Month::sep: case Month::nov:
            days_in_month = 30;
            break;
        case Month::jan: case Month::mar: case Month::may: case Month::jul:
        case Month::aug: case Month::oct: case Month::dec:
            break;
        default:
            return false;
    }

    return d <= days_in_month;
}

bool operator==(const Date& a, const Date& b) {
    return a.day() == b.day() && a.month() == b.month() && a.year() == b.year();
}

bool operator!=(const Date& a, const Date& b) {
    return !(a == b);
}

const Date& default_date() {
    static Date d {1, Month::jan, 1970};
    return d;
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

std::ostream& operator<<(std::ostream& os, const Date& d) {
    return os << '(' << d.year() << ',' << d.month() << ',' << d.day() << ')';
}

std::istream& operator>>(std::istream& is, Date& dd) {
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

    return is;
}

} // Chrono namespace
