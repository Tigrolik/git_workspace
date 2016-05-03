#include <iostream>
#include <algorithm>

using namespace std;

int get_guess() {
    int low_val {10}, hi_val {1000};
    cout << "Please, enter your guess number between (" << low_val <<
        " and " << hi_val << "): ";
    int your_guess {};
    while (true) {
        cin >> your_guess;
        if (your_guess < low_val || your_guess > hi_val)
            cout << "Number is not in the given range, try again\n";
        else
            break;
    }

    // cout << static_cast<int>(log2(hi_val - low_val) + 1) << endl;

    int curr_guess {};
    const int thresh = static_cast<int>(log2(hi_val - low_val) + 1);
    for (auto j = 0; j < thresh; ++j) {
        curr_guess = (hi_val - low_val) / 2 + low_val;
        if (curr_guess < your_guess) {
            low_val = curr_guess;
        } else if (curr_guess > your_guess) {
            hi_val = curr_guess;
        } else {
            break;
        }
    }

    return curr_guess;
}

int main() {

    int guess_num = get_guess();
    cout << "You have guessed " << guess_num << "!\n";

    return 0;
}
