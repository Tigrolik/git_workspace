#include "Patron.h"

const Patron &default_patron() {
    static const Patron pp {"", 0, 0.0};
    return pp;
}

Patron::Patron(const string &n, const int cn, const double f):
        name_{n}, card_num_{cn}, fee_{f} { }

Patron::Patron(): name_{default_patron().name()},
    card_num_{default_patron().card_num()}, fee_{default_patron().fee()} { }

string Patron::name() const {
    return name_;
}

int Patron::card_num() const {
    return card_num_;
}

double Patron::fee() const {
    return fee_;
}

bool Patron::has_fee() const {
    return (fee_ != 0);
}

void Patron::set_fee(const double f) {
    fee_ = f;
}

bool operator==(const Patron &p1, const Patron &p2) {
    return (p1.name() == p2.name()) && (p1.card_num() == p2.card_num());
}

bool operator!=(const Patron &p1, const Patron &p2) {
    return !(p1 == p2);
}

ostream &operator<<(ostream &os, const Patron &p) {
    os << "Name: " << p.name() << ", card number: " << p.card_num();
    if (p.fee() != 0)
        os << ", fee: " << p.fee();
    return os;
}

istream &operator>>(istream &is, Patron &pp) {
    string n {};
    int cn;
    is >> n >> cn;
    if (!is)
        return is;
    pp = Patron {n, cn};
    return is;
}

