#ifndef _PUNCT_STREAM_H_
#define _PUNCT_STREAM_H_

#include <iostream>
#include <fstream>
#include <sstream>

using namespace std;

class Punct_stream {
    public:
        Punct_stream(istream& = cin);

        void whitespace(const string&);
        void add_white(const char);
        bool is_whitespace(const char) const;
        void case_sensitive(const bool);
        bool is_case_sensitive() const;

        Punct_stream &operator>>(string&);
        operator bool(); // turn Punct_stream into a bool

    private:
        istream &source_;   // character source
        istringstream buf_; // buf does formatting
        string white_;      // whitespace chars
        bool sensitive_;    // is the stream case-sensitive
};

#endif

