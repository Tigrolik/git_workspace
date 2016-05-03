#ifndef _VECTOR2_H_
#define _VECTOR2_H_

#include <initializer_list>

using namespace std;

template<typename T>
class Vector2 {
    private:
        T *elem;
        int sz;
    public:
        Vector2(int s);
        ~Vector2();

        T &operator[](int i);
        const T &operator[](int i) const;
        int size() const;

        T* begin(Vector2<T>&);
        T* end(Vector2<T>&);
};

#endif
