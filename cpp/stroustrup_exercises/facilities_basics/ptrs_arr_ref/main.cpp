#include <iostream>

void f1() {
    using namespace std;

    const char c {'c'};
    // pointer to a character
    const char *pc = &c;
    // array of 10 integers
    const int arr[10] {1, 3, 7, 5, 9, 11, 17, 15, 13, 19};
    // reference to the array
    auto &ref_arr = arr;
    // pointer to an array of character strings
    const char *str_arr[] = {"hey", "sup", "dog"};
    // pointer to pointer to a character
    const char** ppc = &pc;
    // constant integer
    const int y {7};
    // pointer to a constant int
    const int *pci = &y;
    int x {5};
    // constant pointer to an int
    int *const cpi = &x;

    cout << "Pointer to char: " << &pc << endl;
    cout << "Pointer to a pointer to char: " << ppc << endl;
    cout << "Array of 10 elements:" << endl;
    for (auto i : arr)
        cout << i << ' ';
    cout << "\b\n";
    cout << "Pointer to array of char strings: " << str_arr << endl;
    cout << "Ref to array of 10 ints: " << ref_arr << endl;
    cout << "Pointer to const int: " << pci << endl;
    cout << "Const pointer to int: " << cpi << endl;

    cout << "int* alignment: " << alignof(int*) << endl;
    cout << "char* alignment: " << alignof(char*) << endl;
    cout << "void* alignment: " << alignof(void*) << endl;
}

//void f2() {
//    using unsch = unsigned char;
//    using cunsch = const unsigned char;
//    using ptoi = int*;
//    using pptoch = char**;
//    using ptoarrch = char(*)[];
//    using arr7ptoi = int*[7];
//    using ptoarr7ptoi = arr7ptoi*;
//    using arr8arr7ptoi = ptoarr7ptoi[][8];
//}

void f3() {
    using namespace std;
    //    const char ch_arr[] = "Hello, there";
    //    const char *pc1 = &ch_arr[0];
    //    const char *pc2 = &ch_arr[3];
    //    const char *pca[] = {"Hello"};
    //    const char *ca = "hello";
    //    const char(*kings)[] = "hello";
    char s[] = "Joe";
    char *s1 = s;
    char *s2 = s;
    ++s2;
    cout << "s1 = " << s1 << ", s2 = " << s2 << ", diff = " << s2 - s1 << endl;
    const char s3[] = "a short string";
    cout << "s = " << s3 << ", size of s = " << sizeof(s3) << endl;
}

void f4(char c) {
    using namespace std;
    cout << c << endl;
}

void g(char& c) {
    using namespace std;
    cout << c << endl;
}

void h(const char& c) {
    using namespace std;
    cout << c << endl;
}

void f5(const char *ms[]) {
    using namespace std;
    for (int i = 0; ms[i] != 0; ++i)
        cout << ms[i] << ' ';
    cout << "\b\n";
}

int main()
{
    //f4('a'); h('a');
    ////g('a'); g(49); g(3300); // illegal, not a variable
    //f4(49); h(49);
    ////f4(3300); h(3300); // overflow in implicit conversion
    //char c = 'x';
    //f4(c); h(c); g(c);
    //unsigned char uc = 'y';
    //f4(uc); h(uc);
    //// g(uc); g(sc); // ref to char is different from unsigned char
    //signed char sc = 'z';
    //f4(sc); h(sc);

    using namespace std;

    const char *months[] = {"Jan", "Feb", "Mar", "Apr", '\0'};
    f5(months);

    const char *v[] = {"May", "Jun", "Jul", '\0'};
    f5(v);

    const char *mv[] = {"Aug", "Sep", "Oct", "Nov", "Dec", '\0'};
    f5(mv);

    return 0;
}
