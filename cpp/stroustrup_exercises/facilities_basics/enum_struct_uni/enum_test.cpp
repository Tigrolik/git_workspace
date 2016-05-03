#include <iostream>

using namespace std;

enum Season {spring = 1, summer = 2, autumn = 4, winter = 8};

ostream &operator<<(ostream &os, const Season s) {
    switch (s) {
        case spring:
            os << "spring";
            return os;
        case summer:
            os << "summer";
            return os;
        case autumn:
            os << "autumn";
            return os;
        case winter:
            os << "winter";
            return os;
    }
    return os;
}

istream &operator>>(istream &input, Season &a) {
    string s;
    input >> s;
    if (s == "spring")
        a = spring;
    else if (s == "summer")
        a = summer;
    else if (s == "autumn")
        a = autumn;
    else if (s == "winter")
        a = winter;
    else {
        cout << "Wrong input, set season to spring\n";
        a = spring;
    }
    return input;
}

Season &operator++(Season &a) {
    if (a == winter)
        return a = spring;
    return a = static_cast<Season>(static_cast<int>(a) << 1);
}

Season &operator--(Season &a) {
    if (a == spring)
        return a = winter;
    return a = static_cast<Season>(static_cast<int>(a) >> 1);
}

void test_season() {
    const int n = 4;
    Season s_arr[n] {spring, summer, autumn, winter};

    for (auto i = 0; i < n; ++i)
        cout << --s_arr[i] << endl;
    Season s2;
    cout << "Enter a season name: ";
    cin >> s2;
    cout << s2 << endl;
}

int main()
{
    test_season();

    return 0;
}
