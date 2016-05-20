#include <iostream>
#include <sstream>
#include <typeinfo>
#include <stdexcept>

//struct bad_from_string: std::bad_cast {
//    const char* what() const {
//        return "bad cast from string";
//    }
//};

template <class T>
std::string to_str(const T &t) {
    std::ostringstream os;
    os << t;
    return os.str();
}

template <class T>
T from_str(const std::string &s) {
    std::istringstream is {s};
    T t;
    if (!(is >> t))
        throw std::bad_cast();
    return t;
}

template <class T, class U>
T to(const U &u) {
    std::stringstream ss;
    T t;
    if (!(ss << u) || !(ss >> t) || !(ss >> std::ws).eof())
        throw std::bad_cast();
    return t;
}

void test_to_str() {
    std::cout << to_str(14.902) << '\n';
    std::cout << to_str(3 * 8 + 44 / 11 - 5) << '\n';
}

void convert_from_string(const std::string &s) {
    try {
        int i = from_str<int>(s);
        std::cout << i << '\n';
    } catch (const std::bad_cast &e) {
        std::cerr << e.what() << '\n';
    }
}

void convert_to_int() {
    try {
        int i = to<double>(7.2);
        std::cout << i << '\n';
    } catch (const std::bad_cast &e) {
        std::cerr << e.what() << '\n';
    }
}

void test_convert() {
    convert_from_string("37");
    convert_from_string("Ok, how are you doing?");
    convert_from_string("3.7");
    convert_to_int();
}

int main() {

    test_to_str();
    test_convert();

    return 0;
}

