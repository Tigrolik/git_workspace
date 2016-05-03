#ifndef _CIPHER_H
#define _CIPHER_H
#include <stdio.h>
#include <stdlib.h>
#include <string.h>

#define BLOCK_SISE 128

void reverse(char *begin, char *end);
void encrypt(char *s, size_t len);
void resize_string(char **s, size_t new_size);
size_t getstr(char **s, FILE *in);

#endif
