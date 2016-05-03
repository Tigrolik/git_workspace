#include <iostream>
#include <algorithm>

inline void error(const std::string s) {
    using namespace std;
    cerr << "Error: " << s << endl;
    exit(1);
}

double ctok(const double c) {
    using namespace std;
    constexpr double abs_zero_c {-273.15};
    if (c < abs_zero_c)
        error({"The temperature cannot be below " + to_string(abs_zero_c) +
                "\xB0" + "C"});
    return c - abs_zero_c;
}

double ktoc(const double k) {
    using namespace std;
    constexpr int abs_zero_k {0};
    constexpr double abs_zero_c {-273.15};
    if (k < abs_zero_k)
        error({"The temperature cannot be below " + to_string(abs_zero_k) +
               "K"});
    return k + abs_zero_c;
}

void quadr_eq(const double a, const double b, const double c) {
    using namespace std;
    if (a == 0) {
        if (b == 0)
            error("The equation is a constant: no roots");
        else
            cout << "The equation is linear: one root = " << -c / b << endl;
    } else {
        const double d {b * b - 4 * a * c};
        if (d < 0) {
            error("The discriminant is negative: no real roots");
        }
        const double x1 {(sqrt(d) - b) / (a * 2)},
              x2 {(-sqrt(d) - b) / (a * 2)};
        if (x1 == x2)
            cout << "The roots are equal: " << x1 << endl;
        else
            cout << "The first root = " << x1 << "; the second root = " <<
                x2 << endl;
    }
}

void sum_of_ints() {
    using namespace std;

    cout << "Please, enter the number of integer values you want to sum:\n";
    size_t n {};
    if (!(cin >> n))
        error("Not an integer");

    cout << "Please, enter several integer values (press '|' to stop)\n";
    vector<int> v {};
    int val {};
    while (cin >> val)
        v.push_back(val);

    if (n > v.size())
        error("Too little elements in the vector");

    int sum {0};
    cout << "The sum of the first " << n << " values ( ";
    for (size_t i = 0; i < n; ++i) {
        cout << v[i] << ' ';
        sum += v[i];
    }
    cout << ") is " << sum << endl;
}

void test_temp_conv() {
    using namespace std;
    double c {};
    cout << "Temperature in degree Celsius: ";
    cin >> c;
    cout << ctok(c) << "K\n";
    cout << "Temperature in degree Kelvin: ";
    cin >> c;
    cout << ktoc(c) << "\xB0" << "C\n";
}

void test_quadr_eq() {
    // quadr_eq(0, 0, 3);
    quadr_eq(0, 7, -9);
    quadr_eq(2, 0, -9);
    quadr_eq(2, 0, 0);
    quadr_eq(-2, -4, 2);
    quadr_eq(-2, 1, -2);
}

int main() {

    // test_temp_conv();
    // test_quadr_eq();
    sum_of_ints();

    return 0;
}
