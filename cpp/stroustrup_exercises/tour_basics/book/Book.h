/*
 * Book class
 * exercise from part 9 from Stroustrup book "Programming Principles"
 */

#ifndef _BOOK_H_
#define _BOOK_H_

#include "Chrono.h"

using namespace std;

enum class Genre {
    fiction, nonfiction, periodical, biography, children
};

class Book {
    public:
        class Invalid {}; // for throwing errors about invalid data

        // initialize: isbn, title, author, copyright data, genre
        // and check out status
        Book(const string&, const string&, const string&, const Chrono::Date&,
                const Genre&, const bool = false);
        Book();

        string isbn() const;
        string title() const;
        string author() const;
        Genre genre() const;
        Chrono::Date copyright_date() const;
        bool is_checkedout() const;

        void check_in();
        void check_out();

    private:
        string isbn_; // x-x-x-y: x is digit, y is alphanumeric
        string title_;
        string author_;
        Chrono::Date cr_date_; // copyright date
        Genre genre_;
        bool checked_out_;
};

const Book &default_book();

bool is_isbn(const string&);
bool is_genre(const Genre &g);

bool operator==(const Book&, const Book&);
bool operator!=(const Book&, const Book&);

ostream &operator<<(ostream&, const Book&);
// does not work yet
istream &operator>>(istream&, Book&);

#endif
