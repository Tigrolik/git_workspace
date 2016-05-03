#include<iostream>

using namespace std;

int sum(const int a, const int b, const int c = 0, const int d = 0) {
    return a + b + c + d;
}

int sum(const int n, const int a[]) {
    return n == 0 ? 0 : a[0] + sum(n - 1, a + 1);
}

double sum(const double a, const double b) {
    return a + b;
}
int main()
{
    int a = 3, b = 4;
    double x = 3.2, y = 7.9;

    cout << sum(a, b, 6) << endl;
    cout << sum(x, y) << endl;

    int arr[] = {1, 2, 3, 4, 5, 6, 7};
    cout << sum(7, arr) << endl;

    return 0;
}

