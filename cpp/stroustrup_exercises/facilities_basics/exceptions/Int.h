#ifndef INT_H
#define INT_H

#include <limits>

class Int {
    int val_;
public:
    class Underflow_error { };
    class Overflow_error { };

    Int(const long int val): val_(val) {
        if (val < min_value())
            throw Underflow_error{};
        else if (val > max_value())
            throw Overflow_error{};
    }

    static constexpr int max_value() {return std::numeric_limits<int>::max();}
    static constexpr int min_value() {return std::numeric_limits<int>::min();}
    friend std::ostream& operator<<(std::ostream &os, const Int &i) {
        return os << i.val_;
    }
};


#endif

