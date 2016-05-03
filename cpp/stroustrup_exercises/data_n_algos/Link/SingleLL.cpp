#include "SingleLL.h"

SingleLL::SingleLL(const God &g, SingleLL *n): value_ {g.name, g.mythology,
    g.vehicle, g.weapon}, next_{n} {
}

// insert n lexicographically into the list: use name for ordering
SingleLL* SingleLL::add_ordered(SingleLL *n) {
    if (n == nullptr) return this;
    if (this == nullptr) return n;
    if (value_.name > n->value_.name) {
        n->next_ = this;
        return n;
    }
    SingleLL *p = this;
    while (p->next_) {
        if (p->next_->value_.name > n->value_.name) {
            n->next_ = p->next_;
            p->next_ = n;
            return n;
        }
    }
    p->next_ = n;
    return p;
}

// find g in the list
SingleLL* SingleLL::find(const God &g) {
    SingleLL *p = this;
    while (p) {
        if (p->value_ == g)
            return p;
        p = p->next_;
    }
    return nullptr;
}

const SingleLL* SingleLL::find(const God &g) const {
    const SingleLL *p = this;
    while (p) {
        if (p->value_ == g)
            return p;
        p = p->next_;
    }
    return nullptr;
}

// move n positions in the list
SingleLL* SingleLL::advance(int n) {
    SingleLL *p = this;
    if (p == nullptr)
        return nullptr;
    if (n > 0)
        while (n--)
            if (p->next_ == nullptr)
                return nullptr;
            else
                p = p->next_;
    return p;
}

const SingleLL* SingleLL::advance(int n) const {
    const SingleLL *p = this;
    if (p == nullptr)
        return nullptr;
    if (n > 0)
        while (n--)
            if (p->next_ == nullptr)
                return nullptr;
            else
                p = p->next_;
    return p;
}

void print_all(const SingleLL *p) {
    std::cout << "{\n";
    while (p) {
        const God g = p->value();
        std::cout << g.name << ", " << g.mythology << ", " << g.vehicle <<
            ", " << g.weapon;
        if ((p = p->next()))
            std::cout << ";\n";
    }
    std::cout << "\n}\n";
}

bool operator==(const God &g1, const God &g2) {
    return (g1.name == g2.name && g1.mythology == g2.mythology &&
            g1.vehicle == g2.vehicle && g1.weapon == g2.weapon);
}

bool operator!=(const God &g1, const God &g2) {
    return !(g1 == g2);
}

