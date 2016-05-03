#include "../my_facilities.h"
#include <fstream>

struct Point {
    int x {};
    int y {};
};

ostream &operator<<(ostream &os, const Point &p) {
    return os << '(' << p.x << ", " << p.y << ')';
}

istream &operator>>(istream &is, Point &p) {
    // input points in format (x, y)
    char ch1;
    is >> ch1;
    if (ch1 != '(') {
        is.unget();
        is.clear(ios_base::failbit);
        return is;
    }

    int x, y;
    char ch2, ch3;
    is >> x >> ch2 >> y >> ch3;
    if (!is || ch2 != ',' || ch3 != ')')
        error("Bad input");
    p.x = x;
    p.y = y;
    return is;
}

constexpr bool operator==(const Point &p1, const Point &p2) {
    return (p1.x == p2.x) && (p1.y == p2.y);
}

void read_vec() {
    const string fn {"mydata.txt"};

    // --- read entered data into file ---
    ofstream ost {fn};
    if (!ost)
        error("cannot open file " + fn);

    constexpr int num_points {3};
    cout << "Enter " << num_points << " point in format (x, y):\n";

    // throw exception if ost goes bad
    ost.exceptions(ost.exceptions() | ios_base::badbit);

    vector<Point> original_points;
    for (auto i = 0; i < num_points; ++i) {
        Point p;
        cin >> p;
        ost << p << endl; // write points to the file
        original_points.push_back(p);
    }
    ost.close();
    // --- end reading ---

    // --- read data from file ---
    ifstream ist {fn};
    if (!ist)
        error("cannot open file " + fn);

    ist.exceptions(ist.exceptions() | ios_base::badbit);

    // read points from the file
    vector<Point>processed_points;
    for (Point p; ist >> p;) {
        processed_points.push_back(p);
        if (ist.fail()) {
            ist.unget();
            ist.clear(ios_base::failbit);
        }
    }
    ist.close();
    // --- end reading ---

    cout << original_points << endl;
    cout << processed_points << endl;
    if (!compare(original_points, processed_points))
        error("Something is wrong!");
}

void read_sum(const string &fn) {
    ifstream ifs {fn};
    if (!ifs)
        error("cannot open file " + fn);
    ifs.exceptions(ifs.exceptions() | ios_base::badbit);
    double sum {0.0};
    for (double d; ifs >> d;) {
        sum += d;
        if (ifs.fail()) {
            ifs.unget();
            ifs.clear(ios_base::failbit);
        }
    }
    cout << "The sum = " << sum << endl;
}

int main() {

    read_vec();
    //read_sum("nums.txt");

    return 0;
}
