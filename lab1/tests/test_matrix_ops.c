#include <stdlib.h>
#include "unity/unity.h"
#include "../kernel/kernel.h"
#include "test_matrix_ops.h"
#include "../utils/helpers.h"

void test_matmul_square_matrices(void)
{
    // test multiplication 2x2 matrix and 2x2 matrix
    float matrix_1_val[] = {1, 2, 3, 4};
    float **matrix_1 = matrix_generator_2d(matrix_1_val, 2, 2);

    float matrix_2_val[] = {5,6,7,8};
    float **matrix_2 = matrix_generator_2d(matrix_2_val, 2, 2);

    float matrix_3_val[] = {19, 22, 43, 50};
    float **matrix_3 = matrix_generator_2d(matrix_3_val, 2, 2);

    compare_matrices(matmul(matrix_1, matrix_2, 2, 2, 2, 2), matrix_3, 2, 2);

    // 5 x 5
    float matrix_4_val[] = {4,6,4,3,5,5,9,6,6,8,6,10,4,1,8,7,9,7,3,4,7,2,2,10,2};
    float **matrix_4 = matrix_generator_2d(matrix_4_val, 5, 5);

    float matrix_5_val[] = {3,10,1,10,4,4,7,4,10,4,10,2,1,4,9,7,6,5,10,3,7,10,10,5,5};
    float **matrix_5 = matrix_generator_2d(matrix_5_val, 5, 5);

    float matrix_6_val[] = {132, 158, 97, 171, 110, 209, 241, 157, 264, 168, 161, 224, 135, 226, 143, 176, 205, 105, 238, 156, 133, 168, 87, 208, 94};
    float **matrix_6 = matrix_generator_2d(matrix_6_val, 5, 5);

    compare_matrices(matmul(matrix_4, matrix_5, 5,5,5,5), matrix_6, 5, 5);

    // different dimensions
    float matrix_7_val[] = {1, 5, 6, 3, 2, 4};
    float **matrix_7 = matrix_generator_2d(matrix_7_val, 2, 3);

    float matrix_8_val[] = {4, 1, 4};
    float **matrix_8 = matrix_generator_2d(matrix_8_val, 3, 1);

    float matrix_9_val[] = {33, 30};
    float **matrix_9 = matrix_generator_2d(matrix_9_val, 2, 1);

    compare_matrices(matmul(matrix_7, matrix_8, 2,3,3,1), matrix_9,2, 1);

    // big size, 4 * 32
    int lg_input_size = 128;
    float lg_matrix_1_val[lg_input_size];
    for(int i = 0; i < lg_input_size; i++) {
        lg_matrix_1_val[i] = rand();
    }
    float **lg_matrix_1 = matrix_generator_2d(lg_matrix_1_val, 4, 32);

    float lg_matrix_2_val[lg_input_size];
    for(int i = 0; i < lg_input_size; i++) {
        lg_matrix_2_val[i] = rand();
    }
    float **lg_matrix_2 = matrix_generator_2d(lg_matrix_2_val, 32, 4);

    matmul(lg_matrix_1, lg_matrix_2, 4, 32, 32, 4);

    for (int i = 0; i < 2; i++)
    {
        free(matrix_1[i]);
        free(matrix_2[i]);
        free(matrix_3[i]);
    }
    free(matrix_1);
    free(matrix_2);
    free(matrix_3);
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
    float **C = matmul(A, B, 2, 3, 2, 2);

    // Check expectations
    UNITY_TEST_ASSERT_NULL(C, __LINE__, "Expected NULL!");

    // Cleanup
    for (int i = 0; i < 2; i++)
    {
        free(A[i]);
        free(B[i]);
    }
    free(A);
    free(B);
}