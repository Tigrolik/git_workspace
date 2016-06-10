#include <iostream>
#include <vector>
#include <iomanip>
#include <typeinfo>
#include "Vector.h"
#include "Int.h"
#include "Checked_ptr.h"

struct K {};

template <class T>
void disp_max_size()
try {
    std::cout << "Maximum vector size for type: " << typeid(T).name() << '\n';
    std::cout << std::numeric_limits<std::size_t>::max() / sizeof(T) << '\n';
} catch (const std::bad_typeid &e) {
    std::cerr << e.what() << '\n';
}

void test_vector() {
    try {
        Vector<int> v (100, 3);
        for (size_t i {0}; i < v.size(); ++i)
            if (v.at(i) != v.at(i + 1))
                std::cout << v.at(i) << ' ';
        std::cout << '\n';
    } catch (const Size_error &e) {
        std::cerr << e.what() << '\n';
    } catch (const Range_error &e) {
        std::cerr << "Out of range\n";
    } catch (const std::bad_alloc &e) {
        std::cerr << e.what() << '\n';
    }
    //for (auto p = v; p != v + v.size(); ++p) std::cout << p << ' ';
    //std::cout << '\n';
    std::vector<int> vi, v_cap;
    for (int i {0}; i < 100; ++i) {
        vi.push_back(4);
        const int c = vi.capacity();
        bool b = true;
        for (int j = v_cap.size(); j; --j)
            if (v_cap[j] == c)
                b = false;
        if (b) {
            v_cap.push_back(c);
            //std::cout << c << '\n';
        }
    }

    //disp_max_size<char>();
    //disp_max_size<int>();
    //disp_max_size<double>();
    //disp_max_size<K>();
    //disp_max_size<long double>();
}

void disp_int(const long int li) {
    try {
        std::cout << Int(li) << '\n';
    } catch (const Int::Underflow_error &e) {
        std::cerr << "Too low value\n";
    } catch (const Int::Overflow_error &e) {
        std::cerr << "Too big value\n";
    }
}

void test_int() {
    std::cout << "Max Int value: " << Int::max_value() << '\n';
    std::cout << "Min Int value: " << Int::min_value() << '\n';
    long int li1 {-2147483649};
    disp_int(li1);
    long int li2 {2147483659};
    disp_int(li2);
    long int li3 {3659};
    disp_int(li3);
}

int main() {

    test_vector();
    //test_int();

    return 0;
}

