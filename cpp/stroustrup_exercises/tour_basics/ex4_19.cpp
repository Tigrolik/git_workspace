#include <iostream>
#include <vector>

using namespace std;

void search_for_score(const vector<string> v, const vector<int> s) {
    cout << "Enter a name to search for: ";
    string name {};
    cin >> name;
    for (size_t i = 0; i < v.size(); ++i)
        if (name == v[i]) {
            cout << name << "'s score: " << s[i] << endl;
            return;
        }
    cout << "Name not found\n";
}

void search_for_names(const vector<int> s, const vector<string> v) {
    cout << "Enter a score to search for: ";
    int val {};
    cin >> val;
    bool notFound {true};
    for (size_t i = 0; i < s.size(); ++i)
        if (val == s[i]) {
            cout << "Name with given score: " << v[i] << endl;
            notFound = false;
        }
    if (notFound)
        cout << "Name not found\n";
}

void read_names_values() {
    vector<string> names {};
    vector<int> scores {};

    cout << "Enter a name and an int value (stop with NoName 0)\n";

    string name {};
    int val {};
    cin >> name >> val;
    while ((name != "NoName") || (val != 0)) {
        for (auto x : names)
            if (x == name) {
                cerr << "No duplicate names allowed\n";
                exit(1);
            }
        names.push_back(name);
        scores.push_back(val);
        cin >> name >> val;
    }

    for (size_t i = 0; i < names.size(); ++i)
        cout << "Name: " << names[i] << "; score: " << scores[i] << endl;

    // search_for_score(names, scores);
    search_for_names(scores, names);
}

int main() {

    read_names_values();

    return 0;
}
