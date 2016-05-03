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
#include <stdexcept>
#include <algorithm>

using namespace std;

// constants
static constexpr char let         {'L'};
static constexpr char inv         {'I'};
static constexpr char quit        {'q'};
static constexpr char help        {'h'};
static constexpr char Help        {'H'};
static constexpr char print       {';'};
static constexpr char func_delim  {','};
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

inline void error(const string &s)
{
    throw runtime_error(s);
}

constexpr unsigned int factorial(const unsigned int n) {
    return ((n == 0) || (n == 1)) ? 1 : n * factorial(n - 1);
}

class Token {
    public:
        char kind;     // kind of token
        double value;  // for numbers: a value
        string name;   // name for a variable

        Token(const char ch): kind {ch}, value {0}, name {} { }
        Token(const char ch, const double val): kind {ch}, value {val}, name {}
        { }
        Token(const char ch, const string s): kind {ch}, value {}, name {s} { }
};

class Token_stream {
    public:
        Token_stream(); // make a Token_stream that reads from cin
        Token get();    // get a Token (get() is defined elsewhere)
        void putback(const Token); // put a Token back
        void ignore(const char);   // flush the buffer until the char is met
    private:
        bool full;    // is there a Token in the buffer?
        Token buffer; // keep a Token put back using putback()
};


// The constructor just sets full to indicate that the buffer is empty:
Token_stream::Token_stream(): full {false}, buffer {0} { }

void Token_stream::putback(const Token t)
{
    if (full)
        error("putback() into a full buffer");
    buffer = t;  // copy t to buffer
    full = true; // buffer is now full
}

void Token_stream::ignore(const char c) {
    if (full && c == buffer.kind) {
        full = false;
        return;
    }
    full = false;

    char ch {};
    while (cin >> ch)
        if (ch == c)
            return;
}

Token Token_stream::get()
{
    if (full) { // remove token from buffer
        full = false;
        return buffer;
    }

    char ch {};
    cin.get(ch);
    while (isspace(ch)) {
        if (ch == '\n')
            return Token {print};
        cin.get(ch);
    }

    switch (ch) {
        case print: case quit: case func_delim:
        case help:  case Help:
        case '!': case '%': case '=':
        case '{': case '}': case '(': case ')':
        case '+': case '-': case '*': case '/':
            return Token {ch};
        case '.':
        case '0': case '1': case '2': case '3': case '4':
        case '5': case '6': case '7': case '8': case '9':
            {
                cin.putback(ch);
                double val;
                cin >> val;
                return Token {number, val};
            }
        case decl_label:
            return Token {let};
        default:
            // does the input start with a char?
            if (isalpha(ch) || ch == '_') {
                string s;
                s += ch;
                // accumulate the string of chars and digits (plus _)
                while (cin.get(ch) && (isalpha(ch) || isdigit(ch) || ch == '_'))
                    s += ch;
                cin.putback(ch);
                if (s == decl_key)
                    return Token {let};
                if (s == sqrt_key)
                    return Token {sqrt_label};
                if (s == power_key)
                    return Token {power_label};
                if (s == inv_key)
                    return Token {inv};
                return Token {name, s};
            }
            error("Bad token");
    }
    return 0;
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

// static vector<Variable> names; // keep all variables in one vector

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

static Symbol_table st;
static Token_stream ts;

double expression(); // declaration so that primary() can call expression()

// deal with numbers and parentheses
double primary()
{
    Token t {ts.get()};
    switch (t.kind) {
        case '{':
            {
                const double d {expression()};
                t = ts.get();
                if (t.kind != '}')
                    error("'}' expected");
                return d;
            }
        case '(':
            {
                const double d = expression();
                t = ts.get();
                if (t.kind != ')')
                    error("')' expected");
                return d;
            }
        case number:
            return t.value;
        case name:
            return st.get_value(t.name);
        default:
            error("primary expected");
            return 0.0;
    }
}

double func() {
    Token t {ts.get()};
    switch (t.kind) {
        case sqrt_label:
            {
                t = ts.get();
                if (t.kind != '(')
                    error("'(' expected");
                const double d {expression()};
                t = ts.get();
                if (t.kind != ')')
                    error("')' expected");
                if (d < 0)
                    error("negative value for sqrt()");
                return sqrt(d);
            }
        case power_label:
            {
                t = ts.get();
                if (t.kind != '(')
                    error("'(' expected");
                const double d {expression()};
                t = ts.get();
                if (t.kind != ',')
                    error("',' expected");
                const double p {expression()};
                t = ts.get();
                if (t.kind != ')')
                    error("')' expected");
                //int i = static_cast<int>(p);
                if (static_cast<int>(p) != p)
                    error("only integer values are allowed for exp");
                if (d == 0 && p < 0)
                    error("cannot raise zero to negative power");
                return pow(d, p);
            }
        default:
            ts.putback(t);
            return primary();
    }
}

// deal with postfix characters (factorials, basically)
double postfix() {
    // double left {primary()};
    double left {func()};
    Token t {ts.get()};
    if (t.kind == '!') {
        if (left < 0)
            error("Factorial is not defined for negative values");
        do {
            left = factorial(left);
            t = ts.get();
        } while (t.kind == '!');
    }
    ts.putback(t);
    return left;
}

// deal with + and - signs in front of expressions
double prefix() {
    const Token t {ts.get()};
    switch (t.kind) {
        case '-':
            return -postfix();
        case '+':
            return postfix();
        default:
            ts.putback(t);
            return postfix();
    }
}

// deal with *, /, and %
double term()
{
    double left {prefix()};
    while (true) {
        const Token t {ts.get()};
        switch (t.kind) {
            case '*':
                left *= prefix();
                break;
            case '/':
                {
                    const double d {prefix()};
                    if (d == 0)
                        error("divide by zero");
                    left /= d;
                    break;
                }
            case '%':
                {
                    const double d {prefix()};
                    if (d == 0)
                        error("divide by zero");
                    left = fmod(left, d); // modulo for floats
                    break;
                }
            default:
                ts.putback(t);
                return left;
        }
    }
}

// deal with + and -
double expression()
{
    double left {term()}; // read and evaluate a Term
    while (true) {
        const Token t {ts.get()};
        switch (t.kind) {
            case '+':
                left += term();
                break;
            case '-':
                left -= term();
                break;
            default:
                ts.putback(t);
                return left;
        }
    }
}

double declaration(const bool b) {
    Token t = ts.get();
    if (t.kind != name)
        error("name expected in declaration");
    string var_name {t.name};

    t = ts.get();
    if (t.kind != '=')
        error("= missing in declaration of " + var_name);

    return st.declare(var_name, expression(), b);
}

double assign(const Token tk) {
    // not very elegant solution
    const double v = st.get_value(tk.name);
    Token t {ts.get()};
    switch (t.kind) {
        case print:
            return v;
        case '+':
            return v + expression();
        case '-':
            return v - expression();
        case '*':
            return v * expression();
        case '/':
            return v / expression();
        case '%':
            return fmod(v, expression());
        case '=':
            {
                double d {expression()};
                st.set_value(tk.name, d);
                return d;
            }
        default:
            return v;
    }
}

double statement() {
    const Token t = ts.get();
    switch (t.kind) {
        case let:
            return declaration(false);
        case inv:
            return declaration(true);
        case name:
            //return assign(t.name);
            return assign(t);
        default:
            ts.putback(t);
            return expression();
    }
}

void clean_up_mess() {
    ts.ignore(print);
}

void display_help() {
    cout << "Enter expressions using float-point numbers\n" <<
        "Operations: + - * / ! % ( )  { } =; Functions: sqrt() and pow()\n" <<
        "Variables (names comply with C++ rules)\n" << "Use " << print <<
        " to display result, " << help << " or " << Help << " for help and "
        << quit << " to quit\n";
}

//------------------------------------------------------------------------------

void calculate() {
    while (cin) {
        try {
            cout << prompt;
            Token t {ts.get()};
            while (t.kind == print)
                t = ts.get(); // discard all "prints"
            if (t.kind == quit)
                return;
            if (t.kind == help || t.kind == Help) {
                display_help();
                continue;
            }
            ts.putback(t);
            cout << result << statement() << endl;
        } catch (exception &e) {
            cerr << e.what() << endl;
            clean_up_mess();
        }
    }
}

int main() {
    cout << "Simple calculator" << endl;
    display_help();

    st.declare("pi", 3.1415926535, true);
    st.declare("e", 2.7182818284, true);
    st.declare("k", 1000, true);

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

