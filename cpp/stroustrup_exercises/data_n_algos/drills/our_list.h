#ifndef OUR_LIST_H
#define OUR_LIST_H

template <class Elem>
class list {
public:
    class iterator; // member type: iterator

    iterator begin(); // iterator to the first element
    iterator end(); // iterator to one beyond the last element

    iterator insert(iterator, const Elem&); // insert after Elem element
    iterator erase(iterator); // remove from the list

    void push_back(const Elem&); // insert at the end
    void push_front(const Elem&); // insert at the front
    void pop_front(); // remove the first element
    void pop_back(); // remove the last element

    Elem &front(); // the first element
    Elem &back(); // the last element
};

template <class Elem>
class list<Elem>::iterator {
public:
    iterator(Link<Elem> *p): curr{p} { }

    iterator& operator++() {curr = curr->succ; return *this; }
    iterator& operator--() {curr = curr->prev; return *this; }

    Elem& operator*() { return curr->val; }

    bool operator==(const iterator &b) const {return curr == b.curr; }
    bool operator!=(const iterator &b) const {return curr != b.curr; }

private:
    Link<Elem> *curr; // current link
};

template <class Iter>
void advance(Iter &p, const int n) {
    (n > 0) ?  while (n > 0) { ++p; --n; } : while (n < 0) { --p; ++n; }
}

#endif

