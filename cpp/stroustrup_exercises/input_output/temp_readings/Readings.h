#ifndef _READINGS_H_
#define _READINGS_H_

#include "../my_facilities.h"
#include <fstream>

// introduce constants
static constexpr int not_a_reading {-300}; // below the absolute zero
static constexpr int steep_min {-200};
static constexpr int steep_max {200};
static constexpr int not_a_month {-1};
static constexpr int months_in_year {12};
static constexpr int hours_in_day {24};
static constexpr int max_day_idx {32};
static constexpr char cels_char {'c'};
static constexpr char fahr_char {'f'};
static const vector<string> month_input_tbl {"jan", "feb", "mar", "apr", "may",
    "jun", "jul", "aug", "sep", "oct", "nov", "dec"};

void end_of_loop(istream &ifs, char term, const string &msg) {
    if (ifs.fail()) {
        ifs.clear();
        char ch;
        if (ifs >> ch && ch == term) // all is fine
            return;
        error(msg);
    }
}

struct Day {
    vector<double> hour {vector<double>(hours_in_day, not_a_reading)};
    vector<char> suffix {vector<char>(hours_in_day, fahr_char)};
};

struct Month {
    int month {not_a_month}; // [0:11]
    vector<Day> day {max_day_idx}; // [1:31]
    // "wasting" day[0] to keep the code simple
};

struct Year { // year of temperature readings, organized by month
    int year {}; // positive == A.D.
    vector<Month> month {months_in_year};
};

struct Reading {
    int day;
    int hour;
    double temperature;
    char suffix;
};

constexpr bool is_valid(const Reading &r) {
    //rough test
    return (r.day > 0 && r.day < max_day_idx) &&
        (r.hour >= 0 && r.hour < hours_in_day) &&
        (r.temperature > steep_min && r.temperature < steep_max) &&
        (r.suffix == cels_char || r.suffix == fahr_char);
}

int month_to_int(const string &s) {
    for (auto i = 0; i < months_in_year; ++i)
        if (month_input_tbl[i] == s)
            return i;
    return -1;
}

string int_to_month(const int i) {
    // months: [0:11]
    if (i < 0 || i >= months_in_year) {
        error("bad month index");
        return "";
    }
    return month_input_tbl[i];
}

ostream &operator<<(ostream &os, const Reading &r) {
    return os << '(' << r.day << ' ' << r.hour << ' ' << r.temperature <<
        r.suffix << ')';
}

ostream &operator<<(ostream &os, const Month &m) {
    os << "{month " << int_to_month(m.month);
    for (int i = 1; i < max_day_idx; ++i)
        for (int j = 0; j < hours_in_day; ++j){
            const Reading r {i, j, m.day[i].hour[j], m.day[i].suffix[j]};
            if (r.temperature != not_a_reading)
                os << ' ' << r;
        }
    return os << '}';
}

ostream &operator<<(ostream &os, const Year &y) {
    os << "{year " << y.year;
    for (int i = 0; i < months_in_year; ++i) {
        const Month m = y.month[i];
        if (m.month != not_a_month)
            os << ' ' << m;
    }
    return os << '}' << endl;
}

istream &operator>>(istream &is, Reading &r) {
    // format: (3 4 9.7c) c = celsius, f = fahrenheit
    // check the format but don't bother with data validity
    char ch;
    is >> ch; // do not put this inside the "if", gives a runtime error...
    if (!is || ch != '(') { // could it be a Reading?
        is.unget();
        is.clear(ios_base::failbit);
        return is;
    }

    int d, h;
    double t;
    char ch2;
    is >> d >> h >> t >> ch >> ch2;
    if (!is || (ch != cels_char && ch != fahr_char) || ch2 != ')')
        error("bad reading");
    r.day = d;
    r.hour = h;
    r.temperature = t;
    r.suffix = ch;
    return is;
}

istream &operator>>(istream &is, Month &m) {
    // format: {month feb ...}
    char ch; is >> ch;
    if (!is || ch != '{') {
        is.unget();
        is.clear(ios_base::failbit);
        return is;
    }

    string month_marker, mm;
    is >> month_marker >> mm;
    if (!is || month_marker != "month")
        error("bad start of month");
    m.month = month_to_int(mm);
    int duplicates {0}, invalids {0};
    for (Reading r; is >> r;) {
        if (is_valid(r)) {
            if (m.day[r.day].hour[r.hour] != not_a_reading)
                ++duplicates;
            m.day[r.day].hour[r.hour] = r.temperature;
            m.day[r.day].suffix[r.hour] = r.suffix;
        } else {
            ++invalids;
        }
    }
    if (invalids)
        error("invalid readings in month: " + to_string(invalids));
    if (duplicates)
        error("duplicates readings in month: " + to_string(duplicates));
    end_of_loop(is, '}', "bad end of month");
    return is;
}

istream &operator>>(istream &is, Year &y) {
    // format: {year 1972 ...}
    char ch; is >> ch;
    if (!is || ch != '{') {
        is.unget();
        is.clear(ios_base::failbit);
        return is;
    }
    string year_marker;
    int yy;
    is >> year_marker >> yy;
    if (!is || year_marker != "year")
        error("bad start of year");
    y.year = yy;
    for (Month m; is >> m;) {
        y.month[m.month] = m;
        m = Month {};
    }
    end_of_loop(is, '}', "bad end of year");
    return is;
}

constexpr double c_to_f(const double temp_cels) {
    return temp_cels * 1.8 + 32;
}

#endif

