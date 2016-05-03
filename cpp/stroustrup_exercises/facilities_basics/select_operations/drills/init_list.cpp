#include <iostream>
#include <vector>
#include <algorithm>

using namespace std;

void test_init_list() {
    initializer_list<int> lst {1, 2, 3};
    cout << *lst.begin() << endl;
}

void print_modulo(const vector<int> &v, ostream &os, int m) {
    auto Mod_print = [&os, m](const int x){ if (!(x % m)) os << x << ' '; };
    for_each(begin(v), end(v), Mod_print);
    os << endl;
}

template <class C>
void print_mod(const C &v, ostream &os, int m) {
    for (const auto &x: v)
        if (!(x % m))
            os << x << ' ';
    os << endl;
}

void sort(vector<int> &v) {
    sort(v.begin(), v.end());
}

void sort_abs(vector<int> &v) {
    auto Sort_abs = [](const int x, const int y) { return abs(x) < abs(y); };
    sort(v.begin(), v.end(), Sort_abs);
}

void rev_str(string &s1) {
    // define a lambda
    function<void(char *b, char *e)> rev = [&](char *b, char *e) {
        if (e - b > 1) { swap(*b, *--e); rev(++b, e); } };
    rev(&s1[0], &s1[0] + s1.size());
}

void test_lambda() {
    vector<int> w {1, 2, -6, 5, 7, -3, -9, 11, 12};
    sort_abs(w);
    print_mod(w, cout, 1);
    //const vector<int> v {1, 2, 6, 5, 7, 3, 9, 11, 12};
    //print_modulo(v, cout, 3);
    //print_mod(v, cout, 3);
    string s1 {"hello, string"};
    string s2 {"Greetings, my friend"};
    rev_str(s1);
    rev_str(s2);
    cout << s1 << endl << s2 << endl;
}

int main() {

    test_lambda();
    //test_init_list();

    return 0;
}
