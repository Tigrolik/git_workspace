#include "geometry.h"

void printAttributes(Polygon *p) {
    cout << "Polygon area: " << p->area() << endl;
    p->getPoints()->print();
}

int main()
{
    cout << "Enter lower left and upper right coordinates for the rectangle" <<
        " as four separated integers" << endl;
    int x1, y1, x2, y2;

    cin >> x1 >> y1 >> x2 >> y2;
    // Rectangle rect(Point(x1, y1), Point(x2, y2));
    Rectangle rect(x1, y1, x2, y2);
    printAttributes(&rect);

    cout << "Enter coordinates of a triangle as six integers" << endl;
    int x3, y3;

    cin >> x1 >> y1 >> x2 >> y2 >> x3 >> y3;

    Triangle tri(Point(x1, y1), Point(x2, y2), Point(x3, y3));
    printAttributes(&tri);

    return 0;
}
