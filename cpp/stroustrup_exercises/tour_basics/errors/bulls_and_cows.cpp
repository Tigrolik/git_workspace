#include <iostream>
#include <vector>

inline int randint(const int low_val, const int high_val) {
    // function returns a random integer between low_val and high_val
    return low_val + rand() % (high_val - low_val);
}

inline int randint(const int high_val) {
    // function returns a random integer between 0 and high_val
    return rand() % high_val;
}

void print_vector(const std::vector<int> v) {
    using namespace std;
    for (auto x : v)
        cout << x << ' ';
    cout << "\b\n";
}

std::vector<int> comp_guess(const int num_digits) {
    // generate computer guess randomly
    using namespace std;
    constexpr int high_val {10};
    vector<int> guess(num_digits);
    for (auto i = 0; i < num_digits; ++i) {
        bool hasequal {true};
        while (hasequal) {
            hasequal = false;
            guess[i] = randint(high_val);
            for (auto j = 0; j < i; ++j)
                if (guess[i] == guess[j]) {
                    hasequal = true;
                    break;
                }
        }
    }
    return guess;
 }

std::vector<int> user_guess(const int num_digits) {
    // function returns digits (0 to 9) entered by the user
    using namespace std;
    cout << "Please, enter your guess (" << num_digits << " digits):\n";
    vector<int> g(num_digits);
    bool iswrong {true};
    while (iswrong) {
        iswrong = false;
        for (auto i = 0; i < num_digits; ++i) {
            cin >> g[i];
            if (g[i] > 10 || g[i] < 0)
                iswrong = true;
        }
        if (iswrong)
            cout << "Some of the values are not digits, try again:\n";
    }
    return g;
}

void game() {
    using namespace std;

    srand(time(nullptr));

    constexpr int num_digits {4};
    const vector<int> guess {comp_guess(num_digits)};

    int bulls {0};
    while (bulls < num_digits) {
        int cows {0};
        bulls = 0;
        vector<int> g {user_guess(num_digits)};
        for (auto i = 0; i < num_digits; ++i)
            for (auto j = 0; j < num_digits; ++j)
                if (guess[i] == g[j]) {
                    if (i == j)
                        ++bulls;
                    else
                        ++cows;
                }
        cout << "Bulls: " << bulls << ", cows: " << cows << endl;
    }

    cout << "You have won!\n";
    print_vector(guess);
}

int main() {

    game();

    return 0;
}
