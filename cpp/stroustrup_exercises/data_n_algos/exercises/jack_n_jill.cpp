#include <iostream>
#include <fstream>
#include <stdexcept>
#include <vector>
#include <algorithm>

using namespace std;

double* find_highest(vector<double> &v) {
    double h {-1.0};
    double *high = 0;
    for (size_t i {0}; i < v.size(); ++i)
        if (h < v[i]) {
            high = &v[i];
            h = v[i];
        }
    return high;
}

double* high(double *first, double *last) {
    double h {-1.0};
    double *high;
    for (double *p = first; p != last; ++p)
        if (h < *p) {
            high = p;
            h = *p;
        }
    return high;
}

template<class Iter>
Iter high_iter(Iter first, Iter last) {
    Iter high {first};
    while (++first != last)
        if (*high < *first)
            high = first;
    return high;
}

vector<double>* get_from_jill(const string &fn) {
    ifstream ifs {fn};
    if (!ifs)
        throw std::runtime_error("cannot open file " + fn);
    ifs.exceptions(ifs.exceptions() | std::ios_base::badbit);
    vector<double> *v = new vector<double>;
    for(double d; ifs >> d;) {
        v->push_back(d);
    }
    return v;
}

double* get_from_jack(const string &fn, const size_t count) {
    ifstream ifs {fn};
    if (!ifs)
        throw std::runtime_error("cannot open file " + fn);
    ifs.exceptions(ifs.exceptions() | std::ios_base::badbit);
    double *d = new double[count];
    for (size_t i {0}; i < count; ++i) {
        double v; ifs >> v;
        d[i] = v;
    }
    return d;
}


void test_jack_n_jill() {
    //double jill_data;
    vector<double> &v = *get_from_jill("jill_data.txt");
    double *jill_high {high(&v[0], &v[0] + v.size())};
    double *h1 = high_iter(&v[0], &v[0] + v.size());
    for (auto x: v)
        cout << x << ' ';
    cout << "\nmax value: " << *jill_high << ' ' << *h1 << '\n';
    delete &v;

    constexpr size_t count {7};
    double *d = get_from_jack("jack_data.txt", count);
    double *jack_high {high(d, d + count)};
    double *h2 = high_iter(d, d + count);
    for (size_t i {0}; i < count; ++i)
        cout << *d++ << ' ';
    cout << "\nmax value: " << *jack_high << ' ' << *h2 << '\n';
    //delete [] d;

    //vector<double> v1 {1, 2, 3};
    vector<double> v1 {};
    const auto vs = v1.size();
    double *h = high_iter(&v1[0], &v1[vs > 0 ? vs : 1]);
    if (h == &v1[0] + v1.size())
        cout << "The list is empty\n";
    else
        cout << *h << '\n';
}

int main() {

    test_jack_n_jill();

    return 0;
}

