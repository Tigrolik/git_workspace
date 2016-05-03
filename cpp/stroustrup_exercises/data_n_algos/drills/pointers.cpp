#include <iostream>

using namespace std;

double* calc(const int res_size, const int max_val) {
    double *p = new double[max_val];
    double *res = new double [res_size];

    for (int i {0}; i < res_size; ++i)
        res[i] = i * i;

    delete [] p;
    return res;
}

constexpr int my_strlen(const char *s) {
    return (*s) ? 1 + my_strlen(++s) : 0;
}

char* strdup(const char *s) {
    if (*s == '\0')
        return '\0';
    const int n {my_strlen(s)};
    cout << n << endl;
    char *res = new char[n + 1];
    //for (int i {0}; i < n; ++i)
    for (int i {0}; s[i]; ++i)
        res[i] = s[i];
    res[n] = 0;
    delete [] s;
    return res;
}

void test_int() {
    double *r = calc(10, 1000);
    for (int i {0}; i < 10; ++i)
        cout << r[i] << ' ';
    cout << endl;

    delete [] r;
}

void test_str() {
    const char *s {"Hello"};
    char *cp = strdup(&s[0]);
    cout << cp << ' ' << my_strlen(cp) << endl;
    delete [] cp;
}

int main() {

    //test_int();
    test_str();

    return 0;
}
