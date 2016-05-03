#include "Book.h"
#include "Patron.h"
#include "Library.h"

void test_book() {
    using namespace Chrono;
    // Date d {2013, Month::apr, 12};
    //Book b1 {"7-4-5-H", "Joy", "James", Date{2013, Month::sep, 14},
    //    Genre::fiction};
    //Book b2 {"7-4-5-H", "Happiness", "Mary", Date{2002, Month::jun, 7},
    //    Genre::biography};

    //std::cout << b1 << std::endl;
    //std::cout << b2 << std::endl;
    // std::cout << (b1 == b2) << std::endl;

    Book b {};
    std::cout << b << std::endl;
    //std::cin >> b;
    //std::cout << b << std::endl;
}

void test_patron() {
    Patron p {};
    //cout << p << endl;
    p = Patron {"Joe", 123789, 2.34};
    Patron p2 {"Joe", 123789, 2.35};
    cout << p << endl;
    if (p == p2)
        cout << "True\n";
    else
        cout << "False\n";
    //cout << "Enter a name and card number:\n";
    //cin >> p;
    //cout << p << endl;
}

void test_library() {
    Library l {};

    using namespace Chrono;
    Book b1 {"7-4-5-H", "Joy", "James", Date{2013, Month::sep, 14},
        Genre::fiction};
    Book b2 {"2-3-5-k", "Happiness", "Mary", Date{2002, Month::jun, 7},
        Genre::biography};
    Book b3 {"8-1-4-m", "Illusion", "Peter", Date{1938, Month::oct, 21},
        Genre::children};
    l.add_book(b1);
    l.add_book(b2);
    l.add_book(b3);

    Patron p1 {"Joe", 123789, 2.34};
    Patron p2 {"Alex", 378209};
    Patron p3 {"Joe", 203894, 0.5};
    l.add_patron(p1);
    l.add_patron(p2);
    l.add_patron(p3);

    cout << l << endl;

    Book b4 {"3-1-4-m", "Big", "Nelson", Date{1989, Month::dec, 1},
        Genre::children};
    l.check_book_out(b1, p1);
    l.check_book_out(b4, p1);
    l.check_book_out(b2, p2);
    p2.set_fee();
    cout << l << endl;

    l.check_book_out(b3, p2);
}

void test_date() {
    Chrono::Date today {1978, Chrono::Month::jun, 25};
    std::cout << today << std::endl;
    std::cout << Chrono::Date() << std::endl;
    std::cout << Chrono::Date(2004, Chrono::Month::jan, 30) << std::endl;
    cout << day_of_week(Chrono::Date(2016, Chrono::Month::jan, 25)) << endl;
    cout << next_workday(Chrono::Date(2016, Chrono::Month::mar, 25)) << endl;
    //cout << "enter a date: ";
    //Chrono::Date d {};
    //cin >> d;
    //cout << d << endl;
}

int main() {

    test_date();
    // test_book();
    // test_patron();
    // test_library();

    return 0;
}
