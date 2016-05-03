#include <iostream>
#include <fstream>
#include <stdexcept>

using namespace std;

void disp_greetings(const int argc, char *argv[]) {
    for (int i {1}; i < argc; ++i)
        cout << "Greetings, " << argv[i] << "!\n";
}

void cat_files(const int argc, char *argv[]) {
    for (int i {1}; i < argc; ++i) {
        const string fn {argv[i]};
        ifstream ifs {fn};
        if (!ifs)
            throw runtime_error("cannot open file " + fn);
        for (string s; getline(ifs, s);)
            cout << s << endl;
    }
}

int main(int argc, char *argv[]) {

    //disp_greetings(argc, argv);
    cat_files(argc, argv);

    return 0;
}
