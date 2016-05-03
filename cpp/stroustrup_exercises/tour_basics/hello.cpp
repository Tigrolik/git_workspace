#include <iostream>
#include <vector>
#include <algorithm>

using namespace std;

// constexpr = to be evaluated at compile time.
constexpr double square(const double);

void print_square(double x) {
    cout << "The square of " << x << " is " << square(x) << endl;
}

bool accept() {
    int tries = 0;

    while (tries < 3) {
        cout << "Would you like to proceed (y or n)?\n";

        char ans = 0;
        cin >> ans;

        switch (ans) {
            case 'y':
                return true;
            case 'n':
                return false;
            default:
                cout << "I don't understand that, try again\n";
                ++tries;
        }
    }
    cout << "I'll take that for a no\n";
    return false;
}

void g(const int i) {
    cout << "The value of i is: " << i << endl;
}

void hello_line() {
    cout << "Please, enter your name\n";
    string str;
    getline(cin, str);
    cout << "Please, enter your age\n";
    int age;
    cin >> age;
    //getline(cin, str);
    cout << "Hello, " << str << "! You are " << age << "years old.\n";
}

class Entry {
    private:
        string name;
        int age;
    public:

        Entry(string s = "", int i = 0): name{s}, age{i} {}

        Entry &operator=(const Entry &e) {
            name = e.name;
            age = e.age;
            return *this;
        }

        friend ostream &operator<<(ostream &os, const Entry &e) {
            return os << "Name: " << e.name << ", age: " << e.age << endl;
        }

        friend istream &operator>>(istream &is, Entry &e) {
            char c, c2;
            if (is >> c && c == '{' && is >> c2 && c2 == '"') {
                string name2 = "";
                while (is.get(c) && c != '"')
                    name2 += c;
                if (is >> c && c == ','){
                    int age2 = 0;
                    if (is >> age2 >> c && c == '}'){
                        e = {name2, age2};
                        return is;
                    }
                }
            }
            //is.setf(ios_base::failbit);
            return is;
        }
};

void print_book(const vector<Entry> &book) {
    for (const auto &x : book)
        cout << x << endl;
}

template <typename T>
void print_vec(const vector<T> v) {
    for (auto i : v)
        cout << i << " ";
    cout << endl;
}

//ostream_iterator<string> oo {
//    cout
//};

int main()
{
    //cout << "Hello, World!\n";
    // auto = automatically define the type
    //const auto x = -87.2704;
    //print_square(x);
    //constexpr auto x2 = square(x);
    //cout << x2 << endl;
    //cout << accept() << endl;
    //int v[] = {0, 1, 2, 3, 4, 5, 6};
    //for (auto &i : v)
    //    cout << i << '\n';
    //for (auto i : {10, 21, 32, 68})
    //    cout << i << endl;
    //enum class Color { red, blue, green};
    //Color col = Color::red;
    //cout << &col << endl;
    //g(5.5);
    //hello_line();
    // Entry e;
    // cin >> e;
    // cout << e;
    //vector<Entry> phone_book = {
    //    {"David Hume",123456},
    //    {"Karl Popper",234567},
    //    {"Bertrand Ar thur William Russell",345678}
    //};
    //print_book(phone_book);
    //vector<int> v{5, 9, -1, 200, 0};
    //print_vec(v);
    //sort(v.begin(), v.end());
    //print_vec(v);

    //vector<string> vs {"Kant", "Plato", "Aristotle", "Klerkegard", "Hume"};
    //print_vec(vs);
    //sort(vs.begin(), vs.end());
    //print_vec(vs);
    //*oo = "Hello, ";
    //++oo;
    //*oo = "World!\n";

    cout << exp(1) << endl;

    return 0;
}

constexpr double square(const double x) {
    return x * x;
}

