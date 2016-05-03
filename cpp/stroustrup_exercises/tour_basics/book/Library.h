#ifndef _LIBRARY_H_
#define _LIBRARY_H_

#include "Book.h"
#include "Patron.h"
#include "Chrono.h"
#include <vector>

struct Transaction {
    Book b;
    Patron p;
    Chrono::Date d;
};

class Library {
    public:
        Library();
        Library(const vector<Book>&, const vector<Patron>&,
                const vector<Transaction>&);

        vector<Book> books() const;
        vector<Patron> readers() const;

        void add_book(const Book&);
        void add_patron(const Patron&);
        void check_book_out(Book&, Patron&);

    private:
        vector<Book> books_;
        vector<Patron> readers_;
        vector<Transaction> tr_vec_;

        int is_lib_book(const Book&);
        int is_lib_reader(const Patron&);
};

ostream &operator<<(ostream&, const Library&);

#endif

