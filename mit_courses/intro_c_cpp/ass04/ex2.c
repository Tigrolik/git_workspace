#include <stdlib.h>
#include <stdio.h>

int main(int argc, char **argv)
{
    union int_bytes {
        int byte1;
        int byte2;
        int byte3;
        int byte4;
    };

    int x = 12578329; // 0xBFEE19
    union int_bytes x_bytes;

    x_bytes.byte1 = (x >> 24) & 0xFF;
    printf("%02X", x_bytes.byte1);
    x_bytes.byte2 = (x >> 16) & 0xFF;
    printf("%02X", x_bytes.byte2);
    x_bytes.byte1 = (x >> 8) & 0xFF;
    printf("%02X", x_bytes.byte3);
    x_bytes.byte1 = x & 0xFF;
    printf("%02X\n", x_bytes.byte4);

    struct X
    {
        short s;
        int i;
        char c;
    };

    struct Y
    {
        int i;
        char c;
        short s;
    };

    struct Z
    {
        int   i;
        short s;
        char  c;
    };

    printf("Size of struct X = %lu\n", sizeof(struct X));
    printf("Size of struct Y = %lu\n", sizeof(struct Y));
    printf("Size of struct Z = %lu\n", sizeof(struct Z));

    return 0;
}
