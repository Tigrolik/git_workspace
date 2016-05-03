#include <stdio.h>

int main(int argc, char ** argv){
    int i = 1;

begin:
    if (i < argc) {
        printf("%s\n", argv[i]);
        i++;
        goto begin;
    } else {
        goto end;
    }

end:
   return 0;
}
