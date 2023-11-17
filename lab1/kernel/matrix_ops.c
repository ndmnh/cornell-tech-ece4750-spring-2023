#include <stdlib.h>
#include "matrix_ops.h"
#include <pthread.h>

int BLK_SIZE = 32;

typedef struct {
    int *row_pointers;
    int *column_indices;
    float *values;
    int nrows;
    int ncols;
    int nnz; // Number of non-zero elements
} CSRMatrix;

typedef struct {
    float **A, **B, **C;
    int row, A_cols, B_cols;
} ThreadArgs;

#define CACHE_LINE_SIZE 64 // Common cache line size



// make CSR matrix from (sparse) matrix
CSRMatrix* constructCSR(float **matrix, int nrows, int ncols) {
    int nnz = 0; // Count of non-zero elements
    for(int i = 0; i < nrows; i++) {
        for(int j = 0; j < ncols; j++) {
            if(matrix[i][j] != 0.0) {
                nnz++;
            }
        }
    }

    int *row_pointers = (int *)malloc((nrows + 1) * sizeof(int));
    float *values = (float *)malloc(nnz * sizeof(float));
    int *column_indices = (int *)malloc(nnz * sizeof(int));

    int k = 0;
    for(int i = 0; i < nrows; i++) {
        row_pointers[i] = k;
        for(int j = 0; j < ncols; j++) {
            if(matrix[i][j] != 0.0) {
                values[k] = matrix[i][j];
                column_indices[k] = j;
                k++;
            }
        }
    }
    row_pointers[nrows] = k;

    CSRMatrix *csr = (CSRMatrix *)malloc(sizeof(CSRMatrix));
    csr->row_pointers = row_pointers;
    csr->column_indices = column_indices;
    csr->values = values;
    csr->nrows = nrows;
    csr->ncols = ncols;
    csr->nnz = nnz;

    return csr;
}

float** matmul_csr(CSRMatrix* A, CSRMatrix* B) {
    if (A->ncols != B->nrows) {
        printf("Matrix dimensions incompatible for multiplication.\n");
        return NULL;
    }

    // Initialize the resulting matrix C to all zeros
    float** C = (float**) malloc(A->nrows * sizeof(float*));
    for (int i = 0; i < A->nrows; i++) {
        C[i] = (float*) calloc(B->ncols, sizeof(float));
    }

    // Carry out matrix multiplication
    for (int i = 0; i < A->nrows; i++) {
        for (int k = A->row_pointers[i]; k < A->row_pointers[i + 1]; k++) {
            int row_B = A->column_indices[k];
            float val_A = A->values[k];
            for (int j = B->row_pointers[row_B]; j < B->row_pointers[row_B + 1]; j++) {
                int col_B = B->column_indices[j];
                float val_B = B->values[j];
                C[i][col_B] += val_A * val_B;
            }
        }
    }

    return C;
}


float **matmul_sparse(float **A, float **B, int A_rows, int A_cols, int B_rows, int B_cols) {
    float **result;
    /**** 1. Create CSR format of input matrix ****/
    // When profiling, only loop over part 2.
    CSRMatrix* csr_A = constructCSR(A, A_rows, A_cols);
    CSRMatrix* csr_B = constructCSR(B, B_rows, B_cols);

    /**** 2. Perform matrix multiplication on CSR format of input
    matrix ****/
    float** C = matmul_csr(csr_A, csr_B);
    return C;
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

    for (int ii = 0; ii < A_rows; ii += BLK_SIZE) {
        for (int jj = 0; jj < B_cols; jj += BLK_SIZE) {
            for (int kk = 0; kk < A_cols; kk += BLK_SIZE) {
                // Multiply the tiles
                for (int i = ii; i < ii + BLK_SIZE && i < A_rows; i++) {
                    for (int j = jj; j < jj + BLK_SIZE && j < B_cols; j++) {
                        for (int k = kk; k < kk + BLK_SIZE && k < A_cols; k++) {
                            C[i][j] += A[i][k] * B[k][j];
                        }
                    }
                }
            }
        }
    }

    return C;
}

void *multiply_row(void *arg) {
    ThreadArgs *args = (ThreadArgs *)arg;
    int row = args->row;
    for (int j = 0; j < args->B_cols; j++) {
        args->C[row][j] = 0;
        for (int k = 0; k < args->A_cols; k++) {
            args->C[row][j] += args->A[row][k] * args->B[k][j];
        }
    }
    return NULL;
}

float **matmul_multithread(float **A, float **B, int A_rows, int A_cols, int B_rows, int B_cols) {
    if (A_cols != B_rows) {
        printf("Matrix dimensions incompatible for multiplication.\n");
        return NULL;
    }

    float **C = (float **)malloc(A_rows * sizeof(float *));
    for (int i = 0; i < A_rows; i++) {
        C[i] = (float *)aligned_alloc(CACHE_LINE_SIZE, B_cols * sizeof(float));
    }

    pthread_t *threads = (pthread_t *)malloc(A_rows * sizeof(pthread_t));
    ThreadArgs *thread_args = (ThreadArgs *)malloc(A_rows * sizeof(ThreadArgs));

    for (int i = 0; i < A_rows; i++) {
        thread_args[i] = (ThreadArgs){A, B, C, i, A_cols, B_cols};
        pthread_create(&threads[i], NULL, multiply_row, &thread_args[i]);
    }

    for (int i = 0; i < A_rows; i++) {
        pthread_join(threads[i], NULL);
    }

    free(threads);
    free(thread_args);

    return C;
}
