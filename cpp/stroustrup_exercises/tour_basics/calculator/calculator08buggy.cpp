/*
	calculator08buggy.cpp

	Helpful comments removed.

	We have inserted 3 bugs that the compiler will catch and 3 that it won't.
*/

#include <iostream>
#include <vector>
#include <stdexcept>
#include <algorithm>
// #include "std_lib_facilities.h"

using namespace std;

void error(const string &s)
{
    throw runtime_error(s);
}

class Token {
    public:
        char kind;    // kind of token
        double value; // value of the token
        string name;  // name of the variable?

        // initialize token with a char symbol
        Token(char ch): kind{ch}, value{0}, name {} { }
        Token(char ch, double val): kind{ch}, value{val}, name {} { }
        Token(char ch, string s): kind{ch}, value {}, name{s} { }
};

class Token_stream {
	bool full;
	Token buffer;

public:

	Token_stream(): full{false}, buffer{0} { }
	Token get();
	void unget(Token t) { // kind of putback
        // puts args back into the Token_stream buffer
        if (full)
            error("unget(): buffer is full");
        buffer = t;  // copy to buffer
        full = true; // set the flag that the buffer is full
    }

	void ignore(char);
};

// various labels for types of tokens
const char let = 'L';
const char quit = 'q';
const char print = ';';
const char number = '8';
const char name = 'a';
const char decl_ch = '#';
const char sqrt_kind = 's';
const char power_kind = 'p';
const string declkey {"let"};
const string sqrtkey {"sqrt"};
const string powerkey {"pow"};

Token Token_stream::get() {
    if (full) {
        // remove the token from the buffer if we already have the Token ready
        full = false;
        return buffer;
    }

    char ch;
    cin >> ch;

    switch (ch) {
        // handle operators and actions
        case '(': case ')':
        case '+': case '-':
        case '*': case '/':
        case '%': case '=':
        case print: case quit:
        case ',': // comma as a delimiter of arguments
            return Token(ch);

        case '.':
        case '0': case '1': case '2': case '3': case '4':
        case '5': case '6': case '7': case '8': case '9':
            {
                cin.putback(ch);
                double val;
                cin >> val;
                return Token(number, val);
            }

        case decl_ch:
            return Token {let};
        default:
            // does the input start with a char?
            if (isalpha(ch)) {
                string s;
                s += ch;
                // accumulate the string of chars and digits
                while (cin.get(ch) &&
                        (isalpha(ch) || isdigit(ch) || ch == '_'))
                    s += ch;
                cin.putback(ch);
                if (s == declkey)
                    return Token {let};
                if (s == sqrtkey)
                    return Token {sqrt_kind};
                if (s == powerkey)
                    return Token {power_kind};
                return Token {name, s};
            }
            error("Bad token");
            return 0;
    }
}

void Token_stream::ignore(char c)
{
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

struct Variable {
	string name;
	double value;

	Variable(string n, double v): name{n}, value{v} { }
};

vector<Variable> names;

double get_value(string s)
{
	for (size_t i = 0; i < names.size(); ++i)
		if (names[i].name == s)
            return names[i].value;
	error("get: undefined name " + s);
    return 0;
}

void set_value(string s, double d)
{
    // set the var named s to value d
	for (size_t i = 0; i < names.size(); ++i)
		if (names[i].name == s) {
			names[i].value = d;
			return;
		}
	error("set: undefined name " + s);
}

bool is_declared(string s)
{
	for (size_t i = 0; i < names.size(); ++i)
		if (names[i].name == s)
            return true;
	return false;
}

double define_name(string var, double val) {
    if (is_declared(var))
        error(var + " is declared twice");
    names.push_back(Variable(var, val));
    return val;
}

Token_stream ts;

double expression();

double primary()
{
	Token t = ts.get();
	switch (t.kind) {
	case '(':
	{	double d = expression();
		t = ts.get();
		if (t.kind != ')')
            error("'(' expected");
        return d;
	}
	case '-':
		return -primary();
	case number:
		return t.value;
	case name:
		return get_value(t.name);
	default:
		error("primary expected");
        return 0;
	}
}

double term()
{
	double left = primary();
	while(true) {
		Token t = ts.get();
		switch(t.kind) {
		case '*':
			left *= primary();
			break;
		case '/':
		{	double d = primary();
			if (d == 0) error("divide by zero");
			left /= d;
			break;
		}
		default:
			ts.unget(t);
			return left;
		}
	}
}

double expression()
{
	double left = term();
	while(true) {
		Token t = ts.get();
		switch(t.kind) {
		case '+':
			left += term();
			break;
		case '-':
			left -= term();
			break;
		default:
			ts.unget(t);
			return left;
		}
	}
}

double declaration()
{
	Token t = ts.get();
	if (t.kind != name)
        error ("name expected in declaration");
	string var_name {t.name};

	Token t2 = ts.get();
	if (t2.kind != '=')
        error("= missing in declaration of " + var_name);

	double d = expression();
    define_name(var_name, d);

	return d;
}

double assign(string var_name) {
	const Token t {ts.get()};
	if (t.kind != '=')
        error("= missing in the assignment of " + var_name);

	double d {expression()};
    set_value(var_name, d);

	return d;
}

double statement();

double func(const char func_kind)
{
	Token t {ts.get()};
	if (t.kind != '(')
        error("function expects a '(' as opening");

    switch (func_kind) {
        case sqrt_kind:
            {
                ts.unget(t);
                double d {expression()};
                if (d < 0)
                    error("negative value for sqrt()");
                return sqrt(d);
            }
        case power_kind:
            {
                double d1 {expression()};
                t = ts.get();
                if (t.kind != ',')
                    error("',' expected");
                double d2 {expression()};
                return pow(d1, d2);
            }
        default:
            return func(func_kind);
    }
}

double statement()
{
    Token t = ts.get();
    switch(t.kind) {
        case sqrt_kind:
            return func(sqrt_kind);
        case power_kind:
            return func(power_kind);
        case let:
            return declaration();
        case name:
            return assign(t.name);
        default:
            ts.unget(t);
            return expression();
    }
}

void clean_up_mess()
{
	ts.ignore(print);
}

const string prompt = "> ";
const string result = "= ";

void calculate()
{
    while(cin) {
        try {
            cout << prompt;
            Token t = ts.get();
            while (t.kind == print)
                t = ts.get();
            if (t.kind == quit)
                return;
            ts.unget(t);
            cout << result << statement() << endl;
        } catch(exception &e) {
            cerr << e.what() << endl;
            clean_up_mess();
        }
    }
}

int main() {
    define_name("pi", 3.1415926535);
    define_name("e", 2.7182818284);
    define_name("k", 1000);

    try {
        calculate();
        return 0;
    } catch (exception& e) {
        cerr << "exception: " << e.what() << endl;
        // char c;
        // while (cin >>c&& c!=';') ;
        return 1;
    } catch (...) {
        cerr << "exception\n";
        // char c;
        // while (cin>>c && c!=';');
        return 2;
    }
}
