#include <iostream>
#include <vector>
#include <algorithm>
#include <iterator>
#include <thread>
#include <mutex>
#include <chrono>
#include <future>

using namespace std;

mutex m;

void f() {
}

struct F {
    void operator()();
};

void foo(const string s) {
    //auto t1 = chrono::high_resolution_clock::now();
    this_thread::sleep_for(chrono::milliseconds{1000});
    unique_lock<mutex> lck{m, defer_lock};
    cout << s;
}

void bar(const string s) {
    this_thread::sleep_for(chrono::milliseconds{1000});
    unique_lock<mutex> lck{m, defer_lock};
    cout << s;
}

void user() {

    thread t1 {bar, "hello\n"}; // f() executes in a separate thread
    thread t2 {foo, "world\n"}; // F()() executes in a separate thread

    t1.join(); // wait for t1
    t2.join(); // wait for t2
}

double accum(const double *beg, const double *end, const double init) {
    return accumulate(beg, end, init);
}

double comp4(const vector<double> &v) {
    const double in = 0.0;
    if (v.size() < 1000000)
        return accumulate(v.begin(), v.end(), in);
    auto v0 = &v[0];
    auto sz = v.size();
    auto f0 = async(accum, v0, v0 + sz / 4, in);
    auto f1 = async(accum, v0 + sz / 4, v0 + sz / 2, in);
    auto f2 = async(accum, v0 + sz / 2, v0 + sz *3 / 4, in);
    auto f3 = async(accum, v0 + sz * 3 / 4, v0 + sz, in);
    return f0.get() + f1.get() + f2.get() + f3.get();
}

int main()
{
    //auto t1 = chrono::high_resolution_clock::now();
    //for (auto i = 0; i < 3; ++i) {
    //    this_thread::sleep_for(chrono::seconds{1});
    //    cout << chrono::duration_cast<chrono::seconds>
    //        (chrono::high_resolution_clock::now() - t1).count() <<
    //        " seconds passed\n";
    //    user();
    //}
    //thread t1(foo);
    //thread t2(bar);
    //t1.join();
    //t2.join();
    //auto n = 1000000;
    //vector<double> v(n);
    //for(auto i = 0; i < n; ++i)
    //    v[i] = i / 3.0 * 2;
    //cout << comp4(v) << endl;

    cout << is_arithmetic<string>() << endl;

    return 0;
}

