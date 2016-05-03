#ifndef _MATRIX_H
#define _MATRIX_H

#include <iostream>
#include <vector>

using namespace std;

class Matrix {
    public:
        Matrix(const int, const int);
        Matrix(const vector<vector<int>>& = {{0}});

        vector<int> &operator[](const int);
        vector<int> row(const int) const;

        Matrix operator*(const Matrix&);

        int num_rows() const { return m_.size(); }
        int num_cols() const { return m_[0].size(); }

        friend ostream &operator<<(ostream&, const Matrix&);

    private:
        vector<vector<int>> m_;
};

#endif

