#include <stdlib.h>
#include "matrix_ops.h"

typedef struct {
    float *nz_values;
    int *row_indices;
    int *column_indices;
    int nz_count;
    int rows;
    int cols;
} CSRMatrix;


// make CSR matrix from (sparse) matrix
CSRMatrix* matrix_to_csr(float **matrix, int rows, int cols) {
    int nz_count = 0;
    for(int i = 0; i < rows; i++) {
        for(int j = 0; j < cols; j++) {
            if(matrix[i][j] != 0.0) {
                nz_count++;
            }
        }
    }

    int *row_indices = (int *)malloc((rows + 1) * sizeof(int));
    float *nz_values = (float *)malloc(nz_count * sizeof(float));
    int *column_indices = (int *)malloc(nz_count * sizeof(int));

    int k = 0;
    for(int i = 0; i < rows; i++) {
        row_indices[i] = k;
        for(int j = 0; j < cols; j++) {
            if(matrix[i][j] != 0.0) {
                nz_values[k] = matrix[i][j];
                column_indices[k] = j;
                k++;
            }
        }
    }
    row_indices[rows] = k;

    CSRMatrix *csr = (CSRMatrix *)malloc(sizeof(CSRMatrix));
    csr->row_indices = row_indices;
    csr->column_indices = column_indices;
    csr->nz_values = nz_values;
    csr->rows = rows;
    csr->cols = cols;
    csr->nz_values = nz_values;

    return csr;
}

float** csr_to_matrix(CSRMatrix* csr, int rows, int cols) {
    int* row_indices = csr->row_indices;
    int* column_indices = csr->column_indices;
    int* nz_values = csr->nz_values;

    float **matrix = (float **)malloc(rows * sizeof(float *));
    for (int i = 0; i < rows; i++) {
        matrix[i] = (float *)calloc(cols, sizeof(float));
    }

    for (int i = 0; i < rows; i++) {
        for (int j = row_indices[i]; j < row_indices[i + 1]; j++) {
            int col = column_indices[j];
            matrix[i][col] = nz_values[j];
        }
    }

    return matrix;
}

CSRMatrix* matmul_csr(CSRMatrix *A, CSRMatrix *B) {
    if (A->cols != B->rows) {
        printf("Matrix dimensions incompatible for multiplication.\n");
        return NULL;
    }

    // heuristic
    int *C_row_indices = (int *)calloc((A->rows + 1), sizeof(int));
    int estimated_nz_count = A->nz_count * B->nz_count / (A->rows * B->cols);

    int *C_column_indices = (int *)malloc(estimated_nz_count * sizeof(int));
    float *C_values = (float *)malloc(estimated_nz_count * sizeof(float));

    int nz_count_count = 0;
    for (int i = 0; i < A->rows; i++) {
        for (int j = A->row_indices[i]; j < A->row_indices[i + 1]; j++) {
            int row_A = i;
            int col_A = A->column_indices[j];
            float val_A = A->nz_values[j];

            for (int k = B->row_indices[col_A]; k < B->row_indices[col_A + 1]; k++) {
                int col_B = B->column_indices[k];
                float val_B = B->nz_values[k];
                float multiplied_value = val_A * val_B;

                // reallocate if needed
                if (nz_count_count >= estimated_nz_count) {
                    estimated_nz_count *= 2;
                    C_column_indices = (int *)realloc(C_column_indices, estimated_nz_count * sizeof(int));
                    C_values = (float *)realloc(C_values, estimated_nz_count * sizeof(float));
                }

                C_values[nz_count_count] = multiplied_value;
                C_column_indices[nz_count_count] = col_B;
                nz_count_count++;
            }
        }
        C_row_indices[i + 1] = nz_count_count;
    }

    CSRMatrix *C = (CSRMatrix *)malloc(sizeof(CSRMatrix));
    C->row_indices = C_row_indices;
    C->column_indices = C_column_indices;
    C->nz_values = C_values;
    C->rows = A->rows;
    C->cols = B->cols;
    C->nz_count = nz_count_count;

    return C;
}



float **matmul_sparse(float **A, float **B, int A_rows, int A_cols, int B_rows, int B_cols) {
    float **result;
    /**** 1. Create CSR format of input matrix ****/
    // When profiling, only loop over part 2.
    CSRMatrix* csr_A = matrix_to_csr(A, A_rows, A_cols);
    CSRMatrix* csr_B = matrix_to_csr(B, B_rows, B_cols);

    /**** 2. Perform matrix multiplication on CSR format of input
    matrix ****/
    CSRMatrix* csr_C = matmul_csr(csr_A, csr_B);
    float **C = csr_to_matrix(csr_C, A_rows, B_cols);
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