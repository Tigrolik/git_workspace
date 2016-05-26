#include <fstream>
#include <iostream>
#include <vector>
#include <algorithm>
#include <stdexcept>

template <class C>
void disp_cont(const C& c) {
    for (const auto &x: c)
        std::cout << x << '\n';
    //std::cout << '\n';
}

struct Item {
    std::string name;
    int id;
    double value;
};

std::ostream& operator<<(std::ostream &os, const Item &I) {
    return os << I.name << ": " << I.id << " and " << I.value;
}

std::istream& operator>>(std::istream &is, Item &I) {
    std::string n;
    int i;
    double d;
    is >> n >> i >> d;
    if (is)
        I = Item {n, i , d};
    return is;
}

struct Cmp_by_name {
    bool operator()(const Item &I1, const Item &I2) const {
        return I1.name < I2.name;
    }
};

void erase_by_name(std::vector<Item> &vi, const std::string &s) {
    auto p = std::find_if(begin(vi), end(vi),
            [&s](const Item &I){ return I.name == s; });
    if (p != end(vi))
        vi.erase(p);
    else
        std::cout << "Item " + s + " not found\n";
}

void erase_by_id(std::vector<Item> &vi, const int i) {
    auto p = std::find_if(begin(vi), end(vi),
            [&i](const Item &I){ return I.id == i; });
    if (p != end(vi))
        vi.erase(p);
    else
        std::cout << "Item (id: " << i << ") not found\n";
}


void test_items() {
    const std::string fn {"items.txt"};
    std::ifstream ifs {fn};
    if (!ifs)
        throw std::runtime_error("cannot open file " + fn);
    ifs.exceptions(ifs.exceptions() | std::ios_base::badbit);

    std::vector<Item> vi;
    for (Item I; ifs >> I;) {
        vi.push_back(I);
    }
    disp_cont(vi);
    std::cout << "sorted by name\n";
    std::sort(begin(vi), end(vi), Cmp_by_name());
    disp_cont(vi);
    std::cout << "sorted by id\n";
    std::sort(begin(vi), end(vi),
            [](const Item &I1, const Item &I2) { return I1.id < I2.id; });
    disp_cont(vi);
    std::cout << "sorted by value descending\n";
    std::sort(begin(vi), end(vi),
            [](const Item &I1, const Item &I2) { return I1.value > I2.value; });
    disp_cont(vi);
    vi.insert(begin(vi), Item {"horse shoe", 99, 12.34});
    vi.insert(begin(vi), Item {"Canon S400", 9988, 499.95});
    erase_by_name(vi, "Item4");
    erase_by_name(vi, "Item7");
    erase_by_name(vi, "Item7");
    erase_by_id(vi, 12);
    erase_by_id(vi, 10);
    erase_by_id(vi, 90);
    disp_cont(vi);
}

int main() {

    test_items();

    return 0;
}

