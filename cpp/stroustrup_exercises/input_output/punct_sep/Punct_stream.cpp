#include "Punct_stream.h"

// note: source_ is initialized with basic brackets
Punct_stream::Punct_stream(istream &is): source_(is), buf_{},
    white_{""}, sensitive_{true} { }

void Punct_stream::whitespace(const string &s) {
    white_ = s;
}

void Punct_stream::add_white(const char w) {
    white_ += w;
}

bool Punct_stream::is_whitespace(const char c) const {
    for (auto w: white_)
        if (c == w)
            return true;
    return false;
}

void Punct_stream::case_sensitive(const bool b) {
    sensitive_ = b;
}

inline bool Punct_stream::is_case_sensitive() const {
    return sensitive_;
}

Punct_stream &Punct_stream::operator>>(string &s) {
    while (!(buf_ >> s)) {
        if (buf_.bad() || !source_.good())
            return *this;
        buf_.clear();

        string line;
        getline(source_, line);

        for (auto &c: line)
            if (is_whitespace(c))
                c = ' ';
            else if (!sensitive_)
                c = tolower(c);
        buf_.str(line); // put the string into stream
    }
    return *this;
}

Punct_stream::operator bool() {
    return !(source_.fail() || source_.bad()) && source_.good();
}

