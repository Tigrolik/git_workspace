#include "Roman_int.h"
#include <fstream>

using namespace std;

void test_roman_strings() {
    const string fn {"literals.txt"};
    ifstream ifs {fn};
    if (!ifs) {
        cerr << "error: cannot open file " + fn << endl;
        return;
    }
    ifs.exceptions(ifs.exceptions() | ios_base::badbit);

    int k {0};
    for (Roman_int r; ifs >> r;) {
        const string s {r.roman()};
        if (is_valid_roman(s) && r.value() < 0)
            ++k;
        if (r.value() > 0)
            cout << s << ": " << uncompact(s) << endl;
        //if (r.value() > -1)
        //    cout << r << endl;
       if (ifs.fail()) {
            ifs.unget();
            ifs.clear(ios_base::failbit);
        }
    }
    ifs.close();
    cout << k << endl;

    //cout << "Enter Roman numeric string: ";
    //Roman_int r;
    //cin >> r;
    //cout << r << endl;
}

void test_int_to_roman() {
    int x {3498};
    cout << x << ": " << int_to_roman(x) << endl;
}

void test_operators() {
    Roman_int r1 {"XXVI"}, r2 {"XIX"};
    cout << r1 + r2 << endl;
    cout << r1 - r2 << endl;
    cout << r1 * r2 << endl;
    cout << r1 / r2 << endl;
    cout << r1 % r2 << endl;
}

int main() {

    //test_roman_strings();
    //test_int_to_roman();
    test_operators();

    return 0;
}
