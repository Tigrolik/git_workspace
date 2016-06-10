#include <iostream>
#include <cstdarg>

void error(const std::string &s, ...) {
    va_list ap;
    va_start(ap, s);
    const size_t n {s.length()};
    for (size_t i {0}; i < n; ++i)
        if (s[i] == '%' && ++i < n) {
            switch (s[i]) {
                case 'd':
                    std::cerr << va_arg(ap, int);
                    break;
                case 'c':
                    std::cerr << char(va_arg(ap, int));
                    break;
                case 'f':
                    std::cerr << va_arg(ap, double);
                    break;
                case 's':
                    std::cerr << va_arg(ap, char*);
                    break;
            }
        } else {
            std::cerr << s[i];
        }
}

int main() {

    error("Test: digit: %d, char: %c, double: %f and string: %s\n",
            5, 'K', 3.9048, "symbols");

    return 0;
}

