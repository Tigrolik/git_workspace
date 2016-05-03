#ifndef _VECTOR_CONTAINER_H_
#define _VECTOR_CONTAINER_H_

#include "vector.h"
#include "container.h"

using namespace std;

class Vector_container: public Container {
    private:
        Vector v;
    public:
        Vector_container(size_t s): v(s) { }
        ~Vector_container() {}

        double &operator[](size_t i) { return v[i]; }
        size_t size() const { return v.size(); }
};

#endif
