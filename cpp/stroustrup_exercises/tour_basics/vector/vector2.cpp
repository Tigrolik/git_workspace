#include "vector2.h"
#include <iostream>
#include <stdexcept>
#include <exception>

using namespace std;

template<typename T>
Vector2<T>::Vector2(int s): elem{new T[s]}, sz{s} {
    if (s < 0)
        throw length_error(0);
    elem = new T[s];
    sz = s;
}

template<typename T>
T &Vector2<T>::operator[](int i) {
    if (i < 0 || i >= size())
        throw out_of_range{"Vector2::operator[]"};
    return elem[i];
}

template<typename T>
const T& Vector2<T>::operator[](int i) const {
    if (i < 0 || i >= size())
        throw out_of_range{"Vector2::operator[]"};
    return elem[i];
}

template<typename T>
int Vector2<T>::size() const {
    return sz;
}

template<typename T>
T* Vector2<T>::begin(Vector2<T>& x) {
    return &x[0];
}

template<typename T>
T* Vector2<T>::end(Vector2<T>& x) {
    return x.begin() + x.size();
}
