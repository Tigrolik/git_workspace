#include <iostream>

using namespace std;

void cm_inch() {
    constexpr double cm_per_inch {2.54};
    double length {1.0};
    char unit {' '};

    cout << "Please, enter a length followed by a unit (c or i):\n";
    cin >> length >> unit;

    switch (unit) {
        case 'i':
            cout << length << "in == " << cm_per_inch * length << "cm\n";
            break;
        case 'c':
            cout << length << "cm == " <<  length / cm_per_inch << "in\n";
            break;
        default:
            cout << "Unit unknown: " << unit << endl;
            break;
    }
}

void currency_conv() {
    constexpr double yen_per_dollar {24.72};
    constexpr double euros_per_dollar {0.85};
    constexpr double pounds_per_dollar {0.73};
    constexpr double roubles_per_dollar {71.39};

    double val {1.0};
    char currency {' '};

    cout << "Please, enter the value followed by currency (y, e, p or r):\n";
    cin >> val >> currency;

    switch (currency) {
        case 'y':
            cout << val << "yen == $" << val / yen_per_dollar << endl;
            break;
        case 'e':
            cout << val << "euro == $" << val / euros_per_dollar << endl;
            break;
        case 'p':
            cout << val << "pounds == $" << val / pounds_per_dollar << endl;
            break;
        case 'r':
            cout << val << "roubles == $" << val / roubles_per_dollar << endl;
            break;
        default:
            cout << "Currency unknown: " << currency << endl;
            break;
    }
}

int main() {

    // cm_inch();
    currency_conv();

    return 0;
}
