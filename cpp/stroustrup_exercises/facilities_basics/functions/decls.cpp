#include <iostream>

using namespace std;

// function with arguments of type pointer to a charcter and reference to
// integer and returning no value
void f0(char*, int&);

// pointer to function of type described above
using Pf0 = void(*)(char*, int&);

// function taking above pointer as an argument
void f1(Pf0);

// function returning such a pointer
Pf0 f2();

// definition of a function taking such a pointer as an argument and returning
// the same pointer as a return value
Pf0 f3(Pf0 pf) {
    return pf;
}

int main() {

    cout << "File: " << __FILE__ << ", line: " << __LINE__ << endl;

    return 0;
}
