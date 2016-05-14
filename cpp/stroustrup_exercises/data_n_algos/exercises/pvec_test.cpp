#include <iostream>
#include "pvector.h"

void test_pvec() {
    pvector<int> pvi;
    for (int i {0}; i < 10; ++i)
        pvi.push_back(new int(i * 3 - 1));
    for (pvector<int>::size_type i = 0; i < pvi.size(); ++i)
        std::cout << *pvi[i] << ' ';
    std::cout << '\n';
}

void test_ovec() {
    ovector<double> ovi;
    for (int i {0}; i < 10; ++i)
        ovi.push_back(new double(i * 3.1));
    for (ovector<int>::size_type i = 0; i < ovi.size(); ++i)
        std::cout << ovi[i] << ' ';
    std::cout << '\n';

    ovector<double>::iterator it {begin(ovi)};
    //ovector<double>::iterator it {ovi.begin()};
    while (it != end(ovi))
        std::cout << *it++ << ' ';
    std::cout << '\n';
}

void test_ownership_vec() {
    int i1 {-1};

    ownership_vector<int> ov(i1);
    for (int i {0}; i < 10; i += 2)
        ov.push_back(new int(i));
    for (int i {1}; i < 10; i += 2)
        ov.push_back(i);
    for (size_t i {0}; i < ov.size(); ++i)
        std::cout << *ov[i] << ' ';
    std::cout << '\n';
}

int main() {

    //test_pvec();
    test_ovec();
    //test_ownership_vec();

    return 0;
}

