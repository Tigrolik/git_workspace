#include "../my_facilities.h"
#include <iostream>
#include <iomanip>
#include <vector>

using namespace std;

void test_num_out() {
    //const int x {1982};
    // hex, oct and dec are called manipulators
    //cout << showbase << x << "\t(decimal)\n" << hex << x <<
    //    "\t(hexadecimal)\n" << oct << x << "\t(octal)\n";
    //constexpr double f {12345.6789};
    //cout << setprecision(2) << f << "\t\t(defaultfloat)\n" << fixed <<
    //    f << "\tfixed\n" << scientific << f << "\tscientific\n";
    constexpr int i {123456};
    constexpr char c {'|'};
    cout << i << c << setw(4) << i << c << setw(9) << i << c << i << "|\n";
}

void test_table() {
    vector<string> names {"Joe", "Mary", "Peter", "Alex", "Kate"};
    vector<int> phones {234123, 120348, 348921, 275421, 702981};
    vector<string> emails{"Joe@here.com", "Mary@there.com",
        "Peter@nothere.com", "Alex@some.com", "Kate@where.com"};
    constexpr char c {'|'};
    cout << string(35, '-') + '\n' << setw(6) << "Name" << c << setw(8) <<
        "Ph. No" << c << setw(18) << "Email" << "|\n" << string(35, '-') + '\n';
    for (size_t i = 0; i < names.size(); ++i)
        cout << setw(6) << names[i] << c << setw(8) << phones[i] << c <<
            setw(18) << emails[i] << "|\n";
}

void test_num_in() {
    int a, b, c, d;
    cin.unsetf(ios::dec);
    cin.unsetf(ios::oct);
    cin.unsetf(ios::hex);
    cin >> a >> b >> c >> d;
    cout << a << '\t' << b << '\t' << c << '\t' << d << endl;
}

void test_string() {
    string s {"thErE yoU GO!"};
    //tolower(s);
    cout << s << endl;
}

int main() {

    //test_num_out();
    //test_num_in();
    //test_table();
    test_string();

    return 0;
}
