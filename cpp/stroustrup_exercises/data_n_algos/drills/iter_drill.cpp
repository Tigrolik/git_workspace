#include <iostream>
#include <vector>
#include <array>
#include <list>
#include <algorithm>

using namespace std;

void print(int *f, int *e) {
    while (f != e) {
        cout << *f++ << ' ';
    }
    cout << '\n';
}

void my_copy(int *f1, int *e1, int *f2) {
    while (f1 != e1) {
        *f2++ = *f1++;
    }
}

template <class C>
bool cmp_str(const C& c) {
    const string h {"Howdy"};
    for (size_t i {0}; i < max(h.length(), c.size()); ++i)
        if (c[i] < h[i])
            return -1;
        else
            return 1;
    return 0;
}

void test_containers() {
    //const char c1[] {"Hello"};
    const vector<char> c2 {'H', 'e', 'l', 'l', 'o'};
    const list<char> c3 {'H', 'e', 'l', 'l', 'o'};
    const string c4 {"Hello"};
    cout << cmp_str(c2) << ' ' << cmp_str(c4) << '\n';
}

void test_arr() {
    int f[5] = {1, 2, 3, 4, 5};
    print(f, f + 5);
    int g[6] = {7, 8, -3, 2, 78, 1};
    my_copy(f, f + 3, g);
    print(g, g + 6);

    vector<int> v {1, 2, 3, 4};
    v.at(2) += 3;
    cout << v.at(2) << '\n';
    if (v <= vector<int> {1, 2, 3, 4})
        cout << "true\n";
    else
        cout << "false\n";
}

template <class T>
void disp(const T &t) {
    for (const auto &x: t)
        cout << x << ' ';
    cout << '\n';
}

template <class T>
void incr_arr(T &t, const int val = 0) {
    for (auto &x: t)
        x += val;
}

template <class Iter1, class Iter2>
Iter2 iter_copy(Iter1 f1, Iter1 e1, Iter2 f2) {
    while (f1 != e1)
        *f2++ = *f1++;
    return f2;
}

template <class Iter>
void iter_print(Iter f1, Iter e1) {
    while (f1 != e1)
        cout << *f1++ << ' ';
    cout << '\n';
}

template <class Iter>
void check_element(Iter f, Iter e, const int val) {
    auto t = std::find(f, e, val);
    if (t != e)
        cout << "contains " << val << ", index " << std::distance(f, t) << '\n';
    else
        cout << "does not contain " << val << '\n';
}

void test_arrays() {
    constexpr size_t n {10};
    int ai1[n]; // array of ints
    vector<int> av1(n); // vector
    list<int> al1; // list
    array<int, n> aa1; // std::array
    for (auto i = n; i--; ai1[i] = i, av1[i] = i, al1.push_front(i), aa1[i] = i)
    { }
    disp(ai1); disp(av1); disp(al1); disp(aa1);
    int ai2[n]; for (auto i = n; i--; ai2[i] = ai1[i]);
    vector<int> av2 {av1};
    list<int> al2 {al1};
    array<int, n> aa2 = aa1;
    incr_arr(ai2, 3); incr_arr(av2, 5); incr_arr(al2, 7); incr_arr(aa2, 9);
    disp(ai2), disp(av2), disp(al2); disp(aa2);
    int ai3[n];
    iter_copy(begin(av2), end(av2), begin(ai3)); // copy vector to int array
    vector<int> av3(n);
    iter_copy(begin(ai2), end(ai2), begin(av3)); // copy int array to vector
    array<int, n> aa3;
    iter_copy(begin(al2), end(al2), begin(aa3)); // copy list to std::array
    list<int> al3(n);
    iter_copy(begin(ai2), end(ai2), begin(al3)); // copy int array to list
    iter_print(begin(ai3), end(ai3));
    check_element(begin(ai3), end(ai3), 3);
    iter_print(begin(av3), end(av3));
    check_element(begin(av3), end(av3), 3);
    iter_print(begin(aa3), end(aa3));
    check_element(begin(aa3), end(aa3), 13);
    iter_print(begin(al3), end(al3));
    check_element(begin(al3), end(al3), 12);
}

int main() {

    //test_arr();
    //test_containers();
    //for (size_t i {5}; i-- ;cout << i << ' ') { }
    //cout << '\n';
    test_arrays();

    return 0;
}
