#include "../my_facilities.h"
#include <iostream>
#include <fstream>
#include <sstream>

using namespace std;

void test_bin_files() {
    const string fn1 {"bin_file1.txt"};
    ifstream ifs {fn1, ios_base::binary};
    if (!ifs)
        error("cannot open file " +  fn1);

    const string fn2 {"bin_file2.txt"};
    ofstream ofs {fn2, ios_base::binary};
    if (!ofs)
        error("cannot open file " +  fn2);

    vector<int> v;
    for (int x; ifs.read(as_bytes(x), sizeof(int));) // reading bytes
        v.push_back(x);

    for (auto &x: v)
        ofs.write(as_bytes(x), sizeof(int)); // writing bytes
}

void test_pos() {
    const string fn1 {"bin_file1.txt"};
    fstream fs {fn1};
    if (!fs)
        error("cannot open file " +  fn1);
    fs.seekg(2);
    char ch;
    fs >> ch;
    cout << ch << endl;
    fs.seekp(4);
    fs << 'y';
}

double read_str(const string &s) {
    istringstream is {s};
    double d;
    is >> d;
    if (!is)
        error("double format error: " + s);
    return d;
}

void test_read_str() {
    cout << read_str("12.42") << endl;
    cout << read_str("1.34e-3") << endl;
    cout << read_str("twelve point three") << endl;
}

int main() {

    //test_bin_files();
    //test_pos();
    test_read_str();

    return 0;
}
