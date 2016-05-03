#include <iostream>

using namespace std;

inline int square(const int x) {

    int res {0};

    if (x < 0) {
        for (auto i = 0; i < -x; ++i)
            res -= x;
        return res;
    }

    for (auto i = 0; i < x; ++i)
        res += x;
    return res;
}

void letters() {
    char c {'a' - 1};
    while (++c <= 'z')
        cout << c << '\t' << static_cast<int>(c) << endl;
    for (auto s = 'A'; s <= 'Z'; ++s)
        cout << s << '\t' << static_cast<int>(s) << endl;
}

void alphabet() {
    for (auto c = 'a', s = 'A'; c <= 'z'; ++c, ++s)
        cout << c << '\t' << static_cast<int>(c) << '\t' <<
            s << '\t' << static_cast<int>(s) << endl;
}

int main() {

    // letters();
    // alphabet();

    cout << square(5) << endl;
    cout << square(-3) << endl;
    cout << square(-37) << endl;

    return 0;
}
