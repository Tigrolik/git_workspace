#include <iostream>
#include <vector>

using namespace std;

// declare class template: templated forward declaration
template <class T> class Stack;

// declare friend function prototype
template <class T>
Stack<T> operator + (const Stack<T> &s1, const Stack<T> &s2);

template <class T>
class Stack
{
    private:
        // extra <> are included to indicate the templated function
        friend Stack<T> operator +<> (const Stack<T> &s1, const Stack<T> &s2);
        vector<T> items;

    public:
        bool empty() const {
            return items.empty();
        }

        void push(const T &item) {
            items.push_back(item);
        }

        T pop() {
            T last = items.back();
            items.pop_back();
            return last;
        }

        T &top() {
            return items.back();
        }

        void print() {
            for (unsigned i = 0; i < items.size(); ++i)
                cout << items[i] << ' ';
            cout << endl;
        }
};

template <class T>
Stack<T> operator + (const Stack<T> &s1, const Stack<T> &s2) {
    Stack<T> result = s1;
    for (unsigned i = 0; i < s2.items.size(); ++i)
        result.items.push_back(s2.items[i]);
    return result;
}
