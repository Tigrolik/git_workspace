#ifndef CHECKED_PTR_H
#define CHECKED_PTR_H

#include <stdexcept>

template <class T>
class Checked_ptr {
public:
    explicit Checked_ptr(const T *p): p_{p} { }

    ~Checked_ptr() { delete p_; }

    T* operator->() { return get(); }
    T& operator*() { return *get(); }

private:
    T* p_;
    T* get() {
        if (!p_)
            throw std::runtime_error();
        return p_;
    }
    Checked_ptr(const Checked_ptr &cp): p_{cp.p_} { }
    Checked_ptr& operator=(const Checked_ptr &cp) {
        p_ = cp.p_;
        return *this;
    }
};

#endif

