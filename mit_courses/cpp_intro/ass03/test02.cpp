#include "geometry.h"

using namespace std;

int main()
{
    PointArray parray;
    int n = 4;
    Point *arr = new Point[n];

    parray = PointArray(arr, n);

    parray.print();

    PointArray *pnew = new PointArray(arr, n);
    pnew->print();

    PointArray *q = new PointArray(*pnew);
    Point a(3, 5);
    q->insert(2, a);
    Point b(2, 8);
    q->insert(2, b);
    q->print();

    delete pnew;
    delete q;
    delete [] arr;

    return 0;
}
