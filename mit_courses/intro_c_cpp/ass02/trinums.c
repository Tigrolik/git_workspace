#include <stdio.h>
#include <stdlib.h>
#include <math.h>

int main(int argc, char **argv)
{
    int n = argc < 2 ? 100 : atoi(argv[1]);
    int i, s = 0;
    /* number of triangular numbers below n */
    /* int m = floor(1 + 0.5 * (sqrt(1 + n << 3) - 1)); */

    for (i = 0; i < floor(1 + 0.5 * (sqrt(1 + n << 3) - 1)); i++) {
        s += i;
        printf("%d\n", s);
    }

    printf("%d triangular numbers\n", i);

    return 0;
}
