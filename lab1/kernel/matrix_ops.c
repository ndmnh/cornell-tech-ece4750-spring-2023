#include <stdlib.h>
#include "matrix_ops.h"

#define TILE_SIZE 32  // This is just an example; adjust based on your architecture

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


float **matmul_blocking(float **A, float **B, int A_rows, int A_cols, int B_rows, int B_cols) {
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

    for (int ii = 0; ii < A_rows; ii += TILE_SIZE) {
        for (int jj = 0; jj < B_cols; jj += TILE_SIZE) {
            for (int kk = 0; kk < A_cols; kk += TILE_SIZE) {
                // Multiply the tiles
                for (int i = ii; i < ii + TILE_SIZE && i < A_rows; i++) {
                    for (int j = jj; j < jj + TILE_SIZE && j < B_cols; j++) {
                        for (int k = kk; k < kk + TILE_SIZE && k < A_cols; k++) {
                            C[i][j] += A[i][k] * B[k][j];
                        }
                    }
                }
            }
        }
    }

    return C;
}