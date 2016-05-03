/*
 * The program implements temperature readings
 */

#include "Readings.h"

void read_to_file(const string &fn) {
    ofstream ofs {fn};
    if (!ofs)
        error("cannot open file " + fn);
    ofs.exceptions(ofs.exceptions() | ios_base::badbit); // throw for bad()

    vector<Year> ys;
    for (Year y; cin >> y;) {
        ofs << y << endl;
        ys.push_back(y);
    }
    ofs.close();

    cout << "Read " << ys.size() << " years of readings\n";
}

void test_reading() {
    read_to_file("raw_temps.txt");
}

int main() {

    test_reading();

    return 0;
}
