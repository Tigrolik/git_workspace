/* file Chrono.h
 * header for the Date class
 */

#include <iostream>

// using namespace std;

namespace Chrono {

enum class Month {
    jan=1, feb, mar, apr, may, jun, jul, aug, sep, oct, nov, dec
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

bool is_date(const int y, const Month m, const int d); // true for valid date
constexpr bool leapyear(const int y); // true if y is a leap year

bool operator==(const Date &a, const Date &b);
bool operator!=(const Date &a, const Date &b);

std::ostream &operator<<(std::ostream &os, const Date &d);
std::istream &operator>>(std::istream &is, Date &dd);

}
