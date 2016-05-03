#include "matrix.h"

/* Function read_matrix;
 * ---------------------------------------
 *  reads matrix data from a file
 */
void read_matrix(FILE *in, Matrix *mx)
{
    if (fscanf(in, "%u %u", &mx->R, &mx->C)) {

        if (mx->R >= MAXN || mx->C >= MAXN) {
            fprintf(stderr, "Error: too big matrix\n");
            exit(EXIT_FAILURE);
        }

        uint32_t j;
        for (uint32_t i = 0; i < mx->R; ++i) {
            for (j = 0; j < mx->C; ++j) {
                if (fscanf(in, "%d", &mx->index[i][j])) {
                }
            }
        }
    }
}

PMatrix *new_matrix(uint32_t R, uint32_t C)
{
    PMatrix *mx = malloc(sizeof(*mx));
    mx->R = R;
    mx->C = C;
    mx->index = malloc(R * C * sizeof(mx->index));
    return mx;
}

void destroy_matrix(PMatrix *mx)
{
    free(mx->index);
    free(mx);
}

PMatrix *read_pmatrix(FILE *in, Transpose orient)
{

    if (orient == TRANSPOSE) {
        uint32_t R, C;
        if (fscanf(in, "%u %u", &R, &C)) {
        }
        PMatrix *mx = new_matrix(C, R);
        uint32_t j;
        for (uint32_t i = 0; i < R; ++i)
            for (j = 0; j < C; ++j)
                if (fscanf(in, "%d", &mx->index[i + j * R])) {
                }
        return mx;
    } else if (orient == REGULAR) {
        uint32_t R, C;
        if (fscanf(in, "%u %u", &R, &C)) {
        }
        PMatrix *mx = new_matrix(R, C);
        uint32_t j, r;
        for (uint32_t i = 0; i < R; ++i) {
            r = i * C;
            for (j = 0; j < C; ++j)
                if (fscanf(in, "%d", &mx->index[j + r])) {
                }
        }
        return mx;
    } else {
        fprintf(stderr, "Error: unknown orientation\n");
        exit(EXIT_FAILURE);
    }
}
/* Function print_matrix;
 * ---------------------------------------
 *  displays matrix content
 */
void print_matrix(FILE *out, Matrix *mx)
{
    fprintf(out, "%u %u\n", mx->R, mx->C);
    uint32_t j;
    for (uint32_t i = 0; i < mx->R; ++i) {
        for (j = 0; j < mx->C - 1; ++j)
            fprintf(out, "%d ", mx->index[i][j]);
        fprintf(out, "%d\n", mx->index[i][mx->C - 1]);
    }
}

void print_pmatrix(FILE *out, PMatrix *mx)
{
    uint32_t rows = mx->R;
    uint32_t cols = mx->C;

    fprintf(out, "%u %u\n", rows, cols);
    uint32_t j, r;
    for (uint32_t i = 0; i < rows; ++i) {
        r = i * cols;
        for (j = 0; j < cols - 1; ++j)
            fprintf(out, "%d ", mx->index[j + r]);
        fprintf(out, "%d\n", mx->index[cols - 1 + r]);
    }

}

/* Function multiply_matrix;
 * ---------------------------------------
 *  multiplies matrices A and B and stores the
 *  result in matrix C
 */
void multiply_matrix(Matrix *A, Matrix *B, Matrix *C)
{
    if (A->C != B->R) {
        C->R = 0;
        C->C = 0;
        fprintf(stderr, "Cannot multiply matrices\n");
        exit(EXIT_FAILURE);
    }

    uint32_t j, k;
    C->R = A->R;
    C->C = B->C;
    for (uint32_t i = 0; i < C->R; ++i)
        for (j = 0; j < C->C; ++j) {
            C->index[i][j] = 0;
            for (k = 0; k < A->C; ++k) {
                C->index[i][j] += A->index[i][k] * B->index[k][j];
            }
        }

    return;
}

PMatrix *multiply_pmatrix(PMatrix *A, PMatrix *B)
{
    uint32_t AC = A->C;
    if (AC != B->C) {
        fprintf(stderr, "Cannot multiply matrices\n");
        exit(EXIT_FAILURE);
    }

    uint32_t rows = A->R;
    uint32_t cols = B->R;
    PMatrix *C = new_matrix(rows, cols);
    uint32_t j, k, r, tempA, tempB;
    for (uint32_t i = 0; i < rows; ++i)
        for (j = 0; j < cols; ++j) {
            r = j + i * cols;
            C->index[r] = 0;
            tempA = i * AC;
            tempB = j * AC;
            for (k = 0; k < AC; ++k) {
                C->index[r] += A->index[k + tempA] * B->index[k + tempB];
            }
        }

    return C;
}

/* Function compare_matrices:
 * ----------------------------------
 *  compares two matrices: 0 - not equal, 1 - equal
 */
uint8_t compare_matrices(Matrix *A, Matrix *B)
{
    if ((A->R != B->R) || (A->C != B->C))
        return 0;

    uint32_t j;
    for (uint32_t i = 0; i < A->R; ++i)
        for (j = 0; j < A->C; ++j)
            if (A->index[i][j] != B->index[i][j])
                return 0;

    return 1;
}

uint8_t compare_pmatrices(PMatrix *A, PMatrix *B)
{
    if ((A->R != B->R) || (A->C != B->C))
        return 0;

    for (uint32_t i = 0; i < A->R * A->C; ++i)
        if (A->index[i] != B->index[i]) {
            printf("%d %d %d %d\n", A->R, A->C, A->index[i], B->index[i]);
            return 0;
        }

    return 1;
}
