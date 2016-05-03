#include <iostream>

using namespace std;

void error(const string &s) {
    cerr << "error: " << s << endl;
    exit(1);
}

constexpr unsigned long long factorial(const unsigned int n) {
    return ((n == 0) || (n == 1)) ? 1 : n * factorial(n - 1);
}

unsigned long long factorial_forloop(const unsigned int n) {
    unsigned long long res {1};
    for (unsigned int i = 2; i <= n; ++i)
        res *= i;
    return res;
}

int num_of_perms(const unsigned int a, const unsigned int b) {
    if (a < b)
        error("The first value should be bigger");

    // return factorial(a) / factorial(a - b);

    // to avoid too big numbers in factorials we can reduce the number of
    // operations: P(a, b) = a! / (a - b)! = (a - b + 1) * ... (a - 1) * a
    unsigned int res {1};
    for (auto i = a - b + 1; i <= a; ++i)
        res *= i;
    return res;
}

int num_of_combs(const unsigned int a, const unsigned int b) {
    if (a < b)
        error("The first value should be bigger");

    // return factorial(a) / (factorial(a - b) * factorial(b));

    unsigned int res {1};
    const unsigned int b_fix = (b > a - b) ? a - b : b;

    // instead of computing factorials do the following:
    // C(a, b) = a! / ( (a - b)! * b! ) = [a * (a - 1) * ... * 1] /
    // [ ( (a - b) * (a - b - 1) * ... * 1) * (b * (b - 1) * ... * 1) ] =
    // [a * (a - 1) * ... * (a - b + 1)] / [b * (b - 1) * ... * 1)]
    // we do that to avoid too big numbers in pure factorials
    for (unsigned int i = 0; i < b_fix; ++i)
        res = (res * (a - i)) / (i + 1);

    return res;
}

void perms_or_combs() {

    // handle input
    cout << "Enter to non-negative integers: a, b (a > b)\n";
    int a {}, b{};
    cin >> a >> b;

    // handle errors
    if ((a < 0) || (b < 0))
        error("Values should be non-negative");
    if (a < b)
        error("The first value should be bigger");

    // handle choice
    cout << "Choose permutations or combinations (p or c): ";
    char c {};
    cin >> c;

    // handle computations and errors
    if (c == 'p')
        cout << "Number of permutations: P(" << a << ", " << b << ") = " <<
            num_of_perms(a, b) << endl;
    else if (c == 'c')
        cout << "Number of combinations: C(" << a << ", " << b << ") = " <<
            num_of_combs(a, b) << endl;
    else
        error("Invalid choice");
}

int main() {

    cout << num_of_perms(5, 3) << endl;
    cout << num_of_combs(8, 5) << endl;
    cout << num_of_combs(4, 2) << endl;
    // cout << factorial_forloop(65) << endl;
    perms_or_combs();

    return 0;
}
