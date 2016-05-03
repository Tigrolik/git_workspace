#include <iostream>

void swap1(int *x, int *y) {
    int temp = *x;
    *x = *y;
    *y = temp;
}

void swap2(int &x, int &y) {
    int temp {static_cast<int&&>(x)};
    x = static_cast<int&&>(y);
    y = static_cast<int&&>(temp);
}

void swap3(int &x, int &y) {
    using namespace std;
    int tmp {move(x)};
    x = move(y);
    y = move(tmp);
}

int main()
{
    using namespace std;

    int x = 3, y = 5;
    swap1(&x, &y);
    cout << x << ' ' << y << endl;
    swap2(x, y);
    cout << x << ' ' << y << endl;
    swap3(x, y);
    cout << x << ' ' << y << endl;

    return 0;
}
