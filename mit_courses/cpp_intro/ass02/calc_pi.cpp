#include <iostream>
#include <cstdlib>
#include <cmath>

using namespace std;

double random_double() {
    return rand() / (double(RAND_MAX) + 1);
}

double approx_pi(const int n) {
    srand(time(0));
    int count = 0;
    double x, y;

    for (int i = 0; i < n; ++i) {
        x = random_double();
        y = random_double();
        if (sqrt(x * x + y * y) < 1)
            ++count;
    }

    return count / (double)n * 4;
}

int main()
{
    int numberOfThrows = 5e6;

    double num_pi = approx_pi(numberOfThrows);

    cout << "Pi approximation = " << num_pi << endl;

    return 0;
}
