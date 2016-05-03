#include <iostream>
#include <vector>
#include <limits>

void show_chars(const char first, const int num) {
    using namespace std;

    for (auto i = 0; i < num; ++i) {
        auto t = first + i;
        cout << '\'' << static_cast<char>(t) << '\'' << " = "
            << dec << t << ' ' << hex << t << ' ';
    }
    cout << dec;
    // remove last space and add new line
    cout << '\b' << endl;
}

int main()
{
    using namespace std;

    show_chars('a', 26);
    show_chars('0', 10);

    for (auto i : {4, 5, 9, 17, 12})
        cout << i << ' ';
    cout << '\b' << endl;

    return 0;
}
