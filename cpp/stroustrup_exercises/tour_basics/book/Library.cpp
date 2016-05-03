#include "Library.h"

Library::Library(): books_{}, readers_{}, tr_vec_{} { }

Library::Library(const vector<Book> &b_vec, const vector<Patron> &p_vec,
                const vector<Transaction> &tr_vec):
    books_{b_vec}, readers_{p_vec}, tr_vec_{tr_vec} { }

vector<Book> Library::books() const {
    return books_;
}

vector<Patron> Library::readers() const {
    return readers_;
}

void Library::add_book(const Book &b) {
    books_.push_back(b);
}

void Library::add_patron(const Patron &p) {
    readers_.push_back(p);
}

void Library::check_book_out(Book &b, Patron &p) {
    const int bi = is_lib_book(b);
    if (bi < 0) {
        cerr << "error: The book is not in the library\n";
        return;
    }

    const int pi = is_lib_reader(p);
    if (pi < 0) {
        cerr << "error: There is no such patron in the library\n";
        return;
    }

    if (books_[bi].is_checkedout()) {
        cerr << "error: The book is already checked out\n";
        return;
    }

    if (readers_[pi].has_fee()) {
        cerr << "error: This patron owes a fee\n";
        return;
    }

    books_[bi].check_in();
    readers_[pi].set_fee(0.5);
    tr_vec_.push_back(Transaction{b, p, Chrono::Date{}});
}

int Library::is_lib_book(const Book &b) {
    for (size_t i = 0; i < books_.size(); ++i)
        if (books_[i] == b)
            return i;
    return -1;
}

int Library::is_lib_reader(const Patron &p) {
    for (size_t i = 0; i < readers_ .size(); ++i)
        if (readers_[i] == p)
            return i;
    return -1;
}

ostream &operator<<(ostream &os, const Library &ll) {
    os << "Books:\n";
    for (auto x: ll.books())
        os << '\t' << x << endl;
    os << "\nPatrons:\n";
    for (auto x: ll.readers())
        os << '\t' << x << endl;
    return os;
}

