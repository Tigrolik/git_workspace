#include <iostream>

void test_align() {
    using namespace std;

    struct Compact {
        long double g;
        long y;
        double d;
        int x;
        bool b;
        char c;
    };

    struct Sparse {
        bool b;
        long double g;
        char c;
        long y;
        double d;
        int x;
    };

    cout << "Size of the compact structure: " << sizeof(Compact);
    cout << ", alignment = " << alignof(Compact) << endl;

    cout << "Size of the sparse structure: " << sizeof(Sparse);
    cout << ", alignment = " << alignof(Sparse) << endl;
}

void months_structs() {
    struct smonth {
        const char *name;
        const int num_days;
    };
    const int n = 12;
    // array of structs
    smonth year[n] {{"Jan", 31}, {"Feb", 29}, {"Mar", 31}, {"Apr", 30},
        {"May", 31}, {"Jun", 30}, {"Jul", 31}, {"Aug", 31}, {"Sep", 30},
        {"Oct", 31}, {"Nov", 30}, {"Dec", 31}};
    // arrays for names and days separately
    const char *m_names[n] {"Jan", "Feb", "Mar", "Apr", "May", "Jun", "Jul",
        "Aug", "Sep", "Oct", "Nov", "Dec"};
    const int m_days[n] {31, 29, 31, 30, 31, 30, 31, 31, 30, 31, 30, 31};

    using namespace std;
    for (auto i = 0; i < n; ++i) {
        const smonth y = year[i];
        cout << "Struct: " << y.name << ": " << y.num_days;
        cout << " days; ";
        cout << "Arrays: " << m_names[i] << ": " << m_days[i];
        cout << " days ";
    }
    cout << "\b\n";
}

int main()
{
    test_align();
    // months_structs();

    return 0;
}
