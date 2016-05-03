#include "Model.h"

template <class T, size_t N>
Vec_base<T,N>::Vec_base(const std::array<T,N> &a): a_(a) {
}

