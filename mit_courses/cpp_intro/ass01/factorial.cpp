#include <iostream>

using namespace std;

int main()
{
    short number;
    cout << "Enter a number: ";
    cin >> number;

    if (number < 0) {
        cout << "Negative numbers are not allowed!\n";
        return 1;
    }

    if (number > 20)
        cout << "The program may produce inaccurate result\n";

    cout << "The factorial of " << number << " is ";

    long long acc = 1;
    for(; number > 0; acc *= number--);
    cout << acc << ".\n";

    return 0;
}
