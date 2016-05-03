#include <iostream>
#include <vector>

using namespace std;

// put a C-string to lower case
void to_lower(char *s) {
    constexpr char A_code {'A'}, Z_code {'Z'}, aA_diff {'a' - A_code};
    if (*s)
        do {
            if (*s >= A_code && *s <= Z_code)
                *s += aA_diff;
        } while (*++s);
}

int my_strlen(const char *s) {
    int n {0};
    while(*s++) ++n;
    return n;
}

// copy C-string (warning: has some leaking issues)
char* strdup(const char *s) {
    const int n {my_strlen(s)};
    char *p = new char[n + 1];
    for (int i {0}; i < n; ++i)
        p[i] = s[i];
    p[n] = '\0';
    return p;
}

// find the first occurence of C-style string x in C-style string s
const char* findx(const char *s, const char *x) {
    const int n1 {my_strlen(s)}, n2 {my_strlen(x)};
    for (int i {0}; i < n1; ++i) {
        if (s[i] == x[0])
            for (int j {1}; j < n2; ++j) {
                if (s[i + j] != x[j])
                    break;
                if (x[j + 1] == '\0')
                    return &s[i];
                if (s[i + j + 1] == '\0')
                    return '\0';
            }
    }
    return '\0';
}

char* incr_cstr(const char *s) {
    const int n {my_strlen(s)};
    char *pc = new char[n + 2];
    for (int i {0}; i < n; ++i)
        pc[i] = s[i];
    pc[n] = '\0';
    return pc;
}

void read_from_cin() {
    cout << "enter chars:\n";
    char c;
    int i {1};
    char *pc = new char[i];
    *pc = '\0';
    while (cin >> c && c != '!') {
        pc[i - 1] = c;
        pc = incr_cstr(pc);
        pc[i++] = '\0';
    }
    cout << pc << endl;
    delete [] pc;
}

void test_tolower() {
    char s[] = "HElLo TheRE, mY Friend!";
    //char s[] = "\0";
    cout << s << endl;
    to_lower(s);
    cout << s << endl;
}

void test_duplicate() {
    const char *s1 {"Hello, there"};
    char *s2 = strdup(s1);
    cout << s1 << ": " << my_strlen(s1) << '\n' << s2  <<
        ": " << my_strlen(s2) << endl;
    delete s2;
}

void test_findx() {
    //const char *s1 {"Hello, there"}, *s2 {"there"};
    const char *s1 {"Hello, there"}, *s2 {"ell"};
    const char *s = findx(s1, s2);
    cout << s << endl;
}

int main() {

    //test_tolower();
    //test_duplicate();
    //test_findx();
    read_from_cin();

    return 0;
}
