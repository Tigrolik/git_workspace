#include "Floating.h"
#include "Matrix.h"
#include <fstream>
#include <stdexcept>
#include <bitset>
#include <chrono>

using namespace std;

static const string fn_out {"floating.out"};

void test_bitset() {
    constexpr int x {248};
    std::cout << std::bitset<32>(x) << std::endl;
}

void check_ifs(ifstream &ifs) {
    if (ifs.fail()) {
        ifs.unget();
        ifs.clear(ios_base::failbit);
    }
}

void read_n_write(const string &fn_in) {
    ifstream ifs {fn_in};
    if (!ifs)
        throw runtime_error("cannot open file " + fn_in);
    ifs.exceptions(ifs.exceptions() | ios_base::badbit);

    ofstream ofs {fn_out};

    int no_of_floats;
    ifs >> no_of_floats;
    for (int i {0}; i < no_of_floats; ++i) {
        float f; ifs >> f;
        ofs << Floating{f} << endl;
        check_ifs(ifs);
    }
}

bool compare_files(const string &fn1, const string &fn2) {
    ifstream ifs1 {fn1};
    if (!ifs1)
        throw runtime_error("cannot open file " + fn1);
    ifs1.exceptions(ifs1.exceptions() | ios_base::badbit);

    ifstream ifs2 {fn2};
    if (!ifs2)
        throw runtime_error("cannot open file " + fn2);
    ifs2.exceptions(ifs2.exceptions() | ios_base::badbit);

    bool b {true};
    for (string s1; getline(ifs1, s1);) {
        string s2;
        getline(ifs2, s2);
        check_ifs(ifs1); check_ifs(ifs2);
        if (s1 != s2) {
            //cout << s1 << " not ok\n";
            b = false;
        }
    }
    return b;
}

void test_floating() {
    using namespace std::chrono;
    static constexpr  int no_of_files {7};
    for (int i {1}; i <= no_of_files; ++i) {
        auto t = high_resolution_clock::now();
        const string idx {to_string(i)};
        cout << i << " :";
        read_n_write("../floating." + idx + ".in");
        (compare_files("../floating." + idx + ".out", fn_out)) ? cout << "OK, "
            : cout << "Not OK, ";
        cout << "time: " << duration<double>(high_resolution_clock::now() -
                t).count() << " seconds\n";
    }
}

Matrix read_from_is(ifstream &is, const bool flip = false) {
    int cols, rows;
    is >> rows >> cols;
    if (flip) {
        Matrix A {cols, rows};
        for (int r {0}; r < rows; ++r)
            for (int c {0}; c < cols; ++c)
                is >> A[c][r];
        return A;
    } else {
        Matrix A {rows, cols};
        for (int r {0}; r < rows; ++r)
            for (int c {0}; c < cols; ++c)
                is >> A[r][c];
        return A;
    }
}

void read_n_write_mat(const string &fnm_in, const string &fnm_out) {
    ifstream ifs {fnm_in};
    if (!ifs)
        throw runtime_error("cannot open file " + fnm_in);
    ifs.exceptions(ifs.exceptions() | ios_base::badbit);

    Matrix A {read_from_is(ifs)}, B {read_from_is(ifs, true)};

    ofstream ofs {fnm_out};
    ofs.exceptions(ofs.exceptions() | ios_base::badbit);
    ofs << A * B;
}

bool compare_mats(const string &fn1, const string &fn2) {
    ifstream ifs1 {fn1};
    if (!ifs1)
        throw runtime_error("cannot open file " + fn1);
    ifs1.exceptions(ifs1.exceptions() | ios_base::badbit);

    ifstream ifs2 {fn2};
    if (!ifs2)
        throw runtime_error("cannot open file " + fn2);
    ifs2.exceptions(ifs2.exceptions() | ios_base::badbit);

    bool b {true};
    for (int i; ifs1 >> i;) {
        int j; ifs2 >> j;
        //check_ifs(ifs1); check_ifs(ifs2);
        if (i != j) {
            cout << i << ' ' << j << " not OK\n";
            b = false;
        }
    }
    return b;
}

void test_matrix() {
    static const string fnm_out {"matrix.out"};
    const string fnm_in {"../matrix.1.in"};
    //ifstream ifs {fn_in};
    //if (!ifs)
    //    throw runtime_error("cannot open file " + fn_in);
    //ifs.exceptions(ifs.exceptions() | ios_base::badbit);
    //Matrix A {read_from_is(ifs)}, B {read_from_is(ifs, true)};

    //ofstream ofs {fnm_out};
    //ofs.exceptions(ofs.exceptions() | ios_base::badbit);
    //ofs << A * B;

    using namespace std::chrono;
    static constexpr  int no_of_files {11};
    for (int i {1}; i <= no_of_files; ++i) {
        auto t = high_resolution_clock::now();
        const string idx {to_string(i)};
        cout << "1: " << i << " :";
        read_n_write_mat("../matrix." + idx + ".in", fnm_out);
        (compare_mats("../matrix." + idx + ".out", fnm_out)) ?
            cout << "OK, " : cout << "Not OK, ";
        cout << "time: " << duration<double>(high_resolution_clock::now() -
                t).count() << " seconds\n";
        cout << "2: " << i << " :";
        read_n_write_mat("../matrix2." + idx + ".in", fnm_out);
        (compare_mats("../matrix2." + idx + ".out", fnm_out)) ?
            cout << "OK, " : cout << "Not OK, ";
        cout << "time: " << duration<double>(high_resolution_clock::now() -
                t).count() << " seconds\n";
    }
}

int main() {

    //test_floating();
    test_matrix();

    return 0;
}
