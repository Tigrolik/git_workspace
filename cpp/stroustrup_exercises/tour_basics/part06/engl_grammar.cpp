#include <iostream>
#include <vector>

using namespace std;

inline bool isNoun(const string &s) {
    return ((s == "birds") || (s == "fish") || (s == "C++")) ? true : false;
}

inline bool isConj(const string &s) {
    return ((s == "and") || (s == "or") || (s == "but")) ? true : false;
}

inline bool isVerb(const string &s) {
    return ((s == "rules") || (s == "fly") || (s == "swim")) ? true : false;
}

inline bool isArtl(const string &s) {
    return (s == "the") ? true : false;
}

bool isSent(const vector<string> &vs) {
    switch (vs.size()) {
        case 0: case 1: case 2:
            return false;
        case 3:
            if (isNoun(vs[0]) && isVerb(vs[1]) && (vs[vs.size() - 1] == "."))
                return true;
            else
                return false;
        case 4:
            if (isArtl(vs[0]) && isNoun(vs[1]) && isVerb(vs[2]) &&
                    (vs[vs.size() - 1] == "."))
                return true;
            else
                return false;
        default:
            if (isArtl(vs[0]) && isNoun(vs[1]) && isVerb(vs[2]) &&
                    isConj(vs[3]) && isSent({vs.begin() + 4, vs.end()}) &&
                    (vs[vs.size() - 1] == "."))
                return true;
            else
                return false;
    }
}

vector<string> get_words(const string &s) {
    const size_t n = s.size();
    size_t idx1 {0}, idx2 {0};
    vector<string> vs {};
    while (idx2 < n) {
        while ((idx2 < n) && (s[idx2] != ' '))
            ++idx2;
        vs.push_back(s.substr(idx1, idx2 - idx1));
        while ((idx2 < n) && (s[idx2] == ' '))
            ++idx2;
        idx1 = idx2;
    }
    return vs;
}

int main() {

    string sent {};
    getline(cin, sent);

    vector<string> words {get_words(sent)};

    if (isSent(words))
        cout << "OK\n";
    else
        cout << "Not OK\n";

    return 0;
}
