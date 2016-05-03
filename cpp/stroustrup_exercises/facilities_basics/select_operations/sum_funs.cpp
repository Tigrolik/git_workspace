#include <iostream>
#include <algorithm>
#include <vector>
#include <random>
#include <chrono>

using namespace std;

template <typename T>
T sum_acc(const vector<T> &v) {
    return accumulate(v.begin(), v.end(), T {});
}

template <typename T>
T sum_v0(const vector<T> &v) {
    T sum {};
    for (const auto &x: v)
        sum += x;
    return sum;
}

template <typename T>
T sum_v1(const vector<T> &v) {
    T sum {};
    for (size_t i = 0; i < v.size(); ++i)
        sum += v[i];
    return sum;
}

template <typename T>
T sum_v2(const vector<T> &v) {
    T sum {};
    const T *p {&v[0]};
    for (size_t i = 0; i < v.size(); ++i, ++p)
        sum += *p;
    return sum;
}

template <typename T>
T sum_v3(const vector<T> &v) {
    T sum {};
    auto sum_lam = [&sum](const T &n){ sum += n; };
    for_each(v.begin(), v.end(), sum_lam);
    return sum;
}

template <typename T>
T sum_v4(const vector<T> &v) {
    T sum {};
    for (typename vector<T>::const_iterator it = v.begin(); it != v.end(); ++it)
        sum += *it;
    return sum;
}

template <typename T>
constexpr T sum_v5(const vector<T> &v) {
    return (v.size()) ? v[0] + sum_v5(vector<T>(v.begin() + 1, v.end())) : 0;
}

template <typename T>
T sum_v6(const vector<T> &v) {
    class Sum_v {
        public:
            Sum_v(const vector<T> &w = {}): v_{w} { }
            T operator()() { return accumulate(v_.begin(), v_.end(), T{}); }
        private:
            vector<T> v_;
    };
    return Sum_v{v}();
}

//void apply(vector<int> &v, function<void(int&)> f) {
//    for_each(v.begin(), v.end(), f);
//}

template <typename T>
void timing(T(*f)(const vector<T>&), const vector<T> &v, const string &msg) {
//void timing(function<T(const vector<T>&)> f, const vector<T> &v,
 //       const string &msg) {
    using namespace std::chrono;
    constexpr int reps {100000}; // number of repititions
    const auto t0 = high_resolution_clock::now();
    for (auto i = 0; i < reps; ++i)
        f(v);
    cout << msg << ": value = " << f(v) << ", time elapsed: " <<
        duration_cast<milliseconds>(high_resolution_clock::now() - t0).count()
        << "msec\n";
}

void test_sum_functions() {
    // random engine init
    random_device rd;
    uniform_int_distribution<int> dist(1, 9);

    // generate random vector
    constexpr int n {100}; // size of vector
    vector<int> v;
    for (auto i = 0; i < n; ++i)
        v.push_back(dist(rd));

    timing(*sum_acc<int>, v, "std::accumulate()");
    timing(*sum_v0<int>, v, "sum_v0(range-for)");
    timing(*sum_v1<int>, v, "sum_v1(for-loop)");
    timing(*sum_v2<int>, v, "sum_v2(pointers)");
    timing(*sum_v3<int>, v, "sum_v3(for_each)");
    timing(*sum_v4<int>, v, "sum_v4(iterator)");
    timing(*sum_v5<int>, v, "sum_v5(recursio)");
    timing(*sum_v6<int>, v, "sum_v6(func_obj)");
}

// function object (functor) example
class Functor {
    public:
        Functor(const vector<int> &v = {}): v_{v} { }
        int operator()() { return accumulate(v_.begin(), v_.end(), 0); }
    private:
        vector<int> v_;
};

int main() {

    //cout << Functor{vector<int>{1, 2, 5, 7}}() << endl;
    test_sum_functions();

    return 0;
}
