#include <iostream>

using namespace std;

void error(const string &s) {
    cerr << "error: " << s << endl;
    exit(1);
}

string str_unit(const string &unit, const char a) {
    if (a != '1')
        return unit + "s";
    return unit;
}

void disp_number(const string &s) {
    cout << s << " is ";
    size_t n {s.size()};
    for (int i = n; i > 0; --i) {
        const int j = n - i;
        switch (i - 1) {
            case 3:
                cout << s[j] << ' ' << str_unit("thousand", s[j]) << " and ";
                break;
            case 2:
                cout << s[j] << ' ' << str_unit("hundred", s[j]) << " and ";
                break;
            case 1:
                cout << s[j] << ' ' << str_unit("ten", s[j]) << " and ";
                break;
            case 0:
                cout << s[j] << ' ' << str_unit("one", s[j]);
                break;
        }
    }
    cout << endl;
}

void char_to_int() {
    const char zero_ch {'0'};
    string s {};
    cout << "Enter an int (digits with no spaces:) ";
    cin >> s;

    const size_t len {s.size()};
    int x {0};
    for (size_t i = 0; i < len; ++i) {
        const int temp = s[i] - zero_ch;
        if ((temp < 0) || (temp > 9))
            error("some character is not a digit");
        x = x * 10 + temp;
    }

    disp_number(s);
}

int main() {

    char_to_int();

    return 0;
}
