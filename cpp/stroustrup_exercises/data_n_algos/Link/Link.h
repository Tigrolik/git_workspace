#ifndef _LINK_H_
#define _LINK_H_

#include <iostream>

class Link {
public:
    Link(const std::string&, Link* = nullptr, Link* = nullptr);

    Link* insert(Link*);
    Link* add(Link*);
    Link* erase();
    Link* find(const std::string&);
    const Link* find(const std::string&) const;
    Link* advance(int n);
    const Link* advance(int n) const;

    Link* next() const { return next_; }
    Link* prev() const { return prev_; }
    std::string value() const { return value_; }

    void set_value(const std::string &s) { value_ = s; }

private:
    std::string value_;
    Link *prev_;
    Link *next_;
};

void print_all(const Link*);

#endif

