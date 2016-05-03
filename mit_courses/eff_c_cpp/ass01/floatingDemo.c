#include "floating.h"
#include <string.h>
#include <assert.h>
#include <time.h>
#include <unistd.h>

int main()
{
#if 0
    printf("%8X\n", EXPONENT_MASK);
    printf("%f\n", 1 - 1.0 / 16);
    printf("%f\n", 1.1101010101001111111000 * 4 );

    print_hex(1.5);
    print_hex(0.15625);
    print_hex(7.333);
    print_float(stdout, 7.333);

    printf("%d\n", 0x3fc00000);
    print_binary(EXPONENT_MASK);
    print_binary(MANTISSA_MASK);
#endif
    float f;
    f = 0.00000000000000000000000000000000000001175495000000;
    f = 2222222222222222222222222222222222222222222.0;
    print_float(stdout, f);
    print_hex(f);
    print_binary(*((int*)&f));
    print_binary(0x3e200000);
    //printf("%f\n", 0.15625 * 8);
    printf("%f\n", (1.0 + 0.25) / 8);

    char fn[256];
    char s[256];
    uint32_t i, n;
    uint8_t OK;

    FILE *in;
    FILE *out;

    clock_t start_time;
    for (uint8_t j = 1; j < 8; ++j) {
        start_time = clock();
        OK = 1;
        memset(fn, '\0', sizeof(fn));
        sprintf(fn, "floating.%d.in", j);
        in  = fopen(fn, "r");
        out = fopen("floating.out", "w");

        fscanf(in, "%u", &n);

        for (i = 0; i < n; ++i) {
            fscanf(in, "%f", &f);
            print_float(out, f);
        }

        fclose(in);
        fclose(out);

        fn[11] = 'o'; fn[12] = 'u'; fn[13] = 't';
        in  = fopen(fn, "r");
        out = fopen("floating.out", "r");

        memset(fn, '\0', sizeof(fn));
        for (i = 0; i < n; ++i) {
            fgets(s, sizeof(s), in);
            fgets(fn, sizeof(fn), out);
            if (strcmp(s, fn)) {
                OK = 0;
                printf("%d: %s\n", i, s);
                printf("%d: %s\n", i, fn);
            }
            //assert(!strcmp(s, fn));
        }
        /*
           while (fgets(s, sizeof(s), in))
           printf("%s\n", s);
           */

        fclose(in);
        fclose(out);

        if (OK) {
            printf("%d: OK %f seconds\n", j,
                    (double)(clock() - start_time) / CLOCKS_PER_SEC);
        }
    }
    return 0;
}
