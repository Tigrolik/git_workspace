#include <iostream>
#include "Date.h"

std::ostream& operator<<(std::ostream& os, const char *s) {
    return os << "Initialize\n" + std::string(s) + "Clean up\n";
}

int main() {

    Chrono::Date d {};
    std::cout << d << '\n';
    std::cout << "Hello, World!\n";

    return 0;
}

