#include <stdio.h>
#include <time.h>
#include <stdlib.h>
#include "unity/unity.h"
#include "../kernel/kernel.h"
#include "test_matrix_ops.h"
#include "../utils/helpers.h"

void printMatrix(float **matrix, int rows, int cols) {
    for (int i = 0; i < rows; i++) {
        for (int j = 0; j < cols; j++) {
            printf("%f\t", matrix[i][j]);
        }
        printf("\n");
    }
}

int limited_rand() {
    int res = rand() % 100;
    if (res < 80) {
        res = 0;
    }
    return res;
}

void test_matmul_square_matrices(void)
{
    //     float matrix_7_val[] = {
    //     10, 20, 0, 0, 0, 0,
    //     0, 30, 0, 40, 0, 0,
    //     0, 0, 50, 60, 70, 0,
    //     0, 0, 0, 0, 0, 80,
    // };
    // float **matrix_7 = matrix_generator_2d(matrix_7_val, 4, 6);

    // float matrix_8_val[] = {
    //     10, 0,
    //     20, 0,
    //     0, 0,
    //     0, 20,
    //     0, 0,
    //     0, 0,
    // };
    // float **matrix_8 = matrix_generator_2d(matrix_8_val, 6, 2);

    // float matrix_9_val[] = {
    //     500, 0,
    //     600, 800,
    //     0, 1200,
    //     0, 0,
    // };
    // float **matrix_9 = matrix_generator_2d(matrix_9_val, 4, 2);
    // correctness
    // float matrix_7_val[] = {1, 5, 6, 3, 2, 4};
    // float **matrix_7 = matrix_generator_2d(matrix_7_val, 2, 3);

    // float matrix_8_val[] = {4, 1, 4};
    // float **matrix_8 = matrix_generator_2d(matrix_8_val, 3, 1);

    // float matrix_9_val[] = {33, 30};
    // float **matrix_9 = matrix_generator_2d(matrix_9_val, 2, 1);

    // float** func_res = matmul_sparse(matrix_7, matrix_8, 2,3,3,1);

    // compare_matrices(matrix_9, func_res, 2, 1);

    // big size
    int input_size = 100;
    int input_sq = input_size * input_size;
    int loop_count = 1;

    float matrix_1_val[input_sq];
    for(int i = 0; i < input_sq; i++) {
        matrix_1_val[i] = limited_rand();
    }
    float **matrix_1 = matrix_generator_2d(matrix_1_val, input_size, input_size);

    float matrix_2_val[input_sq];
    for(int i = 0; i < input_sq; i++) {
        matrix_2_val[i] = limited_rand();
    }
    float **matrix_2 = matrix_generator_2d(matrix_2_val, input_size, input_size);

    clock_t start_time;
    clock_t end_time;
    double time_taken;

    start_time = clock();
    for (int loop=0; loop<loop_count; loop++) {
        matmul_sparse(matrix_1, matrix_2, input_size, input_size, input_size, input_size);
    }
    end_time = clock();

    time_taken = ((double) end_time - start_time) / (CLOCKS_PER_SEC * loop_count);
    printf("Time taken basic: %f seconds\n", time_taken);

}

void test_matmul_incompatible_dimensions(void)
{
    // Setup
    float **A = (float **)malloc(2 * sizeof(float *));
    for (int i = 0; i < 2; i++)
    {
        A[i] = (float *)malloc(3 * sizeof(float));
    }

    float **B = (float **)malloc(2 * sizeof(float *));
    for (int i = 0; i < 2; i++)
    {
        B[i] = (float *)malloc(2 * sizeof(float));
    }

    // Run function under test
    // float **C = matmul_sparse(A, B, 2, 3, 2, 2);

    // Check expectations
    // UNITY_TEST_ASSERT_NULL(C, __LINE__, "Expected NULL!");

    // Cleanup
    for (int i = 0; i < 2; i++)
    {
        free(A[i]);
        free(B[i]);
    }
    free(A);
    free(B);
}