#include <stdlib.h>
#include "matrix_ops.h"

float **matmul(float **A, float **B, int A_rows, int A_cols, int B_rows, int B_cols) {
    if (A_cols != B_rows) {
        printf("Matrix dimensions incompatible for multiplication.\n");
        return NULL;
    }

    float **C = (float **)malloc(A_rows * sizeof(float *));
    for (int i = 0; i < A_rows; i++) {
        C[i] = (float *)malloc(B_cols * sizeof(float));
    }

    for (int i = 0; i < A_rows; i++) {
        for (int j = 0; j < B_cols; j++) {
            C[i][j] = 0;
        }
    }

    for (int i = 0; i < A_rows; i++) {
        for (int j = 0; j < B_cols; j++) {
            for (int k = 0; k < B_rows; k++) {
                C[i][j] += A[i][k] * B[k][j];
            }
        }
    }

    return C;
}


float **matmul_blocking(float blk_size, float **A, float **B, int A_rows, int A_cols, int B_rows, int B_cols) {
    if (A_cols != B_rows) {
        printf("Matrix dimensions incompatible for multiplication.\n");
        return NULL;
    }

    float **C = (float **)malloc(A_rows * sizeof(float *));
    for (int i = 0; i < A_rows; i++) {
        C[i] = (float *)malloc(B_cols * sizeof(float));
        for (int j = 0; j < B_cols; j++) {
            C[i][j] = 0;
        }
    }

    for (int ii = 0; ii < A_rows; ii += blk_size) {
        for (int jj = 0; jj < B_cols; jj += blk_size) {
            for (int kk = 0; kk < A_cols; kk += blk_size) {
                // Multiply the tiles
                for (int i = ii; i < ii + blk_size && i < A_rows; i++) {
                    for (int j = jj; j < jj + blk_size && j < B_cols; j++) {
                        for (int k = kk; k < kk + blk_size && k < A_cols; k++) {
                            C[i][j] += A[i][k] * B[k][j];
                        }
                    }
                }
            }
        }
    }

    return C;
}