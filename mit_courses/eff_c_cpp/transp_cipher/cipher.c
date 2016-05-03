#include "cipher.h"

void reverse(char *begin, char *end)
{
    char tmp;
    --end;
    for (char *p = begin; p < end; ++p, --end) {
        tmp = *p;
        *p = *end;
        *end = tmp;
    }
}

void encrypt(char *s, size_t len)
{
    if (len > 2) {
        size_t k = len / 2;

        reverse(s, s + k);
        reverse(s + k, s + len);

        encrypt(s + k, len - k);
        encrypt(s, k);
    }
}

void resize_string(char **s, size_t new_size)
{
    if (*s == NULL) {
        *s = malloc(new_size);
    } else {
        char *tmp = realloc(*s, new_size);
        if (tmp == NULL)
            fprintf(stderr, "Failed realloc to size %zu.\n", new_size);
        else
            *s = tmp;
    }
}

size_t getstr(char **s, FILE *in)
{
    size_t chars_to_read = BLOCK_SISE;
    size_t len = 0;

    // if s already exists we shall append to the end
    if (*s != NULL) {
        len = strlen(*s);
        while (chars_to_read < len)
            chars_to_read <<= 1;
    }

    resize_string(s, chars_to_read << 1);

    size_t chars = 0;
    while ((chars = fread(*s + len, 1, chars_to_read, in))) {
        len += chars;
        if (chars == chars_to_read) {
            chars_to_read <<= 1;
            resize_string(s, chars_to_read << 1);
        } else {
            break; // EOF
        }
    }

    // add '\0' and resize to save space
    if (len > 0) {
        len--;
        (*s)[len] = '\0';
        char *tmp = realloc(*s, len + 1);
        if (tmp != NULL)
            *s = tmp;
    }

    return len;
}
