#include <iostream>
#include <fstream>
#include <vector>
#include <map>
#include <stdexcept>

using namespace std;

template <typename T>
T sum(const vector<T> &v) {
    T s {};
    for (const auto &x: v)
        s += x;
    return s;
}

void error(const string &s) {
    throw runtime_error(s);
}

void compute() {
    const string fn{"name_value.txt"};
    ifstream ifs {fn};
    if (!ifs)
        error("cannot open file " + fn);
    ifs.exceptions(ifs.exceptions() | ios_base::badbit);
    string name;
    double val;
    map<string, vector<double>> name_val {};
    while (ifs >> name >> val) {
        name_val[name].push_back(val);
        if (ifs.fail()) {
            ifs.unget();
            ifs.clear(ios_base::failbit);
        }
    }
    ifs.close();
    for (const auto &x: name_val)
        cout << x.first << ", sum: " << sum(x.second) << endl;
    cout << endl;
}

int main() {

    compute();

    return 0;
}
