#ifndef _ROMAN_INT_H_
#define _ROMAN_INT_H_

#include <iostream>
#include <map>

static const std::string symbols {"MDCLXVI"};
static const std::map<char, int> roman_syms {{'I', 1}, {'V', 5}, {'X', 10},
    {'L', 50}, {'C', 100}, {'D', 500}, {'M', 1000}};
static constexpr int max_roman_int {3999};

//static constexpr char roman_I {'I'}; // one
//static constexpr char roman_V {'V'}; // five
//static constexpr char roman_X {'X'}; // ten
//static constexpr char roman_L {'L'}; // fify
//static constexpr char roman_C {'C'}; // hundred
//static constexpr char roman_D {'D'}; // five hundred
//static constexpr char roman_M {'M'}; // thousand
//
//enum class Roman {
//    I = 1, V = 5, X = 10, L = 50, C = 100, D = 500, M = 1000
//};

class Roman_int {
    public:
        Roman_int(const std::string& = "");
        Roman_int(const Roman_int&);
        Roman_int &operator=(const Roman_int&);

        std::string roman() const { return roman_; }
        int value() const { return value_; }
        int as_int() const;

        Roman_int operator+(const Roman_int&);
        Roman_int operator-(const Roman_int&);
        Roman_int operator*(const Roman_int&);
        Roman_int operator/(const Roman_int&);
        Roman_int operator%(const Roman_int&);

        friend std::ostream &operator<<(std::ostream&, const Roman_int&);
        friend std::istream &operator>>(std::istream&, Roman_int&);

    private:
        std::string roman_;
        int value_;
};

std::string int_to_roman(const int);
bool is_valid_roman(const std::string&);
std::string uncompact(const std::string&);
//std::string compact(const std::string&);

#endif

