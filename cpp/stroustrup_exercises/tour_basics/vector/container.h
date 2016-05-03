#ifndef _CONTAINER_H_
#define _CONTAINER_H_

using namespace std;

class Container {
    public:
        virtual double &operator[](size_t) = 0;
        virtual size_t size() const = 0;
        virtual ~Container() {}
};

#endif
