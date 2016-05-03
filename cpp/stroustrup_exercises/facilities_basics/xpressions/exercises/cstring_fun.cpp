#include <iostream>
#include <vector>
#include <chrono>
#include <cstring>

using namespace std;

inline size_t my_strlen(const char *s) {
    return (*s++) ? 1 + my_strlen(s) : 0;
}

inline void my_strcpy(char *p, const char *q) {
    while ((*p++ = *q++));
}

inline bool my_strcmp(const char *p, const char *q) {
    while (*p++)
        if (*p != *++q)
            return false;
    return true;
}

char *my_cat(const char *p, const char *q) {
    const size_t n {my_strlen(p)};
    char *s {new char[n + my_strlen(q)]};
    my_strcpy(s, p);
    my_strcpy(s + n, q);
    return s;
}

void my_rev(char *p) {
    const size_t n {my_strlen(p) - 1};
    for (size_t i = 0; i < n / 2 + 1; ++i) {
        auto t = p[i];
        p[i] = p[n - i];
        p[n - i] = t;
    }
}

void copy_ints() {
    const int a[] {-2, 3, 4, 0, 6, 9, 22};
    vector<int> b {};
    //for (const auto &x: a)
    //    if ((x > 0) && (~x & 1))
    //        b.push_back(x);
    const int *p {a};
    for (size_t i {0}; i < sizeof(a) / sizeof(int); ++i) {
        if (~*p & 1 && *p > 0)
            b.push_back(*p);
        ++p;
    }
    for (const auto &x: b)
        cout << x << ' ';
    cout << endl;
}

void test_strings() {
    using namespace std::chrono;
    const char *s = "Hello, there";
    constexpr size_t reps {1000000};

    // testing string length functions
    auto t0 = high_resolution_clock::now();
    for (size_t i {0}; i < reps; ++i)
        my_strlen(s);
    cout << "String length function: my_strlen(): " <<
        duration_cast<milliseconds>(high_resolution_clock::now() - t0).count()
        << "msec\n";

    t0 = high_resolution_clock::now();
    size_t j {strlen(s)};
    for (size_t i {0}; i < reps; ++i)
        j = strlen(s);
    cout << "String length function (from cstring): strlen(): " <<
        duration_cast<milliseconds>(high_resolution_clock::now() - t0).count()
        << "msec\n";
    cout << j << endl;

    // testing string copy functions
    char t[j];
    t0 = high_resolution_clock::now();
    for (size_t i {0}; i < reps; ++i)
        my_strcpy(t, s);
    cout << "String copy function: my_strcpy(): " <<
        duration_cast<milliseconds>(high_resolution_clock::now() - t0).count()
        << "msec\n";

    t0 = high_resolution_clock::now();
    for (size_t i {0}; i < reps; ++i)
        strcpy(t, s);
    cout << "String copy function (from cstring): strcpy(): " <<
        duration_cast<milliseconds>(high_resolution_clock::now() - t0).count()
        << "msec\n";

    //my_strcpy(t, s);
    //cout << t << endl;
    //cout << my_strcmp(s, t) << ' ' << my_strcmp(s, "Hello, theree") <<
    //    ' ' << my_strcmp(s, "Hello") << endl;
    //char *p {my_cat(s, t)};
    //cout << p << endl;
    //my_rev(p);
    //cout << p << endl;
}

int main() {

    test_strings();
    //copy_ints();

    return 0;
}
