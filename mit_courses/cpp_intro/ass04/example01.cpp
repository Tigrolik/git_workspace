#include <iostream>
#include <set>
#include <algorithm>

using namespace std;

void printArray(const int arr[], const int len) {
    for (int i = 0; i < len; ++i)
        cout << " " << arr[i];
    cout << endl;
}

int main(void)
{
    set<int> iset;
    iset.insert(5);
    iset.insert(9);
    iset.insert(1);
    iset.insert(8);
    iset.insert(8);
    iset.insert(3);

    cout << "iset contains:";
    set<int>::iterator it;
    for (it = iset.begin(); it != iset.end(); ++it)
        cout << " " << *it;
    cout << endl;

    int searchFor;
    cin >> searchFor;

    if (binary_search(iset.begin(), iset.end(), searchFor))
        cout << "Found " << searchFor << endl;
    else
        cout << "Did not find " << searchFor << endl;

    int a[] = {5, 7, 2, 1, 4, 3, 4, 6};

    sort(a, a + 7);
    printArray(a, 7);
    rotate(a, a + 3, a + 7);
    printArray(a, 7);
    reverse(a, a + 7);
    printArray(a, 7);

    return 0;
}
