#ifndef _LINK_H_
#define _LINK_H_

#include <iostream>

class Link {
public:
    std::string value;
    Link *prev;
    Link *next;
    Link(const std::string& v, Link *p = nullptr, Link *n = nullptr):
        value{v}, prev{p}, next{n} {
        }
};

Link* insert(Link *p, Link *n) {
    if (n == nullptr)
        return p;
    if (p == nullptr)
        return n;
    n->next = p;
    if (p->prev)
        p->prev->next = n;
    n->prev = p->prev;
    p->prev = n;
    return n;
}

#endif

