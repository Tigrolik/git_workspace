#include <stdio.h>

void amaze0()
{
    int i;

    printf("amaze0:\t");

    for (i = 0; i <= 10; i++) {
        if (i % 2 == 1)
            printf("%d ", i);
    }
    printf("\n");
}

void amaze1()
{
    int i;

    printf("amaze1:\t");

    for (i = 1; i <= 10; i += 2) {
        printf("%d ", i);
    }
    printf("\n");
}




int main(int argc, char **argv)
{
    amaze0();
    amaze1();

    return 0;
}
