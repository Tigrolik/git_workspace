#include <iostream>

int main() {
    char c {};
    using namespace std;
    while ((c = cin.peek()) != '!')
        cin.get(c);
    cout << "You entered \'!\'. The next character is ";
    cin.get(c);
    cout << c << endl;

    return 0;
}
