#ifndef _PATRON_H_
#define _PATRON_H_

#include "Book.h"

class Patron {
    public:
        Patron();
        Patron(const string&, const int, const double = 0.0);

        string name() const;
        int card_num() const;
        double fee() const;

        bool has_fee() const;
        void set_fee(const double = 1.0);

    private:
        string name_;
        int card_num_;
        double fee_;
};

const Patron &default_patron();

bool operator==(const Patron&, const Patron&);
bool operator!=(const Patron&, const Patron&);

ostream &operator<<(ostream&, const Patron&);
istream &operator>>(istream&, Patron&);

#endif

