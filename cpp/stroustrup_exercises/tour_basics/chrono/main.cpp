#include "Chrono.h"
#include "Name_pairs.h"

void test_dates() {
    using namespace std;
    Chrono::Date today {1978, Chrono::Month::jun, 25};
    std::cout << today << std::endl;
    std::cout << Chrono::Date() << std::endl;
    std::cout << Chrono::Date(2004, Chrono::Month::jan, 30) << std::endl;
    cout << "enter a date: ";
    Chrono::Date d {};
    cin >> d;
    cout << d << endl;
}

void test_name_pairs() {
    Name_pairs np {};
    np.read_names();
    np.read_ages();
    np.sort();
    cout << np << endl;
    //np.print();
}

int main() {

    // test_dates();
    test_name_pairs();

    return 0;
}
