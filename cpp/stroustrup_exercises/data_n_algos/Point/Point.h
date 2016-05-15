#ifndef POINT_H
#define POINT_H

#include <iostream>
#include <vector>
#include <stdexcept>

/*
 * ------------------ Range_error struct ------------------
 */
struct Range_error: std::out_of_range {
    size_t idx;
    Range_error(const size_t i):
        std::out_of_range{"Range error: index " + std::to_string(i)}, idx{i} {
    }
};

/*
 * ------------------ Point class ------------------
 */
template <class T>
class Point {
public:
    Point(): x_{}, y_{}, w_{} { };
    Point(const T&, const T&, const T& = T{});
    Point(const std::initializer_list<T>);
    Point(const Point&);
    Point& operator=(const Point&);
    ~Point() = default;

    size_t size() const { return 3; }

    T& operator[](const size_t i);
    const T& operator[](const size_t i) const;
    T& at(const size_t i);
    const T& at(const size_t i) const;

    T& x() { return x_; }
    const T& x() const { return x_; }
    T& y() { return y_; }
    const T& y() const { return y_; }
    T& w() { return w_; }
    const T& w() const { return w_; }

private:
    T x_;
    T y_;
    T w_;
};

template <class T>
Point<T>::Point(const T &t1, const T &t2, const T &t3): x_{t1}, y_{t2}, w_{t3} {
}

template <class T>
Point<T>::Point(const std::initializer_list<T> il): x_{}, y_{}, w_{} {
    auto iter = std::begin(il);
    for (size_t i {0}; i < std::min(size(), il.size()); ++i, ++iter)
        operator[](i) = *iter;
}

template <class T>
Point<T>::Point(const Point<T> &o): x_{o.x_}, y_{o.y_}, w_{o.w_} { }

template <class T>
Point<T> &Point<T>::operator=(const Point<T> &o) {
    if (this != &o) {
        x_ = o.x_;
        y_ = o.y_;
        w_ = o.w_;
    }
    return *this;
}

template <class T>
T& Point<T>::operator[](const size_t i) {
    return (i < 1) ? x_ : (i < 2) ? y_ : w_;
}

template <class T>
const T& Point<T>::operator[](const size_t i) const {
    return (i < 1) ? x_ : (i < 2) ? y_ : w_;
}

template <class T>
T& Point<T>::at(const size_t i) {
    return (i < size()) ? operator[](i) : (throw Range_error(i), operator[](i));
}

template <class T>
const T& Point<T>::at(const size_t i) const {
    return (i < size()) ? operator[](i) : (throw Range_error(i), operator[](i));
}

template <class T>
std::ostream& operator<<(std::ostream &os, const Point<T> &p) {
    os << "{ ";
    for (size_t i {0}; i < p.size(); ++i) os << p[i] << ' ';
    //for (const auto &t: p)
    //    os << t << ' ';
    return os << '}';
}

/*
 * ------------------ Point_array class ------------------
 */
template <class T>
class Point_array {
public:
    Point_array(): pa_{} { }
    Point_array(const std::vector<Point<T>> &p): pa_{p} { }

    using iterator = typename std::vector<Point<T>>::iterator;
    using const_iterator = typename std::vector<Point<T>>::const_iterator;

    iterator begin() { return pa_.begin(); }
    const_iterator begin() const { return pa_.begin(); }
    const_iterator cbegin() const { return pa_.cbegin(); }
    iterator end() { return pa_.end(); }
    const_iterator end() const { return pa_.end(); }
    const_iterator cend() const { return pa_.cend(); }

    iterator insert(iterator pos, const Point<T> &p) {
        return pa_.insert(pos, p);
    }
    iterator insert(const_iterator pos, const Point<T> &p) {
        return pa_.insert(pos, p);
    }
    iterator erase(iterator pos) { return pa_.erase(pos); }
    iterator erase(const_iterator pos) { return pa_.erase(pos); }
    iterator erase(iterator f, iterator b) { return pa_.erase(f, b); }
    iterator erase(const_iterator f, const_iterator b) {return pa_.erase(f,b);}
    void push_back(const Point<T> &p) { pa_.push_back(p); }
    void push_back(Point<T>&& p) { pa_.push_back(p); }

    Point<T>& operator[](const size_t i) { return pa_[i]; }
    const Point<T>& operator[](const size_t i) const { return pa_[i]; }
    Point<T>& at(const size_t i) { return pa_.at(i); }
    const Point<T>& at(const size_t i) const { return pa_.at(i); }

    size_t size() const { return pa_.size(); }

private:
    std::vector<Point<T>> pa_;
};

template <class T>
std::ostream& operator<<(std::ostream &os, const Point_array<T> &pa) {
    for (const auto &p: pa) os << p << ' ';
    return os;
}

#endif

