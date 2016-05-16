#include <iostream>
#include <vector>
#include <list>
#include <numeric>
#include <algorithm>
#include <iterator>

using veci = std::vector<int>;
using vecd = std::vector<double>;
using listd = std::list<double>;

struct Record {
    double unit_price;
    int units;
};

constexpr double price(const double v, const Record &r) {
    return v + r.unit_price * r.units;
}

struct Price {
    double operator()(const double v, const Record &r) {
        return v + r.unit_price * r.units;
    }
};

class Larger_than {
public:
    Larger_than(int vv): v{vv} { }
    bool operator()(const int x) { return x > v; }
private:
    int v;
};

struct Cmp_by_sqr {
    bool operator()(const int v1, const int v2) const {
        return v1 * v1 < v2 * v2;
    }
};

constexpr bool odd(const int x) {
    return x & 1;
}

template <class C>
void disp_cont(const C& c) {
    for (const auto &x: c)
        std::cout << x << ' ';
    std::cout << '\n';
}

void test_find_if() {
    std::vector<int> v {5, 2, -4, 7, -9, 12};
    // using bool function
    //auto p = std::find_if(std::begin(v), std::end(v), odd);
    // using lambda
    auto p = std::find_if(std::begin(v), std::end(v),
            [] (const int x) { return x & 1; });
    if (p != std::end(v))
        std::cout << *p << '\n';
    const int val {11};
    p = std::find_if(std::begin(v), std::end(v),
            [&val] (const int x) { return x > val; });
    if (p != std::end(v))
        std::cout << *p << '\n';
    // using function object
    p = std::find_if(std::begin(v), std::end(v), Larger_than(8));
    if (p != std::end(v))
        std::cout << *p << '\n';
    disp_cont(v);
    std::cout << "sorted by square values:\n";
    sort(v.begin(), v.end(), Cmp_by_sqr());
    disp_cont(v);
}

void test_accum() {
    std::array<double, 4> vd {1.5, -2.5, 4.0, 3.5};
    disp_cont(vd);
    std::cout << "product: " << std::accumulate(begin(vd), end(vd), 1.0,
            std::multiplies<double>()) << '\n';
    std::array<int, 4> vi {1, -2, 4, 3};
    disp_cont(vi);
    std::cout << "product: " << std::accumulate(begin(vi), end(vi), 1.0,
            std::multiplies<double>()) << '\n';
    std::vector<Record> vr;
    vr.push_back(Record {1.5, 2});
    vr.push_back(Record {2.5, 8});
    vr.push_back(Record {0.5, 11});
    // function
    std::cout << std::accumulate(begin(vr), end(vr), 0.0, price) << '\n';
    // function object
    std::cout << std::accumulate(begin(vr), end(vr), 0.0, Price()) << '\n';
}

void test_inner() {
    //vecd d_price {81.86, 34.69, 54.45};
    veci d_price {81, 34, 54};
    listd d_weights {5.8549, 2.4808, 3.8940};
    // inner product may take different containers of different types
    const double d_idx {std::inner_product(begin(d_price), end(d_price),
            begin(d_weights), 0.0)};
    std::cout << d_idx << '\n';
}

void test_partial_sum() {
    std::array<int, 8> a; a.fill(2);
    disp_cont(a);
    std::partial_sum(begin(a), end(a),
            std::ostream_iterator<int>{std::cout, " "});
    std::cout << '\n';
    std::partial_sum(begin(a), end(a), begin(a), std::multiplies<int>());
    disp_cont(a);
}

int main() {

    //test_find_if();
    //test_accum();
    //test_inner();
    test_partial_sum();

    return 0;
}

