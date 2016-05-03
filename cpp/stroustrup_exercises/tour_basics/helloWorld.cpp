#include <iostream>

using namespace std;

inline void keep_window_open() {
    char ch;
    cin >> ch;
}

int main() {

    cout << "Hello, World!\n";

    cout << "Please, enter a character to exit\n";
    keep_window_open();

    return 0;
}
