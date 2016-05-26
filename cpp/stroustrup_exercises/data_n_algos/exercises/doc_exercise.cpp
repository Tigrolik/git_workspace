#include <iostream>
#include "Document.h"

void print_doc(Document &d, Text_iterator p) {
    for (; p != d.end(); ++p) cout << *p;
}

void test_doc() {
    const string fn {"sample_text.txt"};
    ifstream ifs {fn};
    if (!ifs)
        throw runtime_error("cannot open file " + fn);
    // reading and displaying test
    Document d {}; ifs >> d;
    cout << d;

    // find text test
    auto p = d.find_text(d.begin(), d.end(), "here it");
    if (p == d.end()) {
        cout << "not found\n";
    } else {
        cout << "found\n";
        print_doc(d, p);
    }
    d.find_and_replace(d.begin(), d.end(), "here it", "It it not here");
    cout << d;
    d.erase_line(1); d.erase_line(1); d.erase_line(1); d.erase_line(1);
    cout << d;
    cout << "number of characters: " << d.count_char() << '\n';
    cout << "number of words: " << d.count_words() << '\n';
    const string wspace {"."};
    cout << "number of words: with white-space characters " + wspace + " = "<<
        d.count_words(wspace) << '\n';
}

int main() {

    test_doc();

    return 0;
}

