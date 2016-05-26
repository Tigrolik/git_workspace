#include <iostream>
#include <fstream>
#include <vector>
#include <map>
#include <set>
#include <unordered_map>
#include <numeric>
#include <algorithm>
#include <iterator>
#include <stdexcept>

constexpr double w_value(const std::pair<std::string, double> &a,
        const std::pair<std::string, double> &b) {
    return a.second * b.second;
}

//template <class C, class V>
//Iterator<C> find(const C &c, const V &val) {
//    return std::find(std::begin(c), std::end(c), val);
//}

void test_map() {
    const std::string fn {"sample_text.txt"};
    std::ifstream ifs {fn};
    if (!ifs)
        throw std::runtime_error("cannot open file " + fn);
    ifs.exceptions(ifs.exceptions() | std::ios_base::badbit);
    std::map<std::string, int> words;
    for (std::string s; ifs >> s;)
        ++words[s];
    for (const auto &x: words)
        if (x.second > 1)
            std::cout << x.first << ": " << x.second << "; ";
    std::cout << '\n';

    std::map<std::string, double> d_price {{"MMM", 81.86}, {"AA", 34.69},
        {"MO", 54.45}};
    std::map<std::string, double> d_weight {{"MMM", 5.8549}, {"AA", 2.4808},
        {"MO", 3.894}};
    std::map<std::string, std::string> d_name {{"MMM", "3M Co."},
        {"AA", "Alcoa Inc."}, {"MO", "Altria Group Inc."}};
    const double d_idx {std::inner_product(d_price.begin(), d_price.end(),
            d_weight.begin(), 0.0, std::plus<double>(), w_value)};
    std::cout << d_idx << '\n';
}

void test_unordered_map() {
    std::unordered_map<std::string, int> um {{"RED", 0xFF0000},
        {"GREEN", 0x00FF00}, {"BLUE", 0x0000FF}};
    um["BLACK"] = 0x000000; um["WHITE"] = 0xFFFFFF;
    for (const auto &x: um)
        std::cout << x.first << ": " << std::showbase << std::hex <<
            x.second << ' ';
    std::cout << std::dec << '\n';
}

void test_streams() {
    const std::string fin {"sample_text.txt"}, fout {"another_text.txt"};
    std::ifstream ifs {fin};
    if (!ifs)
        throw std::runtime_error("cannot open file " + fin);
    ifs.exceptions(ifs.exceptions() | std::ios_base::badbit);
    std::ofstream ofs {fout};
    ofs.exceptions(ofs.exceptions() | std::ios_base::badbit);

    /*
     * set option
     */
    std::set<std::string> b {std::istream_iterator<std::string> {ifs},
        std::istream_iterator<std::string>{}};
    std::copy(begin(b), end(b), std::ostream_iterator<std::string>{ofs, "\n"});
    /*
     * vector option
     */
    //std::istream_iterator<std::string> ii {ifs};
    //const std::istream_iterator<std::string> eos; // input sentinel
    //std::ostream_iterator<std::string> oi {ofs, "\n"};

    //std::vector<std::string> vs {ii, eos}; // vector inited from input
    //std::sort(begin(vs), end(vs));
    //std::unique_copy(begin(vs), end(vs), oi);
}

int main() {

    //test_map();
    //test_unordered_map();
    test_streams();

    return 0;
}

