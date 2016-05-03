#include <iostream>

using namespace std;

//class Matrix {
//    public:
//        Matrix() = default;
//    private:
//        size_t rows_;
//        size_t cols_;
//        int *m_;
//};

void display_matrix(const int *m, const size_t rows, const size_t cols) {
    for (size_t i {0}; i < rows; ++i) {
        cout << m[i * cols + 0];
        for (size_t j {1}; j < cols; ++j)
            cout << ' ' << m[i * cols + j];
        cout << endl;
    }
}

void test_matrix() {
    const size_t rows {3}, cols{5};
    int m[rows][cols];
    for (size_t i {0}; i < rows; ++i)
        for (size_t j {0}; j < cols; ++j)
            m[i][j] = i + i * j;
    display_matrix(&m[0][0], rows, cols);
}

int main() {

    test_matrix();

    return 0;
}
