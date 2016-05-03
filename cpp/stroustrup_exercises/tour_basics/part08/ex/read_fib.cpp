#include <iostream>
#include <vector>
#include <algorithm>

using namespace std;

template <typename T>
void print(const string &prefix, const vector<T> vi) {
    cout << prefix + '\n';
    for (const auto i : vi)
        cout << i << ' ';
    cout << "\b\n";
}

void fibonacci(const int x, const int y, vector<int> &v, const int n) {
    v.push_back(x), v.push_back(y);
    for (int i = 2; i < n; ++i)
        v.push_back(v[i - 1] + v[i - 2]);
}

template <typename T>
vector<T> rev_vec(const vector<T> &v) {
    vector<T> new_vec {};
    for (int i = v.size() - 1; i >= 0; --i)
        new_vec.push_back(v[i]);
    return new_vec;
}

template <typename T>
void reverse_vec(vector<T> &v) {
    const int n = v.size() - 1;
    for (auto i = 0; i < (n + 1) / 2; ++i)
        swap(v[i], v[n - i]);
}

void test_fib() {
    // int n {10}, lim {0};
    // do {
    //     vector<int> fib_vec {};
    //     fibonacci(1, 2, fib_vec, ++n);
    //     lim = fib_vec[fib_vec.size() - 1];
    // } while (lim > 0);
    // cout << n << endl;

    vector<int> fib_vec {};
    fibonacci(1, 2, fib_vec, 8);
    reverse_vec(fib_vec);
    print("Fibonacci numbers:", fib_vec);
    fib_vec = rev_vec(fib_vec);
    print("Fibonacci numbers:", fib_vec);
}

void name_age_pairs() {
    vector<string> names {"Joe", "Peter", "Mary", "Kate", "Alex"};
    const int n = names.size();
    vector<double> ages {};
    for (auto i = 0; i < n; ++i) {
        cout << "Enter age for " << names[i] << ": ";
        double v {};
        cin >> v;
        ages.push_back(v);
    }

    for (auto i = 0; i < n; ++i)
        cout << names[i] << ", age: " << ages[i] << endl;

    vector<string> copy_names {names};
    sort(names.begin(), names.end());

    vector<double> sorted_ages {};
    for (auto i = 0; i < n; ++i) {
        string temp {names[i]};
        for (auto j = 0; j < n; ++j) {
            if (copy_names[j] == temp) {
                sorted_ages.push_back(ages[j]);
                break;
            }
        }
    }
    print("Sorted names:", names);
    print("Sorted ages:", sorted_ages);
}

template <typename T>
void print_until_s(const vector<T> &vs, const T &quit) {
    for (auto s : vs) {
        if (s == quit)
            return;
        cout << s << endl;
    }
}

template <typename T>
void print_until_ss(const vector<T> &vs, const T &quit) {
    bool occured {false};
    for (auto s : vs) {
        if (s == quit) {
            if (occured)
                return;
            else
                occured = true;
        }
        cout << s << endl;
    }
}

int main() {

    // test_fib();
    name_age_pairs();

    return 0;
}
