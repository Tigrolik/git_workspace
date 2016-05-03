/* file Chrono.h
 * header for the Date class
 */
#ifndef _CHRONO_H_
#define _CHRONO_H_

#include <iostream>

// using namespace std;

namespace Chrono {

enum class Month {
    jan = 1, feb, mar, apr, may, jun, jul, aug, sep, oct, nov, dec
};

enum class Day {
    sunday = 0, monday, tuesday, wednesday, thursday, friday, saturday
};

class Date {
    public:
        class Invalid {};

        Date(const int y, const Month m, const int d);
        Date();
        // the default copy operations are fine

        // nonmodifying operations:
        int day() const { return d; }
        Month month() const { return m; }
        int year() const { return y; }

        // modifying operations:
        void add_day(const int n);
        void add_month(const int n);
        void add_year(const int n);

    private:
        int y;
        Month m;
        int d;
};

const Date &default_date();

bool is_date(const int y, const Month m, const int d); // true for valid date
constexpr bool leapyear(const int y); // true if y is a leap year
Day day_of_week(const Date &d);
Date next_workday(const Date &d);

bool operator==(const Date &a, const Date &b);
bool operator!=(const Date &a, const Date &b);

Day &operator++(Day &d);

std::ostream &operator<<(std::ostream &os, const Date &d);
std::istream &operator>>(std::istream &is, Date &dd);

std::ostream &operator<<(std::ostream &os, const Month &m);
std::ostream &operator<<(std::ostream &os, const Day &d);
}

#endif
