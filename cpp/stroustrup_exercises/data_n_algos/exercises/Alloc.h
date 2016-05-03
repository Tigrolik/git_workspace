#ifndef _ALLOC_H_
#define _ALLOC_H_

#include <cstdlib>

template <class T>
class Alloc {
public:
    Alloc() { }
    T* allocate(int n) { malloc(n * sizeof(T)); }
    //void deallocate(T *t, int n) { }
    void destroy(T *t) { free(t); }
};

#endif

