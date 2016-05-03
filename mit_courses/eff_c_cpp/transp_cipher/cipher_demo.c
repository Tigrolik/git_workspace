#include "cipher.h"
#include <time.h>
#include <stdint.h>

int main(void) {

    char fn[256];

    clock_t s_time;
    uint8_t OK, j, i = 1;

    FILE *in;
    FILE *out;

    s_time = clock();

    OK = 1;
    memset(fn, '\0', sizeof(fn));
    sprintf(fn, "loop.%d.in", i);

    in = fopen("loop.1.in", "r");

    if (in == NULL) {
        fprintf(stderr, "Could not open file\n");
        exit(EXIT_FAILURE);
    }

    char *s = NULL;
    size_t len = getstr(&s, in);
    fclose(in);

    encrypt(s, len);

    out = fopen("loop.out", "w");
    fprintf(out, "%zu\n", len);
    fprintf(out, "%s\n", s);
    fprintf(stdout, "%s\n", s);
    fclose(out);

    free(s);

    j = strlen(fn);
    fn[j - 2] = 'o'; fn[j - 1] = 'u'; fn[j] = 't';
    in = fopen(fn, "r");
    out = fopen("loop.out", "w");

    memset(fn, '\0', sizeof(fn));

    /*
    for (i = 0; i < n; ++i) {
    }
    */

    if (OK)
        printf("%d: OK %f seconds\n", i,
            (double)(clock() - s_time) / CLOCKS_PER_SEC);

    printf("%d\n", 128 << 1);

    return 0;
}
