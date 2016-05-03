#include <stdio.h>
#include <string.h>
#include <stdlib.h>

void square(int *num) {
	*num *= *num;
}

int main() {
	int x = 4;
	square(&x);
	printf("%d\n", x);

    char *str = malloc(sizeof(*str) * 20);
    strcpy(str, "hakuna matata!"); // this line should copy "hakuna matata!"
    // into our char array
    printf("%s\n", str);
    // Anything else?
    free(str);

	return 0;
}
