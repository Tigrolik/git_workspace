#include <iostream>
#include <algorithm>
#include <cstring>
#include <vector>

using namespace std;

using CFT = int(*)(const void*, const void*);

void ssort(void *base, size_t n, size_t sz, CFT cmp) {
    /*
     * Sort "n" elements of vector "base" into increasing order using the
     * comparison function pointed to by "cmp". The elements are of size "sz".
     * Shell sort (Knuth, Vol3, pg84)
     */
    for (int gap = n / 2; gap > 0; gap /= 2)
        for (size_t i = gap; i < n; ++i)
            for (int j = i - gap; j >= 0; j -= gap) {
                char *b = static_cast<char*>(base); // necessary cast
                char *pj = b + j;// * sz; // &base[j]
                char *pjg = b + (j + gap);// * sz; // &base[j + gap]
                if (cmp(pjg, pj) < 0)
                    //for (size_t k = 0; k < sz; ++k) {
                    for (size_t k = 0; k < n; ++k) {
                        char temp = pj[k];
                        pj[k] = pjg[k];
                        pjg[k] = temp;
                    }
            }
}

template <typename T>
void my_sort(vector<T> &v, CFT cmp) {
    sort(v.begin(), v.end(), [cmp](const T &x, const T &y) {
            return cmp(static_cast<const void*>(&x),
                static_cast<const void*>(&y)) < 0; });
}

struct User {
    const char *name;
    const char *id;
    int dept;
};

void print_id(const vector<User> &v) {
    for (const auto &x: v)
        cout << x.name << '\t' << x.id << '\t' << x.dept << endl;
}

int cmp1(const void *p, const void *q) {
    return strcmp(static_cast<const User*>(p)->name,
            static_cast<const User*>(q)->name);
}

int cmp2(const void *p, const void *q) {
    return static_cast<const User*>(p)->dept-static_cast<const User*>(q)->dept;
}

int cmp3(const User *p, const User *q) {
    return strcmp(p->id, q->id);
}

int main() {
    vector<User> heads = {{"Ritchie D.M.", "dmr", 11271},
        {"Sethi R.", "ravi", 11272}, {"Szymanski T.G.", "tgs", 11273},
        {"Schr yer N.L.", "nls", 11274}, {"Schr yer N.L.", "nls", 11275},
        {"Kernighan B.W.", "bwk", 11276} };
    //heads[0].name = "Ritchie D.M."; heads[0].id = "dmr"; heads[0].dept = 11271;
    //User u1 {"Ritchie D.M.", "dmr", 11271};
    //User u2 {"Sethi R.", "ravi", 11272};
    //cout << sizeof(u1) << endl;
    //heads.push_back(u1);
    //heads.push_back(u2);
    //User *u = &heads[0] + 1;
    //cout << u->name << ' ' << sizeof(u) << endl;
    //cout << "Heads in alphabetical order:\n";
    //sort(heads.begin(), heads.end(), [](const User &x, const User &y)
    //        { return strcmp(x.id, y.id) < 0; });
    //ssort(static_cast<void*>(&heads), 6, sizeof(User), cmp1);
    //cout << sizeof(&heads) << endl;
    //cout << (&heads[0] + 1)->name << endl;
    ssort(&heads[0], 6, 6, cmp1);
    //my_sort(heads, cmp1);
    //print_id(heads);

    return 0;
}

