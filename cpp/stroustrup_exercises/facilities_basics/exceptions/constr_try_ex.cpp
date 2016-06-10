#include <iostream>
#include <vector>

class X {
    std::vector<int> vi;
    std::vector<std::string> vs;
public:
    X(const int, const int);
};

X::X(const int sz1, const int sz2) try: vi(sz1), vs(sz2) { }
catch (std::exception &e) {
    std::cerr << e.what() << '\n';
}

int main() {

    return 0;
}

