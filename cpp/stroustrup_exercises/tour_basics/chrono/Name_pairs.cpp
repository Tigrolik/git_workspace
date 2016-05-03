#include "Name_pairs.h"
#include <algorithm>

Name_pairs::Name_pairs(): name{}, age{} { }

void Name_pairs::read_names() {
    cout << "Enter names (use ~ to stop):\n";
    string s;
    while ((cin >> s) && (s != "~"))
        name.push_back(s);
}

void Name_pairs::read_ages() {
    for (size_t i = 0; i < name.size(); ++i) {
        int temp;
        cout << "Enter " << name[i] << "'s age: ";
        cin >> temp;
        age.push_back(temp);
    }
}

void Name_pairs::sort() {
    vector<string> copy_names {name};
    std::sort(name.begin(), name.end());

    vector<double> sorted_ages {};
    const int n = name.size();
    for (auto i = 0; i < n; ++i) {
        string temp {name[i]};
        for (auto j = 0; j < n; ++j)
            if (copy_names[j] == temp) {
                sorted_ages.push_back(age[j]);
                break;
            }
    }
    age = sorted_ages;
}

void Name_pairs::print() {
    cout << "We have " << name.size() << " names:\n";
    for (size_t i = 0; i < name.size(); ++i)
        cout << name[i] << ", age: " << age[i] << endl;
}

ostream &operator<<(ostream &os, const Name_pairs &np) {
    os << "We have "  << np.names().size() << " names:\n";
    for (size_t i = 0; i < np.names().size(); ++i)
        os << np.names()[i] << ", age: " << np.ages()[i] << '\n';
    return os;
}

bool operator==(const Name_pairs &a, const Name_pairs &b) {
    return a.names() == b.names() && a.ages() == b.ages();
}

bool operator!=(const Name_pairs &a, const Name_pairs &b) {
    return !(a == b);
}

