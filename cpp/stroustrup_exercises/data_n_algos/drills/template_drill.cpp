#include <iostream>
#include <vector>

using namespace std;

template<typename T> struct S {
    S(const T &t): val{t} {
    }
    S operator=(const T&);
    T& get();
    const T& get() const;
    void set(const T&);
private:
    T val;
};

template<typename T>
T& S<T>::get() {
    return val;
}

template<typename T>
const T& S<T>::get() const {
    return val;
}

template<typename T>
void S<T>::set(const T &t) {
    val = t;
}

template<typename T>
S<T> S<T>::operator=(const T &t) {
    val = t;
}

template<typename T>
void read_val(T &v) {
    cin >> v;
}


void test_template() {
    int iv;
    read_val(iv);
    S<int> si {iv};
    cout << "S<int>: " << si.get() << endl;
    S<char> sc {'w'};
    cout << "S<char>: " << sc.get() << endl;
    S<double> sd {0.3094};
    cout << "S<double>: " << sd.get() << endl;
    S<string> ss {"Hello, templated string!"};
    cout << "S<string>: " << ss.get() << endl;
    S<vector<int>> sv {vector<int>{1, 3, 5, 8}};
    cout << "S<vector<int>>: ";
    for (size_t i {0}; i < sv.get().size(); ++i)
        cout << sv.get()[i] << ' ';
    cout << endl;
}

int main() {

    test_template();

    return 0;
}

