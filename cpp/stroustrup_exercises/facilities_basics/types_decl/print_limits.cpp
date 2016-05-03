#include <iostream>
#include <limits>
#include <typeinfo>

template <typename T>
void print_type(const T v) {
    using namespace std;

    // size
    cout << "size = " << sizeof(v);

    // limits
    if (typeid(T).name() == typeid(char).name()) { // casting for "char"
        cout << "; max = " << static_cast<int>(numeric_limits<T>::max());
        cout << "; lowest = " << static_cast<int>(numeric_limits<T>::lowest());
    } else {
        cout << "; max = " << numeric_limits<T>::max();
        cout << "; lowest = " << numeric_limits<T>::lowest();
    }
    cout << "; align = " << alignof(T) << endl;
}

int main()
{
    using namespace std;

    cout << "Size, maximum and minimal values for various types:\n";

    cout << "boolean: "; print_type(true);
    cout << "char: "; print_type('c');
    cout << "short: "; print_type(static_cast<short>(5));
    cout << "int: "; print_type(static_cast<int>(5));
    // int x = 5;
    // int *p = &x;
    // cout << "align: " << alignof(p) << endl;
    using l_new = long;
    cout << "long: "; print_type(static_cast<l_new>(5));
    cout << "long long: "; print_type(static_cast<long long>(5));
    cout << "float: "; print_type(static_cast<float>(5.0));
    cout << "double: "; print_type(static_cast<double>(5.0));
    cout << "long double: "; print_type(static_cast<long double>(5.0));
    cout << "unsigned: "; print_type(static_cast<unsigned>(5));
    cout << "unsigned long: "; print_type(static_cast<unsigned long>(5));

    cout << "pointer: size = " << sizeof(double*);
    cout << "; max = " << numeric_limits<float*>::max();
    cout << "; lowest = " << numeric_limits<long double*>::lowest();
    cout << "; align = " << alignof(int*) << endl;

    return 0;
}

