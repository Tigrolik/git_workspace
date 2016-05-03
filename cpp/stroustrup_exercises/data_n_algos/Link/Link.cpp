#include "Link.h"

Link::Link(const std::string &s, Link *p, Link *n):
    value_{s}, prev_{p}, next_{n} {
    }

// insert n before p
Link* Link::insert(Link *n) {
    if (n == nullptr) return this;
    if (this == nullptr) return n;
    n->next_ = this;
    if (prev_)
        prev_->next_ = n;
    n->prev_ = prev_;
    prev_ = n;
    return n;
}

// insert n after p
Link* Link::add(Link *n) {
    if (n == nullptr) return this;
    if (this == nullptr) return n;
    n->prev_ = this;
    if (next_)
        next_->prev_ = n;
    n->next_ = next_;
    next_ = n;
    return n;
}


// remove *p from list, return p's successor
Link* Link::erase() {
    if (this == nullptr)
        return nullptr;
    if (next_)
        next_->prev_ = prev_;
    if (prev_)
        prev_->next_ = next_;
    return next_;
}

// find s in list
Link* Link::find(const std::string &s) {
    Link *p = this;
    while (p) {
        if (p->value_ == s)
            return p;
        p = p->next_;
    }
    return nullptr;
}

const Link* Link::find(const std::string &s) const {
    const Link *p = this;
    while (p) {
        if (p->value_ == s)
            return p;
        p = p->next_;
    }
    return nullptr;
}


// move n positions in the list
Link* Link::advance(int n) {
    // positive n - moves forward, negative - backward
    Link *p = this;
    if (p == nullptr)
        return nullptr;
    if (n > 0)
        while (n--)
            if (p->next_ == nullptr)
                return nullptr;
            else
                p = p->next_;
    else if (n < 0)
        while (n++)
            if (p->prev_ == nullptr)
                return nullptr;
            else
                p = p->prev_;
    return p;
}

const Link* Link::advance(int n) const {
    // positive n - moves forward, negative - backward
    const Link *p = this;
    if (p == nullptr)
        return nullptr;
    if (n > 0)
        while (n--)
            if (p->next_ == nullptr)
                return nullptr;
            else
                p = p->next_;
    else if (n < 0)
        while (n++)
            if (p->prev_ == nullptr)
                return nullptr;
            else
                p = p->prev_;
    return p;
}

void print_all(const Link *p) {
    std::cout << "{ ";
    while (p) {
        std::cout << p->value();
        if ((p = p->next()))
            std::cout << ", ";
    }
    std::cout << " }\n";
}


