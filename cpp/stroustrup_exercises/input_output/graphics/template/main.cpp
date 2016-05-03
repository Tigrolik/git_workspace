#include "std_lib_facilities.h"
#include "Point.h"
#include "fltk.h"
#include "Graph.h"
#include "GUI.h"
#include "Simple_window.h"

void test_point() {
    using namespace Graph_lib;

    Point p1 {3, 5};
    Point p2 {3, 5};
    cout << (p1 == p2) << endl;
}

void test_win() {
    using namespace Graph_lib;

    Point tl {100, 100};
    Simple_window win (tl, 600, 400, "Canvas");

    Polygon poly;

    poly.add(Point{300, 200});
    poly.add(Point{350, 100});
    poly.add(Point{400, 200});

    poly.set_color(Color::red);

    win.attach(poly);

    win.wait_for_button();
}

int main() {

    //test_point();
    test_win();

    return 0;
}
