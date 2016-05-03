#include "../my_facilities.h"
#include <fstream>

int sum_from_file(const string &fn) {
    ifstream ifs {fn};
    if (!ifs)
        error("cannot open file " + fn);
    ifs.exceptions(ifs.exceptions() | ios_base::badbit);

    int sum {0};
    for (string s; ifs >> s;) {
        int n {0};
        bool neg {false};
        if (s[0] == '-')
            neg = true;
        for (size_t i = (s[0] == '-' || s[0] == '+'); i < s.length(); ++i)
            if (isdigit(s[i])) {
                n = n * 10 + static_cast<int>(s[i] - '0');
            } else {
                n = 0;
                break;
            }
        if (neg)
            sum -= n;
        else
            sum += n;
        if (ifs.fail()) {
            ifs.unget();
            ifs.clear(ios_base::failbit);
        }
    }
    return sum;
}

void test_sum() {
    cout << sum_from_file("give_ints.txt") << endl;
}

int main() {

    test_sum();

    return 0;
}
