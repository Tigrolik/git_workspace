#include "Punct_stream.h"
#include <algorithm>

void test_punct_stream() {
    Punct_stream ps (cin);
    ps.whitespace(";:,.?!()\"{}<>/&$@#%^*|~");
    ps.case_sensitive(false);
    cout << "Please, enter words:\n";
    vector<string> vs;
    for (string word; ps >> word;)
        vs.push_back(word);
    sort(vs.begin(), vs.end());
    cout << vs[0] << endl;
    for (size_t i = 1; i < vs.size(); ++i)
        if (vs[i] != vs[i-1])
            cout << vs[i] << endl;
}

int main() {

    test_punct_stream();

    return 0;
}
