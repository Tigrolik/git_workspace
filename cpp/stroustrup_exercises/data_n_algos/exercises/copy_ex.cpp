#include <iostream>
#include <vector>
#include <list>
#include <algorithm>
#include <random>
#include <chrono>

using namespace std;

template <class Iter>
void iter_print(Iter f1, Iter e1) {
    while (f1 != e1)
        cout << *f1++ << ' ';
    cout << '\n';
}

vector<double> copy_list(const list<int> &li) {
    vector<double> vd;
    for (const auto &x: li)
        vd.push_back(x);
    return vd;
}

void test_copy() {
    constexpr size_t n {10};
    list<int> li;
    for (auto i = n; i--; li.push_front(i % 4)) { }
    iter_print(begin(li), end(li));
    vector<double> vd {copy_list(li)};
    sort(begin(vd), end(vd));
    iter_print(begin(vd), end(vd));
}

template <class C, class T>
void my_ins(C &c, const T& val) {
    auto first = begin(c);
    while (first != end(c))
        if (*first > val)
            break;
        else
            ++first;
    c.insert(first, val);
}

void test_random() {
    constexpr size_t N {10000};
    random_device rd;
    mt19937 gen(rd());
    uniform_int_distribution<> dis(0, N - 1);

    using namespace std::chrono;

    cout << "number of elements: " << N << '\n';
    auto t = high_resolution_clock::now();
    vector<int> vi;
    for (size_t i = 0; i < N; ++i)
        my_ins(vi, dis(gen));
    cout << "vector time: " << duration<double>(
            high_resolution_clock::now() - t).count() << " seconds\n";

    t = high_resolution_clock::now();
    list<int> li;
    for (size_t i = 0; i < N; ++i)
        my_ins(li, dis(gen));
    cout << "list time: " << duration<double>(
            high_resolution_clock::now() - t).count() << " seconds\n";

    //iter_print(begin(vi), end(vi));
    //iter_print(begin(li), end(li));
}

int main() {

    //test_copy();
    test_random();

    return 0;
}

