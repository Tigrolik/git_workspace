#include <iostream>

#define my_min(x, y) (x < y ? x : y)

template <typename T>
T min(const T a, const T b) {
    return a < b ? a : b;
}

int main(void)
{
    std::cout << min(3, 5) << ' ' <<  min(2.4, 7.8) << ' ' <<
        min('a', 'k') << ' ' << min("help", "car") << std::endl;
    std::cout << std::min(5, 3) << std::endl;
    std::cout << my_min(3, 5) << ' ' <<  my_min(2.4, 7.8) << ' ' <<
        my_min('a', 'k') << ' ' << my_min("help", "car") << std::endl;
    return 0;
}
