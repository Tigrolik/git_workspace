#include <iostream>
#include <vector>
#include <stdexcept>

using namespace std;

inline void error(const string s) {
    throw runtime_error(s);
    // cerr << "Error: " << s << endl;
}

constexpr int area(const int length, const int width) {
    return ((length > 0) && (width > 0)) ? length * width : -1;
}

constexpr int framed_area(const int x, const int y) {
    return area(x - 2, y - 2);
}

int f(int x, int y, int z) {
    int area1 = area(x, y);
    if (area1 <= 0)
        error("non-positive area");
    int area2 = framed_area(1, z);
    int area3 = framed_area(y, z);
    double ratio = double(area1) / area3;

    cout << area1 << ' ' << area2 << ' ' << area3 << ' ' << ratio << endl;

    return 0;
}

void test_area() {
    f(0, 0, 0);
    f(1, 2, 2);
}

int catch_test() {
    try {
        vector<int> v;
        for (int x; cin >> x;)
            v.push_back(x);
        for (size_t i = 0; i <= v.size() + 1; ++i)
            cout << "v[" << i << "] == " << v[i] << endl;
    } catch (exception &e) {
        cerr << "error:" << e.what() << endl;;
        return 1;
    } catch (...) {
        cerr << "Exception: something went wrong\n";
        return 2;
    }
    return 0;
}

void scaffolding() {
    using namespace std;
    cout << "Success!\n";
    cout << "Success!\n";
    cout << "Success" << "!\n";
    cout << "Success!" << '\n';
    int res = 7; vector<int> v1(10); v1[5] = res; cout << "Success!\n";
    vector<int> v2(10); v2[5] = 7; if (v2[5] == 7) cout << "Success!\n";
    if (true) cout << "Success!\n"; else cout << "Fail!\n";
    bool c = false; if (!c) cout << "Success!\n"; else cout << "Fail!\n";
    string s = "ape"; c = "fool" < s; if (!c) cout << "Success!\n";
    s = "ape"; if (s != "fool") cout << "Success!\n";
    s = "ape"; if (s != "fool") cout << "Success!\n";
    s = "ape"; if (s != "fool") cout << "Success!\n";
    vector<char> v(5); for(size_t i=0; i<v.size(); ++i)cout << "Success!\n";
}

int main() {

    //test_area();
    //catch_test();
    scaffolding();

    return 0;
}
