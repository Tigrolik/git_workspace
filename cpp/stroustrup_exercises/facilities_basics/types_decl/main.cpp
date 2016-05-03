#include <iostream>
#include <limits>

int main()
{
    using namespace std;

    //if (numeric_limits<unsigned char>::is_signed)
    if (numeric_limits<char>::is_signed)
        cout << "Signed characters\n";
    else
        cout << "Unsigned characters\n";

    enum INSECTS {BUTTERFLY, ANT, FLY, WASP};
    enum NUMS {ONE, TWO, THREE, FOUR, FIVE, SIX, SEVEN};
    int x;
    int *p = &x;
    char s = ' ';
    double arr[30];
    char *cp = &s;
    cout << sizeof(int) << s << sizeof(double) << s << sizeof(p) << endl;
    cout << sizeof(s) << s << sizeof(NUMS) << s << sizeof(INSECTS) << endl;
    cout << sizeof(arr) << s << sizeof(cp) << endl;
    //auto al_double = alignof(2.0);
    //cout << al_double << endl;

    return 0;
}

