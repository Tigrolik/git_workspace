#include <iostream>
#include <vector>

using namespace std;

class Name_pairs {
    public:
        Name_pairs();

        void read_names();
        void read_ages();

        vector<string> names() const { return name; }
        vector<double> ages() const { return age; }

        void sort();
        void print();

        //std::ostream &operator<<(std::ostream &os);

    private:
        vector<string> name;
        vector<double> age;
};

std::ostream &operator<<(std::ostream &os, const Name_pairs &np);
