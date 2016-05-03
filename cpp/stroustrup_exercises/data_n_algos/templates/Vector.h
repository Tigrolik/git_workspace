#ifndef _VECTOR_H_
#define _VECTOR_H_

#include <iostream>
#include <vector>
#include <algorithm> // std::copy

struct Range_error: std::out_of_range {
    int idx;
    Range_error(const int i): std::out_of_range{"Range error"}, idx {i} {
    }
};

template <class T, class A = std::allocator<T>> class Vector {
public:
    using size_type = typename std::vector<T>::size_type;
    //using Vector<T>::vector;

    // ctors
    Vector(): sz {0}, elem {nullptr}, space {0} {
    }
    explicit Vector(int s): sz {s}, elem {new T[s]}, space {sz} {
        for (int i {0}; i < s; ++i)
            elem[i] = 0;
    }
    // ctor with initializer_list
    Vector(std::initializer_list<T> lst):
        sz (lst.size()), elem {new T[sz]}, space{sz} {
            std::copy(begin(lst), end(lst), elem);
        }
    // copy ctor
    Vector(const Vector&);
    // move ctor
    Vector(Vector&&v);
    // assignment ctor (copy assignment)
    Vector &operator=(const Vector&);
    // move assignment
    Vector &operator=(Vector&&v);

    ~Vector() {
        delete [] elem;
    }

    int size() const { return sz; }
    int capacity() const { return space; }

    T& at(const int n) {
        if (n < 0 || n >= sz) throw std::out_of_range();
        return elem[n];
    }
    const T& at(const int n) const {
        if (n < 0 || n >= sz) throw std::out_of_range();
        return elem[n];
    }
    T& operator[](const int n) {
        if (n < 0 || n >= this->size())
            throw Range_error(n);
        return elem[n];
    }
    const T& operator[](const int n) const {
        if (n < 0 || n >= this->size())
            throw Range_error(n);
        return elem[n];
    }
    void reserve(int);
    void resize(int, const T&);
    void push_back(const T&);


    friend std::ostream &operator<<(std::ostream &os, const Vector &v) {
        for (int i {0}; i < v.size(); ++i)
            std::cout << v[i] << ' ';
        return os;
    }

private:
    int sz;
    T *elem;
    int space;
    A alloc;
};

template <class T, class A>
Vector<T,A>::Vector(const Vector<T,A> &v): sz {v.size()}, elem {new T[sz]},
    space {sz} {
        std::copy(v.elem, v.elem + sz, elem);
    }

// move ctor: copy v's size and elements, then make an empty vector
template <class T, class A>
Vector<T,A>::Vector(Vector<T,A> &&v): sz {v.size()}, elem {v.elem}, space {sz} {
    std::cout << "move ctor called\n";
    v.sz = 0;
    v.elem = nullptr;
}

template <class T, class A>
Vector<T,A> &Vector<T,A>::operator=(const Vector<T,A> &v) {
    if (this != &v) {
        if (v.sz <= space) { // enough space, no need for new allocation
            sz = v.sz;
            for (int i {0}; i < sz; ++i)
                elem[i] = v.elem[i];
        } else {
            sz = space = v.size();
            T *p = alloc.allocate(sz);
            //T *p = new T[sz]; // allocate new space
            for (int i {0}; i < sz; ++i)
                alloc.construct(&p[i], elem[i]);
            //p[i] = v.elem[i];
            //std::copy(v.elem, v.elem + sz, p);
            for (int i {0}; i < sz; ++i)
                alloc.destroy(&elem[i]);
            alloc.deallocate(elem, space);
            //delete [] elem; // deallocate old space
            elem = p;
        }
    }
    return *this;
}

template <class T, class A>
Vector<T,A> &Vector<T,A>::operator=(Vector<T,A> &&v) {
    delete [] elem; // deallocate old space
    sz = space = v.size();
    elem = v.elem; // copy v's size and elements
    v.sz = 0; // make en empty vector
    v.elem = nullptr;
    return *this;
}

template <class T, class A>
void Vector<T,A>::reserve(int newalloc) {
    if (newalloc <= space) // never decrease allocation
        return;
    T *p = alloc.allocate(newalloc); // allocate new space
    for (int i {0}; i < sz; ++i) // copy old elements
        alloc.construct(&p[i], elem[i]); // copy
    for (int i {0}; i < sz; ++i) // copy old elements
        alloc.destroy(&elem[i]); // destroy
    alloc.deallocate(elem, space); // deallocate old space
    elem = p;
    space = newalloc;
}

template <class T, class A>
void Vector<T,A>::resize(int newsize, const T &val) {
    reserve(newsize);
    for (int i {sz}; i < newsize; ++i)
        alloc.construct(&elem[i], val);
    for (int i {newsize}; i < sz; ++i)
        alloc.destroy(&elem[i]);
    sz = newsize;
}

template <class T, class A>
void Vector<T,A>::push_back(const T &d) {
    if (space == 0)
        reserve(8); // start with space for 8 elements
    else if (sz == space)
        reserve(space << 1); // get more space (double it)
    alloc.construct(&elem[sz], d); // add d at the end
    ++sz; // one element has been added
}

#endif

