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

// insert n before p
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

// insert n after p
Link* add(Link *p, Link *n) {
    if (n == nullptr)
        return p;
    if (p == nullptr)
        return n;
    n->prev = p;
    if (p->next)
        p->next->prev = n;
    n->next = p->next;
    p->next = n;
    return n;
}

// remove *p from list, return p's successor
Link* erase(Link *p) {
    if (p == nullptr)
        return nullptr;
    if (p->next)
        p->next->prev = p->prev;
    if (p->prev)
        p->prev->next = p->next;
    return p->next;
}

// find s in list
Link* find(Link *p, const std::string &s) {
    while(p) {
        if (p->value == s)
            return p;
        p = p->next;
    }
    return nullptr;
}

// move n positions in the list
Link* advance(Link *p, int n) {
    // positive n - moves forward, negative - backward
    if (p == nullptr)
        return nullptr;
    if (n > 0)
        while (n--)
            if (p->next == nullptr)
                return nullptr;
            else
                p = p->next;
    else if (n < 0)
        while (n++)
            if (p->prev == nullptr)
                return nullptr;
            else
                p = p->prev;
    return p;
}

void print_all(Link *p) {
    std::cout << "{ ";
    while (p) {
        std::cout << p->value;
        if ((p = p->next))
            std::cout << ", ";
    }
    std::cout << " }\n";
}

#endif

