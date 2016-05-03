#include <iostream>

using namespace std;

char *strdup(const char *s) {
    int n {0};
    const char *p {s};
    while (*p++)
        ++n;
    char *pc = new char[n + 1];
    char *s_pc = pc;
    while ((*s_pc++ = *s++));
    *s_pc = '\0';
    return pc;
}

int my_strcmp(const char *s1, const char *s2) {
    while (*s1 || *s2) {
        if (*s1++ < *s2++)
            return -1;
        else if (*s1 > *s2)
            return 1;
    }
    return 0;
}

void test_dup() {
    const char *s {"Hello"};
    char *cp = strdup(s);
    cout << cp << endl;
    cout << my_strcmp(s, cp) << endl;
    cout << my_strcmp(s, "hello") << endl;
    cout << my_strcmp("hell", "hello") << endl;
    cout << my_strcmp("helloy", "hello") << endl;
    cout << my_strcmp("how are you?", "how is yours?") << endl;
}

int main() {

    test_dup();

    return 0;
}
