#ifndef _MY_FACILITIES_H_
#define _MY_FACILITIES_H_

#include <iostream>
#include <fstream>
#include <sstream>
#include <vector>
#include <stdexcept>
#include <algorithm>

using namespace std;

void error(const string &s) {
    throw runtime_error(s);
}

template <class T>
char* as_bytes(T &i) {
    void *addr = &i;
    return static_cast<char*>(addr);
}

template <typename T>
T mean(const vector<T> &v) {
    return accumulate(v.begin(), v.end(), T {}) / v.size();
}

template <typename T>
void sort(vector<T> &v) {
    sort(v.begin(), v.end());
}

template <typename T>
T median(vector<T> &v) {
    // only for numeric types
    sort(v);
    const size_t mid_idx {v.size() / 2};
    if (v.size() % 2) // odd
        return v[mid_idx];
    else
        return 0.5 * (v[mid_idx - 1] + v[mid_idx]);
}

template <typename T>
ostream &operator<<(ostream &os, const vector<T> &v) {
    for (auto &x: v)
        os << x << ' ';
    return os;
}

template <typename T>
constexpr bool operator!=(const T &t1, const T &t2) {
    return !(t1 == t2);
}

template <typename T>
bool compare(const vector<T> &v1, const vector<T> &v2) {
    if (v1.size() != v2.size())
        return false;
    for (size_t i = 0; i < v1.size(); ++i)
        if (v1[i] != v2[i])
            return false;
    return true;
}

#endif

