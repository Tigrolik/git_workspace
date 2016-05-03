#include <iostream>
#include <vector>

using namespace std;

struct X {
    int val;
    void out(const string &s, int nv) {
        cerr << this << "->" << s << ": " << val << " (" << nv << ")\n";
    }
    X() {
        out("Default ctor: X()", 0);
        val = 0;
    }
    X(int v) {
        val = v;
        out("Ctor with int: X(int)", v);
    }
    X(const X &x) {
        val = x.val;
        out("Copy ctor: X(X&)", x.val);
    }
    X &operator=(const X &a) {
        out("Assignment operator: X::operator=()", a.val);
        val = a.val;
        return *this;
    }
    ~X() {
        out("Destructor: ~X()", 0);
    }
};

X glob(2);

X copy(X a) {
    return a;
}

X copy2(X a) {
    X aa = a;
    return aa;
}

X& ref_to(X &a) {
    return a;
}

X* make(int i) {
    X a(i);
    return new X(a);
}

struct XX {X a; X b;};

int main() {

    //X loc {4}; // local var
    //X loc2 {loc}; // copy ctor
    //loc = X {5}; // copy assignment
    //loc2 = copy(loc); // call by value and return
    //loc2 = copy2(loc);
    //X loc3 {6};
    //X &r = ref_to(loc); // call by reference and return
    //cout << &r << endl;
    //delete make(7);
    //delete make(8);
    vector<X> v(4);
    XX loc4;
    cout << loc4.a.val << ' ' << loc4.b.val << endl;
    X *p = new X {9};
    delete p;
    X *pp = new X[5];
    delete [] pp;

    return 0;
}
