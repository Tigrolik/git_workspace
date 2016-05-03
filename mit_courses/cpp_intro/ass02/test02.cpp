#include <iostream>

using namespace std;

const int LENGTH = 5;
const int WIDTH = 4;

void printArray(const int array[], const int len) {
    int i;
    for (i = 0; i < len - 1; ++i)
        cout << array[i] << ", ";
    cout << array[i] << endl;
}

void reverse(int array[], const int len) {
    int temp;
    for (int i = 0; i < len / 2; ++i) {
        temp = *(array + i);
        int j = len - i - 1;
        *(array + i)= *(array + j);
        *(array + j) = temp;
    }
}

void transpose(const int input[][LENGTH], int output[][WIDTH])
{
    for (int i = 0; i < WIDTH; ++i)
        for (int j = 0; j < LENGTH; ++j) {
            output[j][i] = input[i][j];
        }
}

int main()
{
    int array[] = {1, 2, 5, 4, 8, 9};
    int n = sizeof(array) / sizeof(array[0]);

    printArray(array, n);
    reverse(array, n);
    printArray(array, n);

    return 0;
}
