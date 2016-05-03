#include "Matrix.h"

Matrix::Matrix(const int r, const int c):
    m_{ std::vector<vector<int>> (r, std::vector<int>(c, 0))} {
    }

Matrix::Matrix(const vector<vector<int>> &m): m_{m} { }

vector<int> &Matrix::operator[](const int i) {
    if (i < 0 || i > num_rows())
        return m_[0];
    return m_[i];
}

vector<int> Matrix::row(const int r) const {
    return m_[r];
}

Matrix Matrix::operator*(const Matrix &o) {
    const int r1 {num_rows()}, c1 {num_cols()};
    const int r2 {o.num_rows()}, c2 {o.num_cols()};
    if (c1 != c2)
        return Matrix(r1, c1);
    vector<vector<int>> res =
        std::vector<vector<int>>(r1, std::vector<int>(r2, 0));
    for (int r {0}; r < r1; ++r) {
        const vector<int> v {row(r)};
        for (int c {0}; c < r2; ++c) {
            res[r][c] = 0;
            const vector<int> w {o.row(c)};
            for (int i {0}; i < c1; ++i)
                res[r][c] += v[i] * w[i];
        }
    }
    return Matrix {res};
}

ostream &operator<<(ostream &os, const Matrix &m) {
    os << m.num_rows() << ' ' << m.num_cols() << endl;
    for (const auto &x: m.m_) {
        const vector<int> v = x;
        os << v[0];
        for (size_t i {1}; i < v.size(); ++i)
            os << ' ' << v[i];
        os << endl;
    }
    return os;
}

