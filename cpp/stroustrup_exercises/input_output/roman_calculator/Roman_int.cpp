#include "Roman_int.h"

Roman_int::Roman_int(const std::string &s): roman_{s}, value_{as_int()} {
    if (value_ == -1)
        std::cout << "warning: the input is illegal, value set to -1\n";
}

Roman_int::Roman_int(const Roman_int &o):
    roman_{o.roman()}, value_{o.value()} { }

Roman_int &Roman_int::operator=(const Roman_int &o) {
    if (this == &o)
        return *this;
    roman_ = o.roman();
    value_ = o.value();
    return *this;
}

template <typename T>
T input_error(const std::string &s, T ret) {
    std::cerr << "error: " + s  + "\n";
    return ret;
}

/*
 * method reads a string containing Roman numeric symbols and returns either
 * the integer value if the input is legal or -1 otherwise
 */
int Roman_int::as_int() const {
    int val {0};
    size_t i {0};
    const size_t len {roman_.length()};
    bool has_DLV {false};
    for (size_t idx {0}; idx < symbols.length(); ++idx) {
        int reps {0};
        const char sym {symbols[idx]};
        if (~idx & 1) { // even indices (symbols M C X I)
            while ((i < len) && (roman_[i] == sym)) {
                if (++reps > 3)
                    return input_error("too many repetitions", -1);
                if (++i < len && idx > 1) {
                    if (roman_[i] == symbols[idx - 2] ||
                            roman_[i] == symbols[idx - 1]) {
                        if (reps > 1 || has_DLV)
                            return input_error("wrong input", -1);
                        val += (roman_[i] == symbols[idx - 2]) ?
                            roman_syms.at(symbols[idx - 2])-roman_syms.at(sym):
                            roman_syms.at(symbols[idx - 1])-roman_syms.at(sym);
                        ++i; break;
                    }
                }
                val += roman_syms.at(sym);
            }
        } else { // odd indices (symbols D L V)
            has_DLV = false;
            if (i < len && roman_[i] == sym) {
                ++i;
                val += roman_syms.at(sym);
                has_DLV = true;
            }
            if (i < len) {
                for (size_t j {0}; j < idx; ++j)
                    if (roman_[i] == symbols[j])
                        return input_error("wrong input", -1);
                if (roman_[i] == sym && has_DLV)
                    return input_error("wrong input", -1);
            }
        }
        if (i == len)
            return val;
    }
    if (i < len)
        return input_error("wrong input", -1);
    return val;
}

Roman_int Roman_int::operator+(const Roman_int &r) {
    return Roman_int {int_to_roman(value_ + r.value())};
}

Roman_int Roman_int::operator-(const Roman_int &r) {
    return Roman_int {int_to_roman(value_ - r.value())};
}

Roman_int Roman_int::operator*(const Roman_int &r) {
    return Roman_int {int_to_roman(value_ * r.value())};
}

Roman_int Roman_int::operator/(const Roman_int &r) {
    return Roman_int {int_to_roman(value_ / r.value())};
}

Roman_int Roman_int::operator%(const Roman_int &r) {
    return Roman_int {int_to_roman(value_ % r.value())};
}

std::ostream &operator<<(std::ostream &os, const Roman_int &r) {
    return os << r.roman() << ": " << r.value();
}

std::istream &operator>>(std::istream &is, Roman_int &r) {
    std::string s;
    is >> s;
    if (!is)
        return is;
    r = Roman_int {s};
    return is;
}

constexpr int int_pow(const int x, const int p) {
    return (p > 0) ? (p > 1) ? x * int_pow(x, p - 1) : x : 1;
}

std::string int_to_roman(const int x) {
    if (x > max_roman_int || x < 0)
        return input_error("wrong input", "");
    std::string s {""};
    for (auto i = 0; i < 4; ++i) { // 100s 10s and 1s
        const int t {x / int_pow(10, 3 - i) % 10};
        const int idx {i << 1};
        if (t) {
            if (t == 9 || t == 4) {
                s += symbols[idx];
                s += (t==9) ? symbols[idx-2] : symbols[idx-1];
            } else {
                if (t > 4)
                    s += symbols[idx - 1];
                if (t < 4 || t > 5)
                    s += std::string(t - 5 * (t / 5), symbols[idx]);
            }
        }
    }
    return s;
}

bool is_valid_roman(const std::string &s) {
    size_t i {0};
    const size_t len {s.length()};
    bool has_DLV {false};
    for (size_t idx {0}; idx < symbols.length(); ++idx) {
        int reps {0};
        const char sym {symbols[idx]};
        if (~idx & 1) { // even indices (symbols M C X I)
            while ((i < len) && (s[i] == sym)) {
                if (++reps > 3)
                    return false;
                if (++i < len && idx > 1) {
                    if (s[i] == symbols[idx - 2] || s[i] == symbols[idx - 1]) {
                        if (reps > 1 || has_DLV)
                            return false;
                        ++i; break;
                    }
                }
            }
        } else { // odd indices (symbols D L V)
            has_DLV = false;
            if (i < len && s[i] == sym) {
                ++i;
                has_DLV = true;
            }
            if (i < len) {
                for (size_t j {0}; j < idx; ++j)
                    if (s[i] == symbols[j])
                        return false;
                if (s[i] == sym && has_DLV)
                    return false;
            }
        }
        if (i == len)
            return true;
    }
    if (i < len)
        return false;
    return true;
}

// assume that the string is correct
std::string uncompact(const std::string &s) {
    std::string ss {""};
    size_t i {0};
    const size_t len {s.length()};
    for (size_t idx {0}; idx < symbols.length(); ++idx) {
        const char sym {symbols[idx]};
        if (~idx & 1) {
            while ((i < len) && (s[i] == sym)) {
                if (++i < len && idx > 1) {
                    if (s[i] == symbols[idx - 2] || s[i] == symbols[idx - 1]) {
                        if (s[i] == symbols[idx - 2])
                            ss += symbols[idx - 1];
                        ss += std::string(4, sym);
                        ++i; break;
                    }
                }
                ss += sym;
            }
        } else if (i < len && s[i] == sym) {
            ++i;
            ss += sym;
        }
        if (i == len)
            return ss;
    }
    return ss;
}

//std::string compact(const std::string &s) {
//}

