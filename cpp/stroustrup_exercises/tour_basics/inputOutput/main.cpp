#include <iostream>
#include <fstream>
#include <iterator>
#include <vector>
#include <set>
#include <algorithm>

template <typename T>
void print_vec(const std::vector<T> v) {
    for (auto &i : v)
        std::cout << i << " ";
    std::cout << std::endl;
}

int main()
{
    using namespace std;

    const string fn = "test.txt";
    ofstream os {fn};

    const int n = 1000;
    vector<double> v(n);

    for (auto i = 0; i < n; ++i)
        v[i] = i / 3.0 * 2;

    copy(v.begin(), v.end(), ostream_iterator<double> {os, " "});

    os.close();

    ifstream is {fn};
    vector<double> v2 {istream_iterator<double> {is},
        istream_iterator<double>{}};
    is.close();

    print_vec(v2);

    return !os;

#if 0
    string from, to;
    cin >> from >> to; // get source and target file names

    ifstream is {from}; // input stream for "from"
    //istream_iterator<string> ii {is}; // input iterator for stream
    //istream_iterator<string> eos {}; // input sentinel

    ofstream os {to}; // output stream for "to"
    //ostream_iterator<string> oo {os, "\n"}; // output iterator for stream
    //vector<string> b {ii, eos}; // vector initialized from input [ii:eos)
    //sort(b.begin(), b.end());
    //unique_copy(b.begin(), b.end(), oo); // copy buffer to output

    // read input
    set<string> b {istream_iterator<string> {is}, istream_iterator<string>{}};
    copy(b.begin(), b.end(), ostream_iterator<string> {os, "\n"});

    return !is.eof() || !os;
#endif

#if 0
    vector<int> v1 {1, 2};
    vector<int> v2 {3, 5, 7};
    vector<int> vout(v1.size() + v2.size());
    merge(v1.begin(), v1.end(), v2.begin(), v2.end(), vout.begin());
    print_vec(vout);

    return 0;
#endif
}

