#ifndef MATRIX_H
#define MATRIX_H

#include <array>
#include <stdexcept>
#include <memory>

template <class T>
class Matrix {
public:
    Matrix(const int d1, const int d2): dim_{d1, d2}, elem_{new T[d1 * d2]} { }

    Matrix(const Matrix&);            // copy ctor
    Matrix& operator=(const Matrix&); // copy assignment

    Matrix(Matrix&&);                 // move ctor
    Matrix& operator=(Matrix&&);      // move assignment

    ~Matrix () { delete [] elem_; }

    int size() const { return dim_[0] * dim_[1]; }
    int num_rows() const { return dim_[0]; }
    int num_cols() const { return dim_[1]; }

//private:
public:
    std::array<int, 2> dim_; // two dimensions
    T* elem_; // pointer to dim[0] * dim[1] elements of type T
};

// copy constructor
template <class T>
Matrix<T>::Matrix(const Matrix& M): dim_(M.dim_), elem_{new T[M.size()]} {
    std::uninitialized_copy(M.elem_, M.elem_ + M.size(), elem_);
}

// copy assignment
template <class T>
Matrix<T>& Matrix<T>::operator=(const Matrix& M) {
    //if (dim_[0] != M.dim_[0] || dim_[1] != M.dim_[1])
    //    throw std::runtime_error {"bad size in Matrix = "};
    //copy(M.elem_, M.elem_ + M.size(), elem_);
    Matrix tmp {M};   // make a copy
    std::swap(tmp, *this); // swap copy's representation with *this's
    return *this;
}

// move constructor
template <class T>
Matrix<T>::Matrix(Matrix&& M): dim_(M.dim_), elem_{M.elem_} {
    //std::cout << "Move ctor called\n";
    M.dim_ = {0, 0};
    M.elem_ = nullptr;
}

// move assignment
template <class T>
Matrix<T>& Matrix<T>::operator=(Matrix&& M) {
    //std::cout << "Move assignment called\n";
    std::swap(dim_, M.dim_);
    std::swap(elem_, M.elem_);
    return *this;
}

// sum of Matrices
template <class T>
inline Matrix<T> operator+(const Matrix<T>& A, const Matrix<T>& B) {
    if (A.num_rows() != B.num_rows() || A.num_cols() != B.num_cols())
        throw std::runtime_error {"Matrices sizes are not equal in + "};
    Matrix<T> res {A.num_rows(), A.num_cols()};
    for (int i {0}; i < A.size(); ++i)
        res.elem_[i] = A.elem_[i] + B.elem_[i];
    return res;
}

#endif /* end of include guard: MATRIX_H */

