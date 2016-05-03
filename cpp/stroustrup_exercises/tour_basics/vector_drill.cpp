#include <iostream>
#include <vector>
#include <algorithm>
#include <limits>

using namespace std;

void dict() {

    vector<string> disliked {"broccoli", "man", "plan"};
    sort(disliked.begin(), disliked.end());

    vector<string> words {};
    for (string temp; cin >> temp;)
        words.push_back(temp);
    cout << "Number of words: " << words.size() << endl;

    sort(words.begin(), words.end());
    for (unsigned int i = 0; i < words.size(); ++i) {
        if (i == 0 || words[i - 1] != words[i]) {
            bool goodword {true};
            for (unsigned int j = 0; j < disliked.size(); ++j)
                if (words[i] == disliked[j]) {
                    goodword = false;
                    cout << "BLEEP ";
                    break;
                }
            if (goodword)
                cout << words[i] << ' ';
        }
    }
    cout << "\b\n";
}

void looping() {
    double min_val {numeric_limits<double>::max()};
    double max_val {numeric_limits<double>::min()};
    constexpr int ft_to_inch {12};
    constexpr double inch_to_cm {2.54}, cm_to_m {0.01};
    double sum {0.0}; // keep track of the sum in meters
    int num_of_values {0};
    vector<double> values {};

    double d {};
    string unit {""};
    while (cin >> d >> unit) {
        double curr_val {};

        if (unit == "m" || unit == " m")
            curr_val = d;
        else if (unit == "cm" || unit == " cm")
            curr_val = d * cm_to_m;
        else if (unit == "in" || unit == " in")
            curr_val = d * inch_to_cm * cm_to_m;
        else if (unit == "ft" || unit == " ft")
            curr_val = d * ft_to_inch * inch_to_cm * cm_to_m;
        else {
            cout << "Illegal unit\n";
            continue;
        }

        values.push_back(curr_val);
        ++num_of_values;

        if (curr_val < min_val)
            min_val = curr_val;
        if (curr_val > max_val)
            max_val = curr_val;

        sum += curr_val;
    }
    sort(values.begin(), values.end());
    cout << "The entered values (in meters):";
    for (auto v : values)
        cout << ' ' << v;
    cout << "\nThe number of values given: " << num_of_values <<
        "; sum: " << sum << "m; the smallest value: " << min_val <<
        "m; the largest value: " << max_val << "m\n";
}

void median_fix() {
    vector<double> temps;
    for (double temp; cin >> temp;)
        temps.push_back(temp);

    double sum {0.0};
    for (auto x : temps)
        sum += x;

    const int len = temps.size();
    cout << "Average temperature: " << sum / len << endl;

    sort(temps.begin(), temps.end());

    cout << "Median: ";
    const int mid_idx = len / 2;
    if (len % 2)
        cout << temps[mid_idx] << endl;
    else
        cout << 0.5 * (temps[mid_idx - 1] + temps[mid_idx]) << endl;
}

int main() {

    //dict();
    //looping();
    median_fix();

    return 0;
}
