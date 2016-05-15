#include "Point.h"

void test_point() {
    // testing point
    const Point<int> p1 {15, 23}, p2 {{17, 9}}, p3 {{31, 74, 28, 10}};
    std::cout << p1 << ' ' << p2 << ' ' << p3 << '\n';
    std::cout << "unchecked access (p1[5] == p1[2]): " <<p1[5] << '\n';
    try {
        std::cout << p1.at(5) << '\n';
    } catch (const Range_error& re) {
        std::cout << re.what() << '\n';
    }
    //std::cout << p1.at(1) << '\n';
    Point<int> p4 {7, 9, 4};
    p4.y() = 3;
    std::cout << p4.y() << '\n';
}

void test_arrayp() {
    Point_array<int> pa1 {std::vector<Point<int>>{Point<int> {28, 73},
        Point<int> {49, 62, 35}, Point<int> {10, 21}}};
    pa1.push_back(Point<int> {14, 29, 17});
    pa1.insert(std::begin(pa1), Point<int> {-7, -4, -9});
    pa1.erase(pa1.begin() + 2, pa1.begin() + 4);
    std::cout << pa1 << '\n';
    //const auto p = pa1.cbegin();
    const auto p = std::begin(pa1);
    if (p != pa1.cend())
        std::cout << *p << '\n';
}

int main() {

    //test_point();
    test_arrayp();

    return 0;
}

