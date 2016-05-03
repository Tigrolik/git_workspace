#include <iostream>
#include <vector>
#include <algorithm>

template <class T>
class Number {
public:
    Number(const T &t): val_ {t} { }
    Number(const Number &n): val_{n.val_} { }
    Number& operator=(const Number &n) {
        if (this != &n)
            val_ = n.val_;
        return *this;
    }

    const Number operator+(const Number &n) const {
        return Number {val_ + n.val_};
    }

    const Number operator-(const Number &n) const {
        return Number {val_ - n.val_};
    }

    const Number operator*(const Number &n) const {
        return Number {val_ * n.val_};
    }

    const Number operator/(const Number &n) const {
        return Number {val_ / n.val_};
    }

    const Number operator%(const Number &n) const {
        return Number {val_ % n.val_};
    }

    const T& value() const { return val_; }
    friend std::ostream& operator<<(std::ostream &os, const Number &n) {
        return os << n.val_;
    }
private:
    T val_;
};

using namespace std;

template <class T, class U>
typename std::common_type<T, U>::type acc_sum(const vector<T> vt,
        const vector<U> &vu) {
    typename std::common_type<T, U>::type s {};
    for (size_t i {0}; i < min(vt.size(), vu.size()); ++i)
        s += vt[i] * vu[i];
    return s;
}

void test_number() {
    Number<int> ni {7};
    Number<int> ni2 {ni};
    Number<int> ni3 = ni2 * ni;
    std::cout << ni3 % (ni2 + ni2) << '\n';
    Number<double> nd {7};
    Number<double> nd2 {nd};
    Number<double> nd3 = nd2 * nd;
    std::cout << nd3 / (nd + nd2) << '\n';
}

void test_sumacc() {
    vector<int> vi {1, 2, 4, 8, 16};
    vector<double> vd {0.5, 2.5, 2, 1.5, 0,0};
    const int si = std::round(acc_sum(vi, vd));
    const double sd {acc_sum(vd, vi)};
    cout << si << '\n';
    cout << sd << '\n';
}

int main() {

    //test_number();
    test_sumacc();

    return 0;
}

