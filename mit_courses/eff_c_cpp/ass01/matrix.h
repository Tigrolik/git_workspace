#ifndef _MATRIX_H
#define _MATRIX_H
#include <stdio.h>
#include <stdlib.h>
#include <stdint.h>
#include <math.h>

#define MAXN 300

typedef struct Matrix_s {
    uint32_t R, C;
    int index[MAXN][MAXN];
} Matrix;

typedef enum {
    REGULAR = 0,
    TRANSPOSE = 1
} Transpose;

typedef struct Matrix_p {
    uint32_t R, C;
    int *index;
} PMatrix;

void read_matrix(FILE *in, Matrix *mx);
PMatrix *read_pmatrix(FILE *in, Transpose orient);
void destroy_matrix(PMatrix *mx);
void print_pmatrix(FILE *out, PMatrix *mx);
void print_matrix(FILE *out, Matrix *mx);
void multiply_matrix(Matrix *A, Matrix *B, Matrix *C);
PMatrix *multiply_pmatrix(PMatrix *A, PMatrix *B);
uint8_t compare_matrices(Matrix *A, Matrix *B);
uint8_t compare_pmatrices(PMatrix *A, PMatrix *B);

#endif
