#include <stdlib.h>
#include "../tests/unity/unity.h"

void print_3d_array(float ***array, int depth, int numRows, int numCols) {
    for (int k=0; k < depth; k++) {
        for (int i = 0; i < numRows; i++) {
            for (int j = 0; j < numCols; j++) {
                printf("%f ", array[k][i][j]);
            }
            printf("\n");
        }
        printf("\n");
    }
}

void print_2d_array(float **array, int numRows, int numCols) {
    for (int i = 0; i < numRows; i++) {
        for (int j = 0; j < numCols; j++) {
            printf("%f ", array[i][j]);
        }
        printf("\n");
    }
}

void print_array(float *array, int size) {
    for (int j = 0; j < size; j++) {
        printf("%f ", array[j]);
    }
    printf("\n");
}

// assume no dimension mismatch
void compare_matrices(float **a, float **b, int rows, int cols) {
    for (int i = 0; i < rows; i++) {
        for (int j = 0; j < cols; j++) {
            TEST_ASSERT_FLOAT_WITHIN(1e-5, a[i][j], b[i][j]);
        }
    }
}

void compare_convc_matrices(
    float ***a,
    float ***b,
    int num_filters,
    int rows,
    int cols
) {
    for (int k = 0; k < num_filters; k++) {
        for (int i = 0; i < rows; i++) {
            for (int j = 0; j < cols; j++) {
                TEST_ASSERT_FLOAT_WITHIN(1e-5, a[k][i][j], b[k][i][j]);
            }
        }
    }
}

float **matrix_generator_2d(float *val, int row_size, int col_size) {
    int index = 0;
    float **res = (float **)malloc(row_size * sizeof(float *));
    for (int i = 0; i < row_size; i++) {
        res[i] = (float *)malloc(col_size * sizeof(float));
    }

    for(int j = 0; j < row_size; j++) {
        for(int k = 0; k < col_size; k++) {
            res[j][k] = val[index++];
        }
    }

    return res;
}

float ***matrix_generator_3d(float* val, int first_size, int second_size, int third_size) {
    int index = 0;
    float ***res = (float ***)malloc(first_size * sizeof(float **));
    for (int i = 0; i < first_size; i++) {
        res[i] = (float **)malloc(second_size * sizeof(float *));
        for (int j = 0; j < second_size; j++) {
            res[i][j] = (float *)malloc(third_size * sizeof(float));
        }
    }

    for(int q = 0; q < first_size; q++) {
        for(int k = 0; k < second_size; k++) {
            for(int m = 0; m < third_size; m++) {
                res[q][k][m] = val[index++];
            }
        }
    }

    return res;
}

float ****matrix_generator_4d(
    float* val,
    int first_size,
    int second_size,
    int third_size,
    int fourth_size
    )
{
    int index = 0;
    float ****res = (float ****)malloc(first_size * sizeof(res));
    for (int i = 0; i < first_size; i++) {
        res[i] = (float ***)malloc(second_size * sizeof(float **));
        for (int j = 0; j < second_size; j++) {
            res[i][j] = (float **)malloc(third_size * sizeof(float *));
            for (int k = 0; k < third_size; k++) {
                res[i][j][k] = (float *)malloc(fourth_size * sizeof(float));
            }
        }
    }

    for (int q = 0; q < first_size; q++) {
        for (int p = 0; p < second_size; p++) {
            for (int m = 0; m < third_size; m++) {
                for (int n = 0; n < fourth_size; n++) {
                    res[q][p][m][n] = val[index++];
                }
            }
        }
    }

    return res;
}