#include <stdlib.h>
#include "matrix_ops.h"

typedef struct {
    float *nz_values;
    int *row_indices;
    int *column_indices;
    int nz_count;
    int row_idx_count;
    int column_idx_count;
} CSRMatrix;


// make CSR matrix from (sparse) matrix
CSRMatrix* constructCSR(float **matrix, int row_idx_count, int column_idx_count) {
    int nz_count = 0;
    for(int i = 0; i < row_idx_count; i++) {
        for(int j = 0; j < column_idx_count; j++) {
            if(matrix[i][j] != 0.0) {
                nz_count++;
            }
        }
    }

    int *row_indices = (int *)malloc((row_idx_count + 1) * sizeof(int));
    float *nz_values = (float *)malloc(nz_count * sizeof(float));
    int *column_indices = (int *)malloc(nz_count * sizeof(int));

    int k = 0;
    for(int i = 0; i < row_idx_count; i++) {
        row_indices[i] = k;
        for(int j = 0; j < column_idx_count; j++) {
            if(matrix[i][j] != 0.0) {
                nz_values[k] = matrix[i][j];
                column_indices[k] = j;
                k++;
            }
        }
    }
    row_indices[row_idx_count] = k;

    CSRMatrix *csr = (CSRMatrix *)malloc(sizeof(CSRMatrix));
    csr->row_indices = row_indices;
    csr->column_indices = column_indices;
    csr->nz_values = nz_values;
    csr->row_idx_count = row_idx_count;
    csr->column_idx_count = column_idx_count;
    csr->nz_values = nz_values;

    return csr;
}

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