#include <iostream>
#include <vector>

using namespace std;

template <class T, class U>
class Pair {
public:
    Pair(): t_{}, u_{} {
    }
    Pair(const T &t, const U &u): t_{t}, u_{u} {
    }
private:
    T t_;
    U u_;
};

template <class T>
ostream& operator<<(ostream &os, const vector<T> &v) {
    for (size_t i {0}; i < v.size(); ++i)
        os << v[i] << ' ';
    return os;
}

template <class T>
void f(vector<T> &v1, const vector<T> &v2) {
    for (size_t i {0}; i < min(v1.size(), v2.size()); ++i)
        v1[i] += v2[i];
}

template <class T, class U>
T acc_sum(const vector<T> vt, const vector<U> &vu) {
    T s {};
    for (size_t i {0}; i < min(vt.size(), vu.size()); ++i)
        s += vt[i] * vu[i];
    return s;
}

void test_vectors() {
    vector<int> v1 {1, 3, 7}, v2 {-4, 9, 2};
    f(v1, v2);
    cout << v1 << endl;
    const vector<double> v3 {1.5, 2.5, 3.5};
    const double d = acc_sum(v3, v2);
    cout << d << endl;
}

int main() {

    test_vectors();

    return 0;
}
