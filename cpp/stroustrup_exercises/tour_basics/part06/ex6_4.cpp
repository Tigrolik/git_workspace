#include <iostream>
#include <vector>

using namespace std;

class Name_value {
    public:
        string name;
        int value;

        Name_value(): name {}, value {} { }
};

void search_for_score(const vector<Name_value> v) {
    cout << "Enter a name to search for: ";
    string name {};
    cin >> name;
    for (size_t i = 0; i < v.size(); ++i)
        if (name == v[i].name) {
            cout << name << "'s score: " << v[i].value << endl;
            return;
        }
    cout << "Name not found\n";
}

void search_for_names(const vector<Name_value> v) {
    cout << "Enter a score to search for: ";
    int val {};
    cin >> val;
    bool notFound {true};
    for (size_t i = 0; i < v.size(); ++i)
        if (val == v[i].value) {
            cout << "Name with given score: " << v[i].name << endl;
            notFound = false;
        }
    if (notFound)
        cout << "Name not found\n";
}

void read_names_values() {
    vector<Name_value> v;

    cout << "Enter a name and an int value (stop with NoName 0)\n";

    string name {};
    int val {};
    Name_value nv {};

    cin >> name >> val;
    while ((name != "NoName") || (val != 0)) {
        for (auto x : v)
            if (x.name == name) {
                cerr << "No duplicate names allowed\n";
                exit(1);
            }
        nv.name = name;
        nv.value = val;
        v.push_back(nv);
        cin >> name >> val;
    }

    for (size_t i = 0; i < v.size(); ++i)
        cout << "Name: " << v[i].name << "; score: " << v[i].value << endl;

    search_for_score(v);
    search_for_names(v);
}

int main() {

    read_names_values();

    return 0;
}
