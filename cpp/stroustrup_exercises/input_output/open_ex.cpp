#include "../my_facilities.h"
#include <vector>
#include <fstream>

void test_open() {
    cout << "Enter filename: ";
    string fn;
    cin >> fn;
    ofstream ost {fn};
    if (!ost)
        error("cannot open file " + fn);
    for (auto i = 0; i < 10; ++i)
        ost << i << ' ';
    ost << "\b\n";
    ost.close();
    ifstream ist {fn};
    if (!ist)
        error("cannot open file " + fn);
    int i;
    while (ist >> i)
        cout << i << ' ';
    cout << "\b\n";
}

void fill_vector(istream &ist, vector<int> &v, char terminator) {
    for (int i; ist >> i;)
        v.push_back(i);
    if (ist.eof())
        return;
    if (ist.bad()) // throw an exception
        ist.exceptions(ist.exceptions() | ios_base::badbit);
        // error("ist is bad"); // stream corrupted
    if (ist.fail()) { // clean up the mess
        cout << "fail\n";
        ist.clear(); // clear stream state
        char c;
        ist >> c;
        if (c != terminator) {
            ist.unget();
            // set the state flags and clear other flags
            ist.clear(ios_base::failbit); // set the state back to fail
        }
    }
}

void test_fill_vec() {
    vector<int> v;
    fill_vector(cin, v, '*');
    for (auto x: v)
        cout << x << ' ';
    cout << endl;
}

int main() {

    test_fill_vec();
    //test_open();

    return 0;
}
