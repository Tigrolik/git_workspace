#include "stack_class.h"

int main(void)
{
    Stack<int> a, b;
    a.push(1);
    a.push(2);
    b.push(3);
    b.push(4);
    b.push(5);
    Stack<int> c = a + b;
    c.print();
    std::cout << c.top() << std::endl;

    return 0;
}
