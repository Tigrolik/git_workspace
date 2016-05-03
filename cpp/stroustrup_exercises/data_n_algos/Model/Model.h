#ifndef _MODEL_H_
#define _MODEL_H_

#include <fstream>
#include <array>

template <class T, size_t N>
class Vec_base {
public:
    Vec_base(const std::array<T,N>&);

    T& operator[](const int i) { return a_[i]; }
    const T& operator[](const int i) const { return a_[i]; }

private:
    std::array<T,N> a_;
};

#endif

