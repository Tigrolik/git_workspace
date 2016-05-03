#include "my_facilities.h"
#include <iostream>
#include <vector>
#include <fstream>

using namespace std;

void merge_files(const vector<string> &fn_vec) {
    const string out_fn {"merged.txt"};
    ofstream ofs {out_fn};
    if (!ofs)
        error("cannot open file " + out_fn);
    ofs.exceptions(ofs.exceptions() | ios_base::badbit);

    for (const auto &x: fn_vec) {
        ifstream ifs {x};
        if (!ifs)
            error("cannot open file " + x);
        ifs.exceptions(ifs.exceptions() | ios_base::badbit);
        //for (char c; ifs.get(c);) {
        //    ofs << c;
        for (string s; getline(ifs, s);) {
            ofs << s << endl;
            if (ifs.fail()) {
                ifs.unget();
                ifs.clear(ios_base::failbit);
            }
            if (ofs.fail())
                ofs.clear(ios_base::failbit);
        }
    }

}

void test_merge() {
    const vector<string> fn_vec {"test.txt", "give_ints.txt",
        "temp_readings/raw_temps.txt"};
    merge_files(fn_vec);
}

template <typename T>
vector<T> merge1(const vector<T> &v1, const vector<T> &v2) {
    vector<T> res;
    size_t i1 {0}, i2 {0};
    while (i1 < v1.size() && i2 < v2.size())
        if (v1[i1] < v2[i2]) {
            res.push_back(v1[i1]);
            ++i1;
        } else {
            res.push_back(v2[i2]);
            ++i2;
        }
    while (i1 < v1.size()) {
        res.push_back(v1[i1]);
        ++i1;
    }
    while (i2 < v2.size()) {
        res.push_back(v2[i2]);
        ++i2;
    }
    return res;
}

void merge_sorted_files(const vector<string> &fn_vec) {
    const string out_fn {"sorted.txt"};
    ofstream ofs {out_fn};
    if (!ofs)
        error("cannot open file " + out_fn);
    ofs.exceptions(ofs.exceptions() | ios_base::badbit);

    vector<string> res_vec;
    for (const auto &x: fn_vec) {
        vector<string> temp_vec;
        ifstream ifs {x};
        if (!ifs)
            error("cannot open file " + x);
        ifs.exceptions(ifs.exceptions() | ios_base::badbit);
        for (string s; ifs >> s;) {
            temp_vec.push_back(s);
            if (ifs.fail()) {
                ifs.unget();
                ifs.clear(ios_base::failbit);
            }
        }
        res_vec = merge1(res_vec, temp_vec);
    }
    for (const auto &x: res_vec)
        ofs << x << ' ';
    ofs << endl;
}

void test_merge1() {
    const vector<int> v1 {1, 3, 7, 9}, v2 {2, 3, 4, 5, 8};
    cout << merge1(v1, v2) << endl;
    const vector<string> fn_vec {"sorted1.txt", "sorted2.txt"};
    merge_sorted_files(fn_vec);
}

int main() {

    //test_merge();
    test_merge1();

    return 0;
}
