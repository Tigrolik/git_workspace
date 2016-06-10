#ifndef DATE_H
#define DATE_H

#include <fstream>

namespace Chrono {

enum class Month {
    jan = 1, feb, mar, apr, may, jun, jul, aug, sep, oct, nov, dec
};

class Date {
public:
    class Bad_date { }; // exception class

    explicit Date(const int = {}, const Month = {}, const int = {});
    //virtual ~Date();

    // non-modifying functions
    int day() const { return d_; }
    Month month() const {return m_; };
    int year() const {return y_; };

    std::string string_res() const; // string representation
    void char_rep(char *s, const int max) const; // C-style string

    // modifying functions
    Date& add_year(const int);
    Date& add_month(const int);
    Date& add_day(const int);

private:
    bool is_valid() const;
    int d_, y_; // representation
    Month m_;
    //mutable bool cache_valid;
    //mutable std::string cache;
    //void compute_cache_value() const; // fill (mutable) cache
}; // end of class Date

bool is_date(const int, const Month, const int); // true for valid date

constexpr bool is_leapyear(const int y) {
    return ((y % 4 == 0 && y % 100 != 0) || (y % 400 == 0));
}

bool operator==(const Date&, const Date&);
bool operator!=(const Date&, const Date&);

const Date& default_date();

std::ostream& operator<<(std::ostream&, const Date&);
std::istream& operator>>(std::istream&, Date&);

} // end of namespace Chrono

#endif
