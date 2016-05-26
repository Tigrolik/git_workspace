#ifndef PVECTOR_H
#define PVECTOR_H

#include <vector>

//template <class T, class Allocator = std::allocator<T>>
template <class T>
class pvector {
public:
    //typedef std::vector<T*> base;
    using value_type = typename std::vector<T*>::value_type;
    using size_type = typename std::vector<T*>::size_type;
    using iterator = typename std::vector<T*>::iterator;
    using const_iterator = typename std::vector<T*>::const_iterator;

    pvector(): v_() { }
    explicit pvector(const size_type n): v_(std::vector<T*>(n)) { }
    pvector(const pvector &v): v_{v.v_} { }
    pvector& operator=(const pvector &v) {
        if (this != &v) v_ = v.v_; return *this;
    }

    ~pvector();

    iterator begin() { return v_.begin(); }
    const_iterator begin() const { return v_.begin(); }
    iterator end() { return v_.end(); }
    const_iterator end() const { return v_.end(); }

    T* operator[](const size_type n) { return v_[n]; }
    const T* operator[](const size_type n) const { return v_[n]; }

    size_type size() const { return v_.size(); }
    size_type capacity() const { return v_.capacity(); }

    void push_back(T *t) { v_.push_back(t); }

private:
    std::vector<T*> v_;
};

template <class T>
typename pvector<T>::iterator begin(pvector<T> &pv) {
    return pv.begin();
}

template <class T>
typename pvector<T>::iterator end(pvector<T> &pv) {
    return pv.end();
}

template <class T>
pvector<T>::~pvector() {
    for (iterator it = begin(); it != end(); ++it) {
        std::cout << "deleting " << **it << '\n';
        delete *it;
    }
}

template <class T>
class ovector: public pvector<T> {
public:
    class iterator;

    using size_type = typename pvector<T>::size_type;

    iterator begin() { return typename ovector::iterator(pvector<T>::begin()); }
    iterator end() { return typename ovector::iterator(pvector<T>::end()); }

    T& operator[](const size_type n) { return *pvector<T>::operator[](n); }
    const T& operator[](const size_type n) const {
        return *pvector<T>::operator[](n);
    }

};

template <class T>
class ovector<T>::iterator {
public:
    iterator(const iterator &it): it_(it.it_) { }
    iterator(const typename std::vector<T*>::iterator &it): it_(it) { }

    iterator& operator++() { ++it_; return *this; }
    iterator operator++(int) { iterator t = it_; ++it_; return t; }
    iterator& operator--() { --it_; return *this; }
    iterator operator--(int) { iterator t = it_; --it_; return t; }

    bool operator==(const iterator &o) const { return it_ == o.it_; }
    bool operator!=(const iterator &o) const { return !(*this == o); }

    T& operator*() { return **it_; }
private:
    typename std::vector<T*>::iterator it_;
};

template <class T>
class ownership_vector {
public:
    ownership_vector(): owned_() { }
    ownership_vector(T* t) { push_back(t); }
    ownership_vector(T& t) { push_back(t); }

    ~ownership_vector();

    T* operator[] (const size_t n) { return elems_[n]; }
    const T* operator[] (const size_t n) const { return elems_[n]; }

    void push_back(T* t) { elems_.push_back(t); owned_.push_back(t); }
    void push_back(T& t) { elems_.push_back(&t); }

    size_t size() const { return elems_.size(); }
private:
    std::vector<T*> elems_;
    std::vector<T*> owned_;
    ownership_vector(const ownership_vector&); // private prevents copying
    ownership_vector& operator=(const ownership_vector&);
};

template <class T>
ownership_vector<T>::~ownership_vector() {
    for (size_t i {0}; i < owned_.size(); ++i) {
        std::cout << "deleting " << *owned_[i] << '\n';
        delete owned_[i];
    }
}

#endif

