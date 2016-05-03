#include <iostream>

using namespace std;

int stringLength(const char *s)
{
    int n = 0;
    while (*(s + n) != '\0')
        ++n;
    return n;
}

void swap_int(int **x, int **y)
{
    int *temp = *x;
    *x = *y;
    *y = temp;
}

int main()
{
    const char *s = "new string";

    cout << "String length: " << stringLength(s) << endl;
    cout << "String length: " << stringLength("") << endl;
    cout << "String length: " << stringLength("a") << endl;

    int x = 5, y = 6;
    int *ptr1 = &x, *ptr2 = &y;
    swap_int(&ptr1, &ptr2);
    cout << *ptr1 << ' ' << *ptr2 << endl;

    char oddOrEven[20] = "Never odd or even";
    char *nthCharPtr = &oddOrEven[5];

    nthCharPtr -= 2;

    cout << *nthCharPtr << endl;

    char **pointerPtr = &nthCharPtr;
    cout << **pointerPtr << endl;

    ++nthCharPtr;
    cout << nthCharPtr << endl;

    cout << nthCharPtr - oddOrEven << endl;

    return 0;
}
