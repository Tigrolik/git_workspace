#include <iostream>
#include <sstream>
#include <map>

using namespace std;

double expr(bool);
double term(bool);
double prim(bool);

static int no_of_errors;
static map<string, double> table;

enum class Kind: char {
    name, number, end,
    plus = '+', minus = '-', mul = '*', div = '/',
    print = ';', assign = '=', lp = '(', rp = ')'
};

struct Token {
    Kind kind;
    string string_value;
    double number_value;
};

class Token_stream {
    public:
        Token_stream(istream &s): ip{&s}, owns{false} { }
        Token_stream(istream *p): ip{p}, owns{true} { }

        ~Token_stream() { close(); }

        Token get();
        Token &current() { return ct; };

        void set_input(istream &s) {
            close();
            ip = &s;
            owns = false;
        }

        void set_input(istream *p) {
            close();
            ip = p;
            owns = true;
        }
    private:
        void close() {
            if (owns)
                delete ip;
        }
        istream *ip;
        bool owns;
        Token ct {Kind::end};
};

Token_stream ts {cin};

double error(const string &s) {
    ++no_of_errors;
    cerr << "Error: " << s << endl;
    return 1;
}

Token Token_stream::get() {
    char ch {0};

    do
        if (!ip->get(ch))
            return ct = {Kind::end};
    while (ch != '\n' && isspace(ch));

    *ip >> ch;
    switch (ch) {
        case 0:
            return ct = {Kind::end};
        case ';':
        case '*':
        case '/':
        case '+':
        case '-':
        case '(':
        case ')':
        case '=':
            return ct = {static_cast<Kind>(ch)};
        case '0': case '1': case '2': case '3': case '4': case '5': case '6':
        case '7': case '8': case '9': case '.':
            ip->putback(ch);
            *ip >> ct.number_value;
            ct.kind = Kind::number;
            return ct;
        default:
            if (isalpha(ch)) {
                ct.string_value = ch;
                while (ip->get(ch) && isalnum(ch))
                    ct.string_value += ch;
                ip->putback(ch);
                return ct = {Kind::name};
            }
            error("Bad token");
            return ct = {Kind::print};
    }
}

double expr(bool get) {
    double left = term(get);
    for (;;) {
        switch (ts.current().kind) {
            case Kind::plus:
                left += term(true);
                break;
            case Kind::minus:
                left -= term(true);
                break;
            default:
                return left;
        }
    }
}

double term(bool get) {
    double left = prim(get);
    while (true) {
        switch (ts.current().kind) {
            case Kind::mul:
                left *= term(true);
                break;
            case Kind::div:
                if (auto d = prim(true)) {
                    left /= d;
                    break;
                }
                return error("Divide by zero");
            default:
                return left;
        }
    }
}


double prim(bool get) {
    if (get)
        ts.get();
    switch (ts.current().kind) {
        case Kind::number:
            {
                double v = ts.current().number_value;
                ts.get();
                return v;
            }
        case Kind::name:
            {
                double v = table[ts.current().string_value];
                if (ts.get().kind == Kind::assign)
                    v = expr(true);
                return v;
            }
        case Kind::minus:
            return -prim(true);
        case Kind::lp:
            {
                auto e = expr(true);
                if (ts.current().kind != Kind::rp)
                    return error("')' expected");
                ts.get();
                return e;
            }
        default:
            return error("Primary expected");
    }
}

void calculate() {
    for (;;) {
        ts.get();
        if (ts.current().kind == Kind::end)
            break;
        if (ts.current().kind == Kind::print)
            continue;
        cout << expr(false) << endl;
    }
}

int main(int argc, char *argv[]) {
    switch (argc) {
        case 1:
            break;
        case 2:
            ts.set_input(new istringstream{argv[1]});
            break;
        default:
            error("too many arguments");
            return 1;
    }

    table["pi"] = 3.1415926535897932385;
    table["e"] = 2.7182818284590452354;

    calculate();

    return no_of_errors;
}
