#include <iostream>

struct God {
    std::string name;
    std::string mythology;
    std::string vehicle;
    std::string weapon;

    God(const std::string &n, const std::string &m, const std::string v,
            const std::string &w): name {n}, mythology {m}, vehicle {v},
        weapon {w} {
        }
    God(const God &g): name{g.name}, mythology{g.mythology},
        vehicle{g.vehicle}, weapon{g.weapon} {
        }
    God &operator=(const God &g) {
        name = g.name;
        mythology = g.mythology;
        vehicle = g.vehicle;
        weapon = g.weapon;
        return *this;
    }

    friend std::ostream& operator<<(std::ostream &os, const God &g) {
        os << g.name << ", " << g.mythology << ", " << g.vehicle <<
            ", " << g.weapon;
        return os;
    }
};

bool operator==(const God &g1, const God &g2) {
    return (g1.name == g2.name && g1.mythology == g2.mythology &&
            g1.vehicle == g2.vehicle && g1.weapon == g2.weapon);
}

bool operator!=(const God &g1, const God &g2) {
    return !(g1 == g2);
}

bool operator<(const God &g1, const God &g2) {
    return (g1.name < g2.name);
}

bool operator>(const God &g1, const God &g2) {
    return (g1.name > g2.name);
}

template <class T>
class SingleLL {
public:
    SingleLL(const T &t, SingleLL<T>* = nullptr);

    SingleLL<T>* add_ordered(SingleLL<T>*);

    SingleLL<T>* find(const T&);
    const SingleLL<T>* find(const T&) const;

    SingleLL<T>* advance(int);
    const SingleLL<T>* advance(int) const;

    const SingleLL<T>* next() const { return next_; }
    const T& value() const { return value_; }

    void set_value(const T &g) { value_ = g; }

private:
    T value_;
    SingleLL<T> *next_;
};

template <class T>
void print_all(const SingleLL<T>*);

template <class T>
SingleLL<T>::SingleLL(const T &t, SingleLL<T> *n): value_ {t}, next_ {n} {
}

template <class T>
SingleLL<T>* SingleLL<T>::add_ordered(SingleLL<T> *n) {
    if (n == nullptr) return this;
    if (this == nullptr) return n;
    if (value_ > n->value_) {
        n->next_ = this;
        return n;
    }
    SingleLL<T> *p = this;
    while (p->next_) {
        if (p->next_->value_ > n->value_) {
            n->next_ = p->next_;
            p->next_ = n;
            return n;
        }
    }
    p->next_ = n;
    return p;
}

template <class T>
SingleLL<T>* SingleLL<T>::find(const T &t) {
    SingleLL<T> *p = this;
    while (p) {
        if (p->value_ == t)
            return p;
        p = p->next_;
    }
    return nullptr;
}

template <class T>
const SingleLL<T>* SingleLL<T>::find(const T &t) const {
    const SingleLL<T> *p = this;
    while (p) {
        if (p->value_ == t)
            return p;
        p = p->next_;
    }
    return nullptr;
}

template <class T>
SingleLL<T>* SingleLL<T>::advance(int n) {
    SingleLL<T> *p = this;
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

template <class T>
const SingleLL<T>* SingleLL<T>::advance(int n) const {
    const SingleLL<T> *p = this;
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

template <class T>
void print_all(const SingleLL<T> *p) {
    std::cout << "{\n";
    while (p) {
        std::cout << p->value() << '\n';
        p = p->next();
    }
    std::cout << "}\n";
}

void test_link_int() {
    SingleLL<int> *isl {new SingleLL<int> {3}};
    isl = isl->add_ordered({new SingleLL<int> {5}});
    isl = isl->add_ordered({new SingleLL<int> {2}});
    print_all(isl);
}

void test_sinlgell() {
    SingleLL<God> *norse_gods {
        new SingleLL<God> {God {"Odin", "Norse", "Sleipnir", "Gungir"}}};
    norse_gods = norse_gods->add_ordered(
            new SingleLL<God> {God {"Thor", "Norse", "", "Hammer"}});
    norse_gods = norse_gods->add_ordered(
            new SingleLL<God> {God {"Freia", "Norse", "", ""}});
    print_all(norse_gods);
}

int main() {

    test_link_int();
    test_sinlgell();

    return 0;
}

