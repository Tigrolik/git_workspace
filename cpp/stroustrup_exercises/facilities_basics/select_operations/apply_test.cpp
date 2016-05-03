#include <iostream>
#include <algorithm>
#include <vector>
#include <random>
#include <chrono>

using namespace std;

template <typename T>
ostream &operator<<(ostream &os, const vector<T> &v) {
    for (const auto &x: v)
        os << x << ' ';
    return os;
}

class Funk {
    public:
        Funk(const int x = 0): x_{x} { }
        void operator()(int&y) { y *= y; }
    private:
        int x_;
};

function<void(int &x)> sqr_lam = [](int &x){ x *= x; };

void sqr_fun(int &x) {
    x *= x;
}

void apply(vector<int> &v, function<void(int&)> f) {
    for_each(v.begin(), v.end(), f);
}

void test_apply() {
    vector<int> v {-1, 0, 1, 2, 3, 7, 9, 12};
    apply(v, sqr_fun); cout << v << endl;
    apply(v, sqr_lam); cout << v << endl;
    apply(v, Funk {}); cout << v << endl;
}

int main() {

    test_apply();

    return 0;
}
