#include <iostream>
#include <vector>
#include <algorithm>

using namespace std;

static int ga[10] {1, 2, 4, 8, 16, 32, 64, 128, 256, 512};
static vector<int> gv {1, 2, 4, 8, 16, 32, 64, 128, 256, 512};

void f(int a[], const int n) {
    int la[10];
    copy(ga, ga + 10, la);
    for (int i {0}; i < 10; ++i)
        cout << la[i] << ' ';
    cout << endl;
    int *p = new int[n];
    copy(a, a + n, p);
    for (int i {0}; i < 10; ++i)
        cout << p[i] << ' ';
    cout << endl;
    delete [] p;
}

void g(vector<int> v) {
    vector<int> lv(v.size());
    for (size_t i {0}; i < v.size(); ++i)
        lv[i] = v[i];
    for (size_t i {0}; i < lv.size(); ++i)
        cout << lv[i] << ' ';
    cout << endl;
    vector<int> lv2 {v};
    for (size_t i {0}; i < lv2.size(); ++i)
        cout << lv2[i] << ' ';
    cout << endl;
}

void test_array() {
    f(ga, 10);
    int aa[10];
    aa[0] = 1;
    for (int i {1}; i < 10; ++i)
        aa[i] = aa[i - 1] * i;
    f(aa, 10);
}

void test_vector() {
    g(gv);
    vector<int> vv(10);
    vv[0] = 1;
    for (int i {1}; i < 10; ++i)
        vv[i] = vv[i - 1] * i;
    g(vv);
}

int main() {

    //test_array();
    test_vector();

    return 0;
}
