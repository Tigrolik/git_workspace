#include "matrix.h"
#include <string.h>
#include <time.h>

int main()
{
    char fn[256];
    uint8_t j;

    FILE *in;
    FILE *out;

    /*
    Matrix A, B, C;
    */
    PMatrix *PA, *PB, *PC;

    clock_t start_time;
    for (uint8_t i = 1; i < 12; i++) {
        start_time = clock();
#if 0
        memset(fn, '\0', sizeof(fn));
        sprintf(fn, "matrix.%d.in", i);

        /* read matrices from the file */
        in = fopen(fn, "r");
        read_matrix(in, &A);
        read_matrix(in, &B);
        fclose(in);

        /* perform multiplication on the matrices */
        multiply_matrix(&A, &B, &C);

        /* write the result to the file */
        out = fopen("matrix.out", "w");
        print_matrix(out, &C);
        fclose(out);

        /* read files again and compare matrices */
        j = strlen(fn);
        fn[j - 2] = 'o'; fn[j - 1] = 'u'; fn[j] = 't';
        in = fopen(fn, "r");
        out = fopen("matrix.out", "r");

        read_matrix(in, &A);
        read_matrix(out, &B);

        fclose(in);
        fclose(out);
#endif
        /* test PMatrix */

        memset(fn, '\0', sizeof(fn));
        sprintf(fn, "matrix2.%d.in", i);

        in = fopen(fn, "r");
        PA = read_pmatrix(in, REGULAR);
        PB = read_pmatrix(in, TRANSPOSE);
        fclose(in);

        PC = multiply_pmatrix(PA, PB);
        destroy_matrix(PA);
        destroy_matrix(PB);

        out = fopen("matrix2.out", "w");
        print_pmatrix(out, PC);
        fclose(out);

        j = strlen(fn);
        fn[j - 2] = 'o'; fn[j - 1] = 'u'; fn[j] = 't';
        in = fopen(fn, "r");
        PA = read_pmatrix(in, REGULAR);

        if (compare_pmatrices(PA, PC))
            printf("%02d: OK %f seconds\n", i,
                    (double)(clock() - start_time) / CLOCKS_PER_SEC);

        destroy_matrix(PA);
        destroy_matrix(PC);

        fclose(in);
    }
    return 0;
}
