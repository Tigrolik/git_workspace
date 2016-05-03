#include <iostream>
#include <vector>
#include <chrono>

using namespace std;

void test_bad_alloc() {
    vector<char*> v;
    auto t0 = chrono::high_resolution_clock::now();
    int n {numeric_limits<int>::max()};
    unsigned long long int i {0};
    cout << n << endl;
    try {
        while (true) {
            char *p = new char[n];
            i += n;
            for (int j {0}; j < n; ++j)
                p[j] = 'x';
            v.push_back(p);
        }
    } catch (bad_alloc) {
        cerr << "Memory exhausted!\n";
    }
    cout << "vector size: " << v.size() << endl;
    cout << "i: " << i << ", size of char*: " << sizeof(char*) <<
        ", num bytes: " << i / sizeof(char*) << endl;
    cout << "Time elapsed: " <<
        chrono::duration_cast<chrono::milliseconds>(
                chrono::high_resolution_clock::now() - t0).count() << "msec\n";
}

int main() {

    test_bad_alloc();

    return 0;
}
