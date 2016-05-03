#include <iostream>
#include <vector>

void print_day_info(const std::vector<int> v, const std::string day) {
    using namespace std;
    cout << "Values for " << day << ":";
    int sum {0};
    for (auto x : v) {
        cout << ' ' << x;
        sum += x;
    }
    cout << " and their sum: " << sum << endl;
}

void read_pairs() {
    using namespace std;
    string day {};
    int val {}, num_of_rejects {0};
    vector<int> mon {}, tue {}, wed {}, thu {}, fri {}, sat {}, sun {};
    while (cin >> day >> val) {
        if (day == "Monday" || day == "Mon" || day == "monday")
            mon.push_back(val);
        else if (day == "Tuesday" || day == "Tue" || day == "tuesday")
            tue.push_back(val);
        else if (day == "Wednesday" || day == "Wed" || day == "wednesday")
            wed.push_back(val);
        else if (day == "Thursday" || day == "Thu" || day == "thursday")
            thu.push_back(val);
        else if (day == "Friday" || day == "Fri" || day == "friday")
            fri.push_back(val);
        else if (day == "Saturday" || day == "Sat" || day == "saturday")
            sat.push_back(val);
        else if (day == "Sunday" || day == "Sun" || day == "sunday")
            sun.push_back(val);
        else
            ++num_of_rejects;
    }

    print_day_info(mon, "monday");
    print_day_info(tue, "tuesday");
    print_day_info(wed, "wednesday");
    print_day_info(thu, "thursday");
    print_day_info(fri, "friday");
    print_day_info(sat, "saturday");
    print_day_info(sun, "sunday");
    cout << "Number of rejected values: " << num_of_rejects << endl;
}

int main() {

    read_pairs();

    return 0;
}
