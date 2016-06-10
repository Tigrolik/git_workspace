#ifndef VECTOR_H
#define VECTOR_H

#include <memory>
#include <limits>

/*
 * class Vector_base deals with memory for type T, not objects of type T
 * a user of Vector_base must construct all objects explicitly in the allocated
 * space and later destroy all constructed objects in a Vector_base before the
 * Vector_base itself is destroyed
 */

struct Range_error: public std::out_of_range {
    explicit Range_error(const std::string &s): std::out_of_range(s) { }
    explicit Range_error(const char* s): std::out_of_range(s) { }
};

struct Size_error: public std::length_error {
    explicit Size_error(const std::string &s): std::length_error(s) { }
    explicit Size_error(const char* s): std::length_error(s) { }
};

template <class T, class A = std::allocator<T>>
struct Vector_base {
    A alloc;  // allocator
    T *elem;  // start of allocation
    T *space; // end of element sequence, start of extra space
    T *last;  // end of allocated space
    Vector_base(const A &a, typename A::size_type n): alloc{}, elem{}, space{},
        last{} {
            if (n >= max_size()) throw Size_error{"Bad Size"};
            alloc = a;
            elem = alloc.allocate(n);
            space = elem + n;
            last = elem + n;
        }
    ~Vector_base() { alloc.deallocate(elem, last - elem); }

    static const std::size_t max_size() {
        return 1000;
        //return (std::numeric_limits<std::size_t>::max() / sizeof(T)) >> 1;
    }

    // forbid copying
    Vector_base(const Vector_base&) = delete;
    Vector_base& operator=(const Vector_base&) = delete;

    // move operations
    Vector_base(Vector_base&&);
    Vector_base& operator=(Vector_base&&);
};

/*
 * move operations
 */
template <class T, class A>
Vector_base<T, A>::Vector_base(Vector_base &&a): alloc{a.alloc}, elem{a.elem},
    space{a.space}, last{a.last} {
        a.elem = a.space = a.last = nullptr;
    }

template <class T, class A>
Vector_base<T, A>& Vector_base<T, A>::operator=(Vector_base &&a) {
    // swap transfers ownership of any memory allocated for elements
    std::swap(*this, a); return *this;
}

/*
 * class Vector exploits Vector_base
 */
template <class T, class A = std::allocator<T>>
class Vector {
    Vector_base<T, A> vb; // keep data here
    void destroy_elements();
public:
    using size_type = unsigned int;

    explicit Vector(const size_type, const T& = T{}, const A& = A());

    // copying
    Vector(const Vector&);
    Vector& operator=(const Vector&);

    // moving
    Vector(Vector&&);
    Vector& operator=(Vector&&);

    ~Vector() { destroy_elements(); }

    size_type size() const { return vb.space - vb.elem; }
    size_type capacity() const { return vb.last - vb.elem; }
    void reserve(const size_type); // increase capacity to n

    void resize(const size_type, const T& = {}); // increase size to n
    void push_back(const T&);

    T& operator[](const std::size_t n) { return vb.elem[n]; }
    const T& operator[](const std::size_t n) const { return vb.elem[n]; }

    T& at(const std::size_t n) {
        if (n >= size()) throw Range_error{"Out of range"};
        return operator[](n);
    }
    const T& at(const std::size_t n) const {
        if (n >= size()) throw Range_error{"Out of range"};
        return operator[](n);
    }
};

template <class T, class A>
void Vector<T, A>::destroy_elements() {
    for (T *p = vb.elem; p != vb.space; ++p)
        p->~T(); // destroy each element
    vb.space = vb.elem;
}

template <class T, class A>
Vector<T, A>::Vector(const size_type n, const T &val, const A &a)
    try: vb{a, n} {
        std::uninitialized_fill(vb.elem, vb.elem + n, val);
    } catch (const Size_error &e) {
        throw;
    }

template <class T, class A>
Vector<T, A>::Vector(const Vector<T, A> &a): vb{a.vb.alloc, a.size()} {
    std::uninitialized_copy(std::begin(a), std::end(a), vb.elem);
}

template <class T, class A>
Vector<T, A>::Vector(Vector &&a): vb{std::move(a.vb)} { }

template <class T, class A>
Vector<T, A>& Vector<T, A>::operator=(Vector &&a) {
    destroy_elements(); // most likely redundant
    //clear();
    swap(*this, a);
}

template <class T, class A>
Vector<T, A>& Vector<T, A>::operator=(const Vector &a) {
    if (capacity() < a.size()) {
        Vector temp {a};
        std::swap(*this, temp);
        return *this;
    }
    if (this == &a) return *this;

    const size_type sz = size(), asz = a.size();
    vb.alloc = a.vb.alloc;
    if (asz <= sz) {
        std::copy(std::begin(a), std::begin(a) + asz, vb.elem);
        for (T *p = vb.elem + asz; p != vb.space; ++p)
            p->~T(); // destroy surplus elements
    } else {
        std::copy(std::begin(a), std::begin(a) + sz, vb.elem);
        // construct extra elements
        std::uninitialized_copy(std::begin(a) + sz, std::end(a), vb.space);
    }
    vb.space = vb.elem + asz;
    return *this;
}

template <class T, class A>
void safe_assign(Vector<T, A> &a, const Vector<T, A> &b) {
    Vector<T, A> temp {b};
    std::swap(a, temp);
}

template <class T, class A>
void safe_assign(Vector<T, A> &a, Vector<T, A> b) { // b by value
    std::swap(a, b);
}

template <typename In, typename Out>
Out uninitialized_move(In b, In e, Out oo) {
    //return std::uninitialized_copy(std::make_move_iterator(b),
    //        std::make_move_iterator(b), oo);
    using Value = typename std::iterator_traits<Out>::value_type;
    for (; b != e; ++b, ++oo) {
        ::new(static_cast<void*>(&*oo)) Value{std::move(*b)}; // move construct
        b->~T();
    }
    return b;
}

template <class T, class A>
void Vector<T, A>::reserve(const size_type n) {
    if (n <= capacity()) return;
    Vector_base<T, A> b {vb.alloc, n}; // get new space
    uninitialized_move(vb.elem, vb.elem + size(), b.elem); // move elements
    std::swap(vb, b); // install new base
}

template <typename In>
void destroy(In b, In e) {
    for (; b != e; ++b) // destroy [b:e)
        b->~T();
}

template <class T, class A>
void Vector<T, A>::resize(const size_type n, const T &val) {
    reserve(n);
    if (size() < n)
        std::uninitialized_fill(vb.elem + size(), vb.elem + n, val);
    else
        destroy(vb.elem.size(), vb.elem + n);
    vb.space = vb.last = vb.elem + n;
}

template <class T, class A>
void Vector<T, A>::push_back(const T& x) {
    if (capacity() == size())
        reserve(vb.sz ? vb.sz << 1 : 8);
    vb.alloc.construct(&vb.elem[size()], x); // add val at the end
    ++vb.space; // increment size
}

#endif

