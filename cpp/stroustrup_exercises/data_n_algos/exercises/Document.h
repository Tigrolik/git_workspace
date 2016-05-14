#ifndef DOCUMENT_H
#define DOCUMENT_H

#include <fstream>
#include <vector>
#include <list>
#include <algorithm>

using namespace std;
using Line = vector<char>;

class Text_iterator {
public:
    // start iterator at line ll's character position pp
    Text_iterator(list<Line>::iterator ll, Line::iterator pp): ln{ll}, pos{pp} {
    }
    char& operator*() { return *pos; }
    Text_iterator& operator++(); // prefix
    //Text_iterator operator++(int); // postfix

    list<Line>::iterator get_line() { return ln; }
    Line::iterator get_pos() { return pos; }

    bool operator==(const Text_iterator &o) const {
        return ln == o.ln && pos == o.pos;
    }
    bool operator!=(const Text_iterator &o) const { return !(*this == o); }

private:
    list<Line>::iterator ln;
    Line::iterator pos;
};

Text_iterator& Text_iterator::operator++() {
    if (++pos == ln->end()) pos = (++ln)->begin();
    return *this;
}

//Text_iterator Text_iterator::operator++(int) {
//    Text_iterator t = *this;
//    ++*this;
//    return t;
//}

template <class Iter>
bool match(Iter first, Iter last, const string &s) {
    auto s_iter = begin(s);
    while (first != last && s_iter != end(s)) {
        if (*first != *s_iter) return false;
        ++first; ++s_iter;
    }
    return true;
}

template <class Iter, class T>
Iter my_find(Iter first, Iter last, const T& val) {
    while (first != last) {
        if (*first == val)
            return first;
        ++first;
    }
    return first;
}

bool is_white_space(const char c, const string& wspace) {
    for (size_t i {0}; i < wspace.length(); ++i)
        if (c == wspace[i]) return true;
    return false;
}

struct Document {
    list<Line> line;
    Document() { line.push_back(Line {}); }

    Text_iterator begin() {
        return Text_iterator(line.begin(), (*line.begin()).begin());
    }
    Text_iterator end() {
        auto last = line.end();
        --last;
        return Text_iterator(last, (*last).end());
    }
    Text_iterator find_text(Text_iterator first, Text_iterator last,
            const string &s) {
        if (s.size() == 0) return last;
        char first_char = s[0];
        while (true) {
            auto p = my_find(first, last, first_char);
            if (p == last || match(p, last, s)) return p;
            first = ++p;
        }
    }

    Text_iterator erase(Text_iterator pos) {
        list<Line>::iterator li = pos.get_line();
        Line::iterator pi = pos.get_pos();
        pi = (*li).erase(pi);
        return Text_iterator(li, pi);
    }

    Text_iterator insert(Text_iterator pos, const char &ch) {
        list<Line>::iterator li = pos.get_line();
        Line::iterator pi = pos.get_pos();
        pi = (*li).insert(pi, ch);
        return Text_iterator(li, pi);
    }

    void erase_line(const size_t n) {
        if (n >= line.size() - 1) return;
        auto p = line.begin();
        advance(p, n);
        line.erase(p);
    }

    void concat(Text_iterator &p) {
        list<Line>::iterator cur_line = p.get_line();
        Line::iterator line_pos = p.get_pos();
        size_t idx = line_pos - (*cur_line).begin();
        list<Line>::iterator next_line = cur_line;
        ++next_line;
        (*cur_line).insert((*cur_line).end(), (*next_line).begin(),
                (*next_line).end());
        p = Text_iterator(cur_line, (*cur_line).begin() + idx);
        // find number of line to erase
        list<Line>::iterator li = begin().get_line();
        int line_ctr = 0;
        while (li != next_line) {
            ++li; ++line_ctr;
        }
        erase_line(line_ctr);
    }

    // move the rest of line to beginning of next line
    void break_line(Text_iterator p) {
        list<Line>::iterator cur_line = p.get_line();
        list<Line>::iterator next_line = cur_line;
        ++next_line;
        (*next_line).insert((*next_line).begin(), p.get_pos() + 1,
                (*cur_line).end());
        (*cur_line).erase(p.get_pos() + 1, (*cur_line).end());
    }

    void find_and_replace(Text_iterator first, Text_iterator last,
            const string &s_find, const string &s_repl) {
        const size_t s1 {s_find.size()}, s2 {s_repl.size()};
        if (s1 == 0 || s2 == 0) return;
        Text_iterator p = find_text(first, last, s_find);
        while (p != last) {
            string::const_iterator find_it = s_find.begin();
            string::const_iterator repl_it = s_repl.begin();
            while (find_it != s_find.end() && repl_it != s_repl.end()) {
                if (*find_it != *repl_it) {
                    *p = *repl_it;
                    if (*find_it == '\n')
                        concat(p);
                    if (*repl_it == '\n')
                        break_line(p);
                }
                ++p; ++find_it; ++repl_it;
            }
            while (find_it != s_find.end()) {
                if (*p == '\n')
                    concat(p);
                p = erase(p);
                ++find_it;
            }
            while (repl_it != s_repl.end()) {
                p = insert(p, *repl_it);
                if (*repl_it == '\n')
                    break_line(p);
                ++p; ++repl_it;
            }
            p = find_text(p, last, s_find);
        }
    }

    size_t count_char() {
        size_t c {0};
        for (auto p: line)
            for (auto x: p)
                if (!isspace(x))
                    ++c;
        return c;
    }

    size_t count_words() {
        size_t c {0};
        for (auto p: line) {
            Line::iterator pos = p.begin();
            while (pos != p.end()) {
                if (!isspace(*pos)) {
                    while (!isspace(*pos)) ++pos;
                    ++c;
                }
                //if (isalpha(*pos)) {
                //    while (isalpha(*pos)) ++pos;
                //    ++c;
                //}
                ++pos;
            }
        }
        return c;
    }

    size_t count_words(const string& wspace) {
        size_t c {0};
        Text_iterator p = begin();
        while (p != end()) {
            if (!is_white_space(*p, wspace)) {
                while (p != end() && !is_white_space(*p, wspace))
                    ++p;
                ++c;
            }
            if (p != end())
                ++p;
        }
        return c;
    }
};

Text_iterator begin(Document &d) {
    return d.begin();
}

istream& operator>>(istream &is, Document &d) {
    for (char ch; is.get(ch);) {
        d.line.back().push_back(ch); // add a character
        if (ch == '\n')
            d.line.push_back(Line {}); // add a new line
    }
    if (d.line.back().size()) d.line.push_back(Line {}); // add final empty line
    return is;
}

ostream& operator<<(ostream &os, Document &d) {
    for (auto p: d) os << p;
    return os;
}

#endif

