#include "../my_facilities.h"
#include <iostream>
#include <fstream>
#include <sstream>
#include <vector>
#include <algorithm>

using namespace std;

static const string vowels {"aeiouyAEIOUY"};

void rem_vowels(string &s) {
    for (int i = s.length() - 1; i >= 0; --i) {
        for (size_t j = 0; j < vowels.length(); ++j)
            if (vowels[j] == s[i])
                s.erase(i, 1);
    }
}

void tolower(string &s) {
    for (auto &c: s)
        c = tolower(c);
}

void rev_line(string &s) {
    const size_t n {s.length() - 1};
    for (size_t i = 0; i < n / 2 + 1; ++i)
        swap(s[i], s[n - i]);
}

void rev_words(string &s) {
    istringstream iss {s};
    if (!iss)
        error("error reading string " + s);
    s.clear();
    vector<string> vs;
    int n {0};
    for (string w; iss >> w; ++n)
        vs.push_back(w);
    cout << n << endl;
    for (auto i = n - 1; i > 0; --i)
        s += vs[i] + ' ';
    s += vs[0];
}

void file_to_lower(const string &fn) {
    ifstream ifs {fn};
    if (!ifs)
        error("cannot open file " + fn);
    ifs.exceptions(ifs.exceptions() | ios_base::badbit);

    ofstream ofs {"lower_" + fn};
    ofs.exceptions(ofs.exceptions() | ios_base::badbit);

    for (string s; getline(ifs, s);) {
        tolower(s);
        ofs << s << endl;
        if (ifs.fail()) {
            ifs.unget();
            ifs.clear(ios_base::failbit);
        }
    }
}

void get_wordline(const string &fn, const string &word) {
    ifstream ifs {fn};
    if (!ifs)
        error("cannot open file " + fn);
    ifs.exceptions(ifs.exceptions() | ios_base::badbit);

    int i {1};
    for (string s; getline(ifs, s); ++i) {
        istringstream iss {s};
        for (string w; iss >> w;)
            if (w == word) {
                cout << i << ": " << s << endl;
                break;
            }
        if (ifs.fail()) {
            ifs.unget();
            ifs.clear(ios_base::failbit);
        }
    }
}
void read_n_sort(const string &fn) {
    ifstream ifs {fn};
    if (!ifs)
        error("cannot open file " + fn);
    ifs.exceptions(ifs.exceptions() | ios_base::badbit);

    vector<int> v;
    for (int i; ifs >> i;) {
        v.push_back(i);
        if (ifs.fail()) {
            ifs.unget();
            ifs.clear(ios_base::failbit);
        }
    }
    for (const auto &x: v)
        cout << x << ' ';
    cout << endl;

    sort(v.begin(), v.end());
    //auto cur = v[0];
    size_t i {0};
    while (i < v.size()) {
        size_t j {1};
        auto cur = v[i];
        cout << cur;
        while (v[++i] == cur)
            ++j;
        if (j > 1)
            cout << "\t" << j;
        cout << endl;
        cur = v[i];
    }
}

int main() {

    //file_to_lower("test_file");
    //get_wordline("words.txt", "help");
    //string s {"testing new lines for reversing"};
    //rem_vowels(s);
    //rev_line(s);
    //rev_words(s);
    //cout << s << endl;
    read_n_sort("unsorted_ints.txt");

    return 0;
}
