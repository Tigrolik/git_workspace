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

void print_vector(const std::vector<char> v) {
    using namespace std;
    for (auto x : v)
        cout << x << ' ';
    cout << "\b\n";
}

std::vector<char> comp_guess(const int num_letters) {
    // generate computer guess randomly
    using namespace std;
    constexpr char low_val {'a'}, high_val {'z'};
    vector<char> guess(num_letters);
    for (auto i = 0; i < num_letters; ++i) {
        bool hasequal {true};
        while (hasequal) {
            hasequal = false;
            guess[i] = randint(low_val, high_val);
            for (auto j = 0; j < i; ++j)
                if (guess[i] == guess[j]) {
                    hasequal = true;
                    break;
                }
        }
    }
    return guess;
 }

std::vector<char> user_guess(const int num_letters) {
    // function returns letters (a to z) entered by the user
    using namespace std;
    cout << "Please, enter your guess (" << num_letters <<
        " low-case letters):\n";
    vector<char> g(num_letters);
    bool iswrong {true};
    while (iswrong) {
        iswrong = false;
        for (auto i = 0; i < num_letters; ++i) {
            cin >> g[i];
            if (g[i] > 'z' || g[i] < 'a')
                iswrong = true;
        }
        if (iswrong)
            cout << "Some of the values are not low-case letters, try again:\n";
    }
    return g;
}

void game() {
    using namespace std;

    srand(time(nullptr));

    constexpr int num_letters {4};
    const vector<char> guess {comp_guess(num_letters)};

    int bulls {0};
    while (bulls < num_letters) {
        int cows {0};
        bulls = 0;
        vector<char> g {user_guess(num_letters)};
        print_vector(g);
        for (auto i = 0; i < num_letters; ++i)
            for (auto j = 0; j < num_letters; ++j)
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
