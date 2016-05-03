#include "Readings.h"

void read_from_file(const string &fn) {
    ifstream ifs {fn};
    if (!ifs)
        error("cannot open file " + fn);
    ifs.exceptions(ifs.exceptions() | ios_base::badbit); // throw for bad()

    vector<Year> ys;
    for (Year y; ifs >> y;) {
        ys.push_back(y);
    }

    vector<double> temps;
    for (auto &x1: ys) { // all years
        const vector<Month> mm {x1.month};
        for (auto &x2: mm) // all months in a year
            if (x2.month != not_a_month) // skip months with no data
                // go through each day and every hour in the day
                for (int i = 1; i < max_day_idx; ++i)
                    for (int j = 0; j < hours_in_day; ++j){
                        const Reading r {i, j, x2.day[i].hour[j],
                            x2.day[i].suffix[j]};
                        const double t = r.temperature;
                        if (t != not_a_reading) {
                            if (r.suffix == cels_char)
                                temps.push_back(c_to_f(t));
                            else
                                temps.push_back(t);
                        }
                    }
    }
    cout << temps << endl;
    cout << mean(temps) << endl;
    cout << median(temps) << endl;
}

void test_reading() {
   read_from_file("raw_temps.txt");
}

int main() {
    test_reading();

    return 0;
}
