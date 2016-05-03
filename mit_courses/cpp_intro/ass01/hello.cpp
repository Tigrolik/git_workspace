#include <iostream>

using namespace std;

int main(void)
{
    int n;

    cout << "Enter a nonnegative integer: " << endl;
    cin >> n;

    const char *s = "Hello, World!";

    /*
    for (int i = 0; i < n; ++i)
        cout << s << endl;
        */

    int i = 0;
    do {
        cout << s << endl;
        ++i;
    } while (i < n);

    return 0;
}
