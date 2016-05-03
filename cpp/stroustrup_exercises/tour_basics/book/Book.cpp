#include "Book.h"

Book::Book(const string &i, const string &t, const string &a,
        const Chrono::Date &d, const Genre &g, const bool b):
    isbn_{i}, title_{t}, author_{a}, cr_date_{d}, genre_{g}, checked_out_{b}
{
    if (!is_isbn(i) || !is_genre(g))
        throw Invalid{};
}

Book::Book(): isbn_{default_book().isbn()}, title_{default_book().title()},
    author_{default_book().author()}, cr_date_{default_book().copyright_date()},
    genre_{default_book().genre()},
    checked_out_{default_book().is_checkedout()} {
}

string Book::isbn() const {
    return isbn_;
}

string Book::title() const {
    return title_;
}

string Book::author() const {
    return author_;
}

Genre Book::genre() const {
    return genre_;
}

Chrono::Date Book::copyright_date() const {
    return cr_date_;
}

bool Book::is_checkedout() const {
    return checked_out_;
}

void Book::check_in() {
    checked_out_ = false;
}

void Book::check_out() {
    checked_out_ = true;
}

const Book &default_book() {
    static const Book bb {"0-0-0-0", "C++", "Stroustrup",
        Chrono::Date{2014, Chrono::Month::aug, 28}, Genre::children, false};
    return bb;
}

bool is_isbn(const string& s) {
    return ((s.size() == 7) && (isdigit(s[0]) && (s[1] == '-') &&
                isdigit(s[2]) && (s[3] == '-') && isdigit(s[4]) &&
                (s[5] == '-') && isalnum(s[6])));
}

bool is_genre(const Genre &g) {
    return (g >= Genre::fiction) || (g <= Genre::children);
}

bool operator==(const Book &b1, const Book &b2) {
    return b1.isbn() == b2.isbn();
}

bool operator!=(const Book &b1, const Book &b2) {
    return !(b1 == b2);
}

ostream &operator<<(ostream &os, const Book &b) {
     return os << "Title: " << b.title() << "\nauthor: " << b.author() <<
         "\ngenre: " << static_cast<int>(b.genre()) << "\nISBN " << b.isbn();
}

istream &operator>>(istream &is, Book &bb) {
    // does not work yet
    cout << "Enter title, author, genre, isbn and copyright date:\n";
    string t {}, a {}, i {};
    Chrono::Date d {};
    int g_id {};
    char ch1, ch2, ch3, ch4, ch5, ch6;
    is >> ch1 >> t >> ch2 >> ch3 >> ch4 >> a >> ch5 >> ch6 >> g_id;
    if (ch1 != '"' || ch2 != '"' || ch3 != ',' || ch4 != '"' || ch5 != '"' ||
            ch6 != ',') {
        cerr << "Wrong input\n";
        is.clear(ios_base::failbit);
        return is;
    }
    if (!is)
        return is;
    bb = Book {i, t, a, Chrono::Date{}, Genre(g_id)};
    return is;
}

