#include <iostream>
#include <vector>

using namespace std;

void print_array10(ostream &os, int *a) {
    for (int i {0}; i < 10; ++i)
        os << a[i] << ' ';
    os << '\n';
}

void print_array(ostream &os, int *a, const int n) {
    for (int i {0}; i < n; ++i)
        os << a[i] << ' ';
    os << '\n';
}

void print_vector(ostream &os, const vector<int> &v) {
    for (size_t i {0}; i < v.size(); ++i)
        os << v[i] << ' ';
    os << '\n';
}

void test_new() {
    constexpr int n {10};
    int *arr = new int[n];
    for (int i {0}; i < n; ++i)
        arr[i] = 100 + i;
    print_array10(cout, arr);

    int *arr2 = new int[n + 1];
    for (int i {0}; i < n + 1; ++i)
        arr2[i] = 200 + i;
    print_array(cout, arr2, n + 1);

    int *arr3 = new int[n - 1];
    for (int i {0}; i < n - 1; ++i)
        arr3[i] = 300 + i;
    print_array(cout, arr3, n - 1);

    delete [] arr;
    delete [] arr2;
    delete [] arr3;

    vector<int> vi(n << 1);
    for (int i {0}; i < n << 1; ++i)
        vi[i] = 400 + i;
    print_vector(cout, vi);
}

void test_pointers() {
    int x {7};
    int *p1 = &x;
    print_array(cout, p1, 1);

    int arr1[7] {1, 2, 4, 8, 16, 32, 64};
    int *p2 = arr1;
    cout << p2 << endl;
    print_array(cout, arr1, 7);

    int *p3 = p2;
    cout << p3 << endl;
    p1 = p2;
    p3 = p2;

    cout << p1 << ' ' << p2 << ' ' << *p1 << ' ' << *p2 << endl;

    int *arr2 = new int[10];
    arr2[0] = 1;
    for (int i {1}; i < 10; ++i)
        arr2[i] = arr2[i - 1] << 1;
    p1 = &arr2[0];
    print_array(cout, p1, 10);

    int *arr3 = new int[10];
    arr3[0] = 1;
    for (int i {1}; i < 10; ++i)
        arr3[i] = arr3[i - 1] + i;
    p2 = arr3;
    print_array(cout, p2, 10);

    for (int i {0}; i < 10; ++i)
        p2[i] = p1[i];
    print_array(cout, p2, 10);

    delete [] arr2;
    delete [] arr3;
}

int main() {

    //test_new();
    test_pointers();

    return 0;
}
