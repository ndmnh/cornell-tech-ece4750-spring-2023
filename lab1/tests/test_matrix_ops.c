#include "unity/unity.h"
#include "../kernel/kernel.h"
#include "test_matrix_ops.h"
#include "../utils/helpers.h"

void test_matmul_square_matrices(void)
{
    // test multiplication 2x2 matrix and 2x2 matrix
    float matrix_1_val[2][2] = {{1, 2}, {3, 4}};
    float **matrix_1 = matrix_generator_2d(matrix_1_val, 2, 2);

    float matrix_2_val[2][2] = {{5, 6},{7, 8}};
    float **matrix_2 = matrix_generator_2d(matrix_2_val, 2, 2);

    float matrix_3_val[2][2] = {{19, 22}, {43, 50}};
    float **matrix_3 = matrix_generator_2d(matrix_2_val, 2, 2);

    int compare_res = compare_matrices(matmul(matrix_1, matrix_2, 2, 2, 2, 2), matrix_3, 2, 2);

    UNITY_TEST_ASSERT_EQUAL_INT(1, compare_res, __LINE__, "Expected equality");

    // TODO: more tests
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