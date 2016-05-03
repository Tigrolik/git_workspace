#ifndef _SINGLELL_H_
#define _SINGLELL_H_

#include <iostream>

struct God {
    std::string name;
    std::string mythology;
    std::string vehicle;
    std::string weapon;
};

class SingleLL {
public:
    SingleLL(const God&, SingleLL* = nullptr);

    SingleLL* add_ordered(SingleLL*);
    SingleLL* find(const God&);
    const SingleLL* find(const God&) const;
    SingleLL* advance(int);
    const SingleLL* advance(int) const;

    SingleLL* next() const { return next_; }
    God value() const { return value_; }

    void set_value(const God &g) { value_ = g; }

private:
    God value_;
    SingleLL *next_;
};

void print_all(const SingleLL*);

bool operator==(const God&, const God&);
bool operator!=(const God&, const God&);

#endif

