#include "Point.h"
#include "Vec.h"
#include "Mat.h"

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

void test_vec() {
    // testing initializing vectors
    Vec<3, int> vi1 (5);
    std::cout << "vi1 = " << vi1 << '\n';
    Vec<2, double> vd1 {std::array<double, 2> {2.7, 9.1}};
    std::cout << "vd1 = " << vd1 << '\n';
    Vec<4, char> vc1 {'a', 'b', 'c', 'd'};
    std::cout << "vc1 = " << vc1 << '\n';
    Vec<5, long> vl1;
    std::cout << "vl1 = " << vl1 << '\n';
    Vec<3, float> vf1 {1.4, 3.5};
    std::cout << "vf1 = " << vf1 << '\n';
    using Vec3i = Vec<3, int>;
    using Vec3d = Vec<3, double>;
    Vec3i vi2 {vi1};
    Vec3i vi3 = vi2;
    std::cout << "vi3 = " << vi3 << '\n';
    Vec3d vd2 {vi3};
    std::cout << "vd2 = " << vd2 << '\n';
    Vec<3, long> vl2 {vf1};
    std::cout<< "vl2 = " << vl2 << '\n';
    Vec<3, int> vi4 = vd1;
    std::cout<< "vi4 = " << vi4 << '\n';
    Vec<2, float> vf2 = vc1;
    std::cout << "vf2 = " << vf2 << '\n';
    std::cout << "vi1 + vf1 = " << vi1 + vf1 << '\n';
    std::cout << "vd1 + 7 = " << vd1 + 7 << '\n';
    std::cout << "vi1 - Vec<3, double> {4.8, 2.7, 3.1} = " << vi1 -
        Vec<3, double> {4.8, 2.7, 3.1} << '\n';
    std::cout << "Vec<4, float> {1.5, 2.5, 3.5, 4.5} * 2 = " <<
        Vec<4, float> {1.5, 2.5, 3.5, 4.5} * 2 << '\n';
    std::cout << "Vec<4, int> {10, 20, 30, 40} / 4.0 = " <<
        Vec<4, int> {10, 20, 30, 40} / 4.0 << '\n';
    const Vec<3, double> vd3 {0.5, 2.4, 3.8};
    std::cout << "vd3 = " << vd3 << '\n';
    double sd {vi1 * vd3};
    std::cout << "dot product vi1 * vd3 = " << sd << '\n';
    double vi_norm {vi1.norm()};
    std::cout << "vi1.norm() = " << vi_norm << '\n';
    std::cout << "vi1 normalized = " << vi1.normalize() << '\n';
    std::cout << "vi1 = " << vi1 << '\n';
    std::cout << "vd3.norm() = " << vd3.norm() << '\n';
    std::cout << "vd3 normalized = " << vd3.normalize() << '\n';
    std::cout << "vd3 = " << vd3 << '\n';
    std::cout << "vi1 x vd3 = " << (vi1 ^ vd3) << '\n';
}

void test_mat() {
    // using standard (round) brackets for filling the matrix
    Mat<2, 2, int> mi1 (7);
    if (mi1 != Mat<2, 2, int>(7))
        std::cout << "wrong matrix\n";
    Mat<2, 2, float> mf1 (7.3);
    mf1.at(1).at(1) = 4.9; mf1[0].at(1) = 2.8;
    mf1[0][0] = 5.3; mf1.at(1)[0] = 6.4;
    std::cout << "mf1 size: " << mf1.size() << '\n';
    Vec<2, int> mi1_size {mi1.size()};
    if (mi1_size != Vec<2, int>(2))
        std::cout << "wrong matrix size\n";
    Mat<3, 2, int> mi2 {std::array<std::array<int, 2>, 3> {
        std::array<int, 2> {12, 19}, std::array<int, 2> {14, 15},
            std::array<int, 2> {15, 11}}};
    std::cout << "mi2 size: " << mi2.size() << '\n';
    Mat<3, 4, double> md1 {{1.5, 2.4, 9.6}, {3.7, 8.2}, {7.5}};
    std::cout << md1 << '\n';
    Mat<3, 4, int> mi3 {md1};
    std::cout << mi3 << '\n';
    Mat<2, 3, int> mi4 = md1;
    std::cout << mi4 << '\n';
    Mat<5, 2, float> mf2 (Vec<2, float> {1.3, 5.9});
    std::cout << mf2 << '\n';
    Mat<2, 2, int> mi5 (Vec<2, float> {1.3, 5.9} + 0.5);
    std::cout << mi5 << '\n';
    Mat<4, 2, double> md2 {1.5, 2.4, 3.7, 9.8};
    if ((md2 += 3.4) != Mat<4, 2, double>{4.9, 5.8, 7.1, 13.2})
        std::cout << "compound plus failed\n";
    Mat<2, 3, int> mi6 {{2, 5, 8}, {4, 3, 9}};
    if ((mi6 += Vec<2, int>{4, 7}) != Mat<2, 3, int>{{6, 9, 12}, {11, 10, 16}})
        std::cout << "compound plus failed\n";
    Mat<2, 2, double> md3 {{2.5, 5.4}, {4.2, 3.7}};
    if ((md3 += Mat<2, 2, int> {{8, 1}, {3, 4}}) !=
            Mat<2, 2, double>{{10.5, 6.4}, {7.2, 7.7}})
        std::cout << "compound plus failed\n";
    Mat<2, 2, int> mi7 {{2, 8}, {3, 7}};
    std::cout << (mi7 *= 5.0) << '\n';
    std::cout << (mi7 /= 3) << '\n';
}

void test_mat_arithmetic() {
    Mat<2, 3, int> mi1 {{1, 2, 3}, {4, 5, 6}}, mi2 {{8, 5, 4}, {6, 7, 2}};
    Mat<2, 3, double> md1 {{1.5, 2.5, 4.5}, {0.2, 6.4, 8.6}};
    auto ma1 = mi1 + mi2 + md1;
    Mat<2, 3, int> mi3 = mi1 + mi2 + md1;
    std::cout << ma1 << '\n';
    std::cout << mi3 << '\n';
    auto ma2 = mi1 * 3 + mi2 * 1.5 + md1 / 4;
    std::cout << ma2 << '\n';
    Vec<3, double> vd1 {8.5, 5.4, 2.7};
    std::cout << mi1 << '\n';
    std::cout << vd1 << '\n';
    std::cout << "mi1 * vd1 = " << mi1 * vd1 << '\n';
    Mat<3, 4, int> mi4 {{-2, 3, -8, 5}, {4, 7, -9, 3}, {0, -5, 4, 1}};
    std::cout << mi4 << '\n';
    std::cout << "mi1 * mi4 = " << mi1 * mi4 << '\n';
}

int main() {

    //test_point();
    //test_arrayp();
    //test_vec();
    //test_mat();
    test_mat_arithmetic();

    return 0;
}

