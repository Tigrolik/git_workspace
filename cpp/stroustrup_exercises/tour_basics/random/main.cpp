#include <iostream>
#include <limits>
#include <vector>
#include <random>
#include <functional>
//#include <algorithm>


int main()
{
    using namespace std;

    using my_engine = default_random_engine;
    using my_dist = uniform_int_distribution<>;

    my_engine re {};

    const int n = 5;
    my_dist one_to_six {0, n - 1};
    auto die = bind(one_to_six, re);
    int x = die();
    cout << x << endl;

    cout << "Uniform distribution:\n";
    vector<int> hist(n);
    for (auto i = 0; i < 200; ++i)
        ++hist[die()];

    for (unsigned int i = 0; i != hist.size(); ++i) {
        cout << i << '\t';
        for (int j = 0; j != hist[i]; ++j)
            cout << '*';
        cout << endl;
    }

    cout << "Normal distribution:\n";
    normal_distribution<double> n_dist(30.0, 20.0);

    const int m = 30;
    default_random_engine gen;
    vector<double> dhist(m);
    for (int i = 0; i < m; ++i) {
        double num = n_dist(gen);
        if ((num >= 0) && (num < m))
            ++dhist[num];
    }

    for (unsigned int i = 0; i != dhist.size(); ++i) {
        cout << i << '\t';
        for (int j = 0; j != dhist[i]; ++j)
            cout << '*';
        cout << endl;
    }

    static_assert((numeric_limits<char>::is_signed), "unsigned characters!");

    return 0;
}

