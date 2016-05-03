/*
 * This program is a simple calculator based on chapters 6 and 7 from
 * "Principles and Practice using C++" by Bjarne Stroustrup
 * Input:  cin
 * Output: cout
 *
 * Calculator operates with floating-point numbers (using type double)
 *
 * Calculator allows use of variables: combination of letters, digits and
 * underscore, cannot start with a digit
 *
 * The grammar:
 *
 * Calculation:
 *    Statement
 *    Print
 *    Quit
 *    Calculation Statement
 *
 * Statement:
 *    Declaration
 *    Expression
 *
 * Declaration
 *    "let" Name '=' Expression
 *
 * Print:
 *    ';' (the symbol can be changed in the code)
 *
 * Quit:
 *    'q' (can be changed)
 *
 * Expression:
 *    Term
 *    Expression '+' Term
 *    Expression '-' Term
 *
 * Term:
 *    Primary
 *    Term '*' Prefix
 *    Term '/' Prefix
 *    Term '%' Prefix (for floats return x - y * int(x / y))
 *
 * Prefix:
 *    Postfix
 *    '-' Postfix
 *    '+' Postfix
 *
 * Postfix:
 *    Func
 *    Func '!' (factorial)
 *
 * Func:
 *    Primary
 *    "sqrt" '(' Expression ')'
 *    "pow"  '(' Expression ',' Expression ')'
 *
 * Primary:
 *    Number
 *    '(' Expression ')'
 *    '{' Expression '}'
 *
 * Number:
 *    floating-point-literal
 */

#include <iostream>
#include <vector>
#include <map>
#include <stdexcept>
#include <algorithm>

using namespace std;

static int no_of_errors {0};
static map<string, double> table;

// constants
static constexpr char let         {'L'};
static constexpr char inv         {'I'};
static constexpr char quit        {'q'};
static constexpr char help        {'h'};
static constexpr char Help        {'H'};
static constexpr char print       {';'};
static constexpr char comma       {','};
static constexpr char number      {'8'};
static constexpr char name        {'a'};
static constexpr char decl_label  {'#'};
static constexpr char sqrt_label  {'s'};
static constexpr char power_label {'p'};
static const string decl_key    {"let"};
static const string inv_key   {"const"};
static const string sqrt_key   {"sqrt"};
static const string power_key   {"pow"};
static const string prompt       {"> "};
static const string result       {"= "};

enum class Kind: char {
    name, number, end = quit, help = help, Help = Help,
    plus = '+', minus = '-', mul = '*', div = '/',
    lfp = '{', rfp = '}', lp = '(', rp = ')',
    fact = '!', mod = '%', print = ';', assign = '=',
    let = let, inv = inv
};

// Two functions to keep a window open in Windows OS
inline void keep_window_open() {
    char ch;
    cin >> ch;
}

inline void keep_window_open(const string &s)
{
    if (s == "")
        return;
    cin.clear();
    cin.ignore(120,'\n');
    while (true) {
        cout << "Please enter " << s << " to exit\n";
        string ss;
        while (cin >> ss && ss != s)
            cout << "Please enter " << s << " to exit\n";
        return;
    }
}

inline double error(const string &s)
{
    ++no_of_errors;
    throw runtime_error(s);
    return 1;
}

constexpr unsigned int factorial(const unsigned int n) {
    return ((n == 0) || (n == 1)) ? 1 : n * factorial(n - 1);
}

struct Token {
    public:
        Kind kind;     // kind of token
        double value;  // for numbers: a value
        string name;   // name for a variable

        //Token(const char ch): kind{static_cast<Kind>(ch)}, value{0}, name{} { }
        //Token(const char ch, const double val): kind {ch}, value {val}, name {}
        //{ }
        //Token(const char ch, const string s): kind {ch}, value {}, name {s} { }
};

//class Token {
//    public:
//        Kind kind;     // kind of token
//        double value;  // for numbers: a value
//        string name;   // name for a variable
//
//        Token(const char ch): kind{static_cast<Kind>(ch)}, value{0}, name{} { }
//        //Token(const char ch, const double val): kind {ch}, value {val}, name {}
//        //{ }
//        //Token(const char ch, const string s): kind {ch}, value {}, name {s} { }
//};

class Token_stream {
    public:
        Token_stream(istream &s = cin): ip{&s}, owns{false} { }
        Token_stream(istream *p): ip{p}, owns{true} { }

        ~Token_stream() { close(); }

        Token get();
        Token &current() { return ct; }

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

        void putback(const Token t) {
            ct = t;
        }

    private:
        void close() { if (owns) delete ip; }
        istream *ip;
        bool owns;
        Token ct {Kind::end};
};

static Token_stream ts {cin};
//void Token_stream::ignore(const char c) {
//    if (full && c == buffer.kind) {
//        full = false;
//        return;
//    }
//    full = false;
//
//    char ch {};
//    while (cin >> ch)
//        if (ch == c)
//            return;
//}

Token Token_stream::get()
{
    //if (full) { // remove token from buffer
    //    full = false;
    //    return buffer;
    //}

    char ch {};
    do {
        if (!ip->get(ch))
            return ct = {Kind::end};
        if (ch == '\n')
            return ct = {Kind::print};
    } while (isspace(ch));

    switch (ch) {
        case print: case quit: case comma:
        case help:  case Help:
        case '!': case '%': case '=':
        case '{': case '}': case '(': case ')':
        case '+': case '-': case '*': case '/':
            return ct = {static_cast<Kind>(ch)};
        case '.':
        case '0': case '1': case '2': case '3': case '4':
        case '5': case '6': case '7': case '8': case '9':
            {
                ip->putback(ch);
                *ip >> ct.value;
                ct.kind = Kind::number;
                return ct;
            }
        default:
            // does the input start with a char?
            if (isalpha(ch) || ch == '_') {
                ct.name = ch;
                while (ip->get(ch) && (isalnum(ch) || ch == '_'))
                    ct.name += ch;
                ip->putback(ch);
                return ct = {Kind::name};
            }
            error("Bad token");
            return ct = {Kind::print};
    }
}

//------------------------------------------------------------------------------
// variables in our calculator
class Variable {
    public:
        string name;
        double value;
        bool isConst;

        Variable(const string s, const double d, const bool b = false):
            name {s}, value {d}, isConst {b} { }
};

class Symbol_table{
    public:
        vector<Variable> names; // keep all variables in one vector

        Symbol_table(): names {} { }

        bool is_declared(const string&);
        double get_value(const string&);
        void set_value(const string&, const double);
        double declare(const string&, const double, const bool);
};

bool Symbol_table::is_declared(const string &s) {
    for (const auto &x : names)
        if (x.name == s)
            return true;
    return false;
}

double Symbol_table::get_value(const string &s) {
    for (auto x : names)
        if (x.name == s)
            return x.value;
    error("get: undefined name " + s);
    return 0.0;
}

void Symbol_table::set_value(const string &s, const double d) {
    for (auto &x : names)
        if (x.name == s) {
            if (x.isConst) {
                error("cannot change the value of const var");
                return;
            }
            x.value = d;
            return;
        }
    error("set: undefined name " + s);
}

double Symbol_table::declare(const string &s, const double d, const bool b) {
    if (is_declared(s))
        error(s + " is declared twice");
    names.push_back(Variable {s, d, b});
    return d;
}

// static Symbol_table st;

// declaration so that primary() can call expression()
double expression(bool);

// deal with numbers and parentheses
double primary(bool get)
{
    if (get)
        ts.get();
    switch (ts.current().kind) {
        case Kind::lp:
            {
                const double d {expression(true)};
                if (ts.current().kind != Kind::rp)
                    error("')' expected");
                    //error(static_cast<char>(Kind::rp) + " expected");
                ts.get();
                return d;
            }
        case Kind::lfp:
            {
                const double d {expression(true)};
                if (ts.current().kind != Kind::rfp)
                    error("'}' expected");
                ts.get();
                return d;
            }
        case Kind::number:
            {
                const double d {ts.current().value};
                ts.get();
                return d;
            }
        case Kind::name:
            {
                const double d {table[ts.current().name]};
                if (ts.get().kind == Kind::assign)
                    return expression(true);
                return d;
            }
        default:
            error("primary expected");
            return 0.0;
    }
}

//double func(Token_stream &ts) {
//    Token t {ts.get()};
//    switch (t.kind) {
//        case sqrt_label:
//            {
//                t = ts.get();
//                if (t.kind != '(')
//                    error("'(' expected");
//                const double d {expression(ts)};
//                t = ts.get();
//                if (t.kind != ')')
//                    error("')' expected");
//                if (d < 0)
//                    error("negative value for sqrt()");
//                return sqrt(d);
//            }
//        case power_label:
//            {
//                t = ts.get();
//                if (t.kind != '(')
//                    error("'(' expected");
//                const double d {expression(ts)};
//                t = ts.get();
//                if (t.kind != ',')
//                    error("',' expected");
//                const double p {expression(ts)};
//                t = ts.get();
//                if (t.kind != ')')
//                    error("')' expected");
//                //int i = static_cast<int>(p);
//                if (static_cast<int>(p) != p)
//                    error("only integer values are allowed for exp");
//                if (d == 0 && p < 0)
//                    error("cannot raise zero to negative power");
//                return pow(d, p);
//            }
//        default:
//            ts.putback(t);
//            return primary(ts);
//    }
//}
//
//// deal with postfix characters (factorials, basically)
double postfix(bool get) {
    // double left {primary()};
    double left {primary(get)};
    const Token t = ts.get();
    if (ts.get().kind == Kind::fact) {
        if (left < 0)
            error("Factorial is not defined for negative values");
        do {
            left = factorial(left);
        } while (ts.get().kind == Kind::fact);
    }
    //ts.putback(t);
    return left;
}

//// deal with + and - signs in front of expressions
double prefix(bool get) {
    const Token t = ts.get();
    switch (ts.current().kind) {
        case Kind::minus:
            return -postfix(get);
        case Kind::plus:
            return postfix(get);
        default:
            //ts.putback(t);
            return postfix(get);
    }
}

// deal with *, /, and %
double term(bool get) {
    //double left {primary(get)};
    double left {prefix(get)};
    while (true) {
        switch (ts.current().kind) {
            case Kind::mul:
                left *= term(true);
                break;
            case Kind::div:
                {
                    if (const double d {prefix(true)}) {
                        left /= d;
                        break;
                    }
                    return error("divide by zero");
                }
            default:
                return left;
        }
    }
}

// deal with + and -
double expression(bool get) {
    double left {term(get)};
    while (true) {
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

//double declaration(Token_stream &ts, const bool b) {
//    Token t = ts.get();
//    if (t.kind != name)
//        error("name expected in declaration");
//    string var_name {t.name};
//
//    t = ts.get();
//    if (t.kind != '=')
//        error("= missing in declaration of " + var_name);
//
//    return st.declare(var_name, expression(ts), b);
//}
//
//double assign(Token_stream &ts, const Token tk) {
//    // not very elegant solution
//    const double v = st.get_value(tk.name);
//    Token t {ts.get()};
//    switch (t.kind) {
//        case print:
//            return v;
//        case '+':
//            return v + expression(ts);
//        case '-':
//            return v - expression(ts);
//        case '*':
//            return v * expression(ts);
//        case '/':
//            return v / expression(ts);
//        case '%':
//            return fmod(v, expression(ts));
//        case '=':
//            {
//                double d {expression(ts)};
//                st.set_value(tk.name, d);
//                return d;
//            }
//        default:
//            return v;
//    }
//}
//
//double statement(Token_stream &ts) {
//    const Token t = ts.get();
//    switch (t.kind) {
//        case let:
//            return declaration(ts, false);
//        case inv:
//            return declaration(ts, true);
//        case name:
//            //return assign(t.name);
//            return assign(ts, t);
//        default:
//            ts.putback(t);
//            return expression(ts);
//    }
//}

//void clean_up_mess(Token_stream &ts) {
//    ts.ignore(print);
//}

void display_help() {
    cout << "Enter expressions using float-point numbers\n" <<
        "Operations: + - * / ! % ( )  { } =; Functions: sqrt() and pow()\n" <<
        "Variables (names comply with C++ rules)\n" << "Use " << print <<
        " to display result, " << help << " or " << Help << " for help and "
        << quit << " to quit\n";
}

//------------------------------------------------------------------------------

void calculate() {
    while (true) {
        ts.get();
        cout << prompt;
        switch (ts.current().kind) {
            case Kind::end:
                return;
            case Kind::print:
                break;
            case Kind::help:
            case Kind::Help:
                display_help();
                break;
            default:
                cout << result << expression(false) << endl;
        }
    }
}

int main() {
    cout << "Simple calculator" << endl;
    display_help();
    cout << prompt;

    //static Token_stream ts;
    table["pi"] = 3.1415926535897932385;
    table["e"] = 2.7182818284590452354;
    //st.declare("pi", 3.1415926535, true);
    //st.declare("e", 2.7182818284, true);
    //st.declare("k", 1000, true);

    try {
        calculate();
        return 0;
    } catch (exception& e) {
        cerr << "error: " << e.what() << '\n';
        // keep_window_open();
        return 1;
    } catch (...) {
        cerr << "error: unknown exception!\n";
        // keep_window_open();
        return 2;
    }
}

