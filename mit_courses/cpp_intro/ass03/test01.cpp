#include "geometry.h"

using namespace std;

int main()
{
    Point p1(3, 5);

    p1.print();

    Point q1;
    q1.print();

    Point *p2 = new Point(4);
    p2->print();
    delete p2;

    return 0;
}
