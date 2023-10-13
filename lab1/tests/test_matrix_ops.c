#include <stdio.h>
#include <time.h>
#include <stdlib.h>
#include "unity/unity.h"
#include "../kernel/kernel.h"
#include "test_matrix_ops.h"
#include "../utils/helpers.h"

void test_matmul_square_matrices(void)
{
    // correctness
    // float matrix_7_val[] = {1, 5, 6, 3, 2, 4};
    // float **matrix_7 = matrix_generator_2d(matrix_7_val, 2, 3);

    // float matrix_8_val[] = {4, 1, 4};
    // float **matrix_8 = matrix_generator_2d(matrix_8_val, 3, 1);

    // float matrix_9_val[] = {33, 30};
    // float **matrix_9 = matrix_generator_2d(matrix_9_val, 2, 1);

    // compare_matrices(matmul_blocking(1, matrix_7, matrix_8, 2,3,3,1), matrix_9,2, 1);

    // // sm size, 
    // int sm_input_size = 10000;
    // float sm_matrix_1_val[sm_input_size];
    // for(int i = 0; i < sm_input_size; i++) {
    //     sm_matrix_1_val[i] = rand();
    // }
    // float **sm_matrix_1 = matrix_generator_2d(sm_matrix_1_val, 100, 100);

    // float sm_matrix_2_val[sm_input_size];
    // for(int i = 0; i < sm_input_size; i++) {
    //     sm_matrix_2_val[i] = rand();
    // }
    // float **sm_matrix_2 = matrix_generator_2d(sm_matrix_2_val, 100, 100);

    // md size, 
    // int md_input_size = 197136;
    // float md_matrix_1_val[md_input_size];
    // for(int i = 0; i < md_input_size; i++) {
    //     md_matrix_1_val[i] = rand();
    // }
    // float **md_matrix_1 = matrix_generator_2d(md_matrix_1_val, 444, 444);

    // float md_matrix_2_val[md_input_size];
    // for(int i = 0; i < md_input_size; i++) {
    //     md_matrix_2_val[i] = rand();
    // }
    // float **md_matrix_2 = matrix_generator_2d(md_matrix_2_val, 444, 444);

    // big size, 
    int lg_input_size = 160000;
    float lg_matrix_1_val[lg_input_size];
    for(int i = 0; i < lg_input_size; i++) {
        lg_matrix_1_val[i] = rand();
    }
    float **lg_matrix_1 = matrix_generator_2d(lg_matrix_1_val, 400, 400);

    float lg_matrix_2_val[lg_input_size];
    for(int i = 0; i < lg_input_size; i++) {
        lg_matrix_2_val[i] = rand();
    }
    float **lg_matrix_2 = matrix_generator_2d(lg_matrix_2_val, 400, 400);

    clock_t start_time;
    clock_t end_time;
    double time_taken;

    // start_time = clock();
    // matmul(lg_matrix_1, lg_matrix_2, 1000, 1000, 1000, 1000);
    // end_time = clock();

    // time_taken = ((double) end_time - start_time) / CLOCKS_PER_SEC;
    // printf("Time taken: %f seconds\n", time_taken);

    // start_time = clock();
    // matmul_blocking(40, sm_matrix_1, sm_matrix_2, 1000, 1000, 1000, 1000);
    // end_time = clock();

    // time_taken = ((double) end_time - start_time) / CLOCKS_PER_SEC;
    // printf("Time taken blocking: %f seconds\n", time_taken);

    // start_time = clock();
    // matmul_blocking(40, md_matrix_1, md_matrix_2, 444, 444, 444, 444);
    // end_time = clock();

    // time_taken = ((double) end_time - start_time) / CLOCKS_PER_SEC;
    // printf("Time taken blocking 444: %f seconds\n", time_taken);
    
    start_time = clock();
    matmul(lg_matrix_1, lg_matrix_2, 400, 400, 400, 400);
    end_time = clock();

    time_taken = ((double) end_time - start_time) / CLOCKS_PER_SEC;
    printf("matmul basic 400 %f seconds\n", time_taken);

    // for (int i = 0; i < 2; i++)
    // {
    //     free(matrix_1[i]);
    //     free(matrix_2[i]);
    //     free(matrix_3[i]);
    // }
    // free(matrix_1);
    // free(matrix_2);
    // free(matrix_3);
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
    // float **C = matmul_blocking(1, A, B, 2, 3, 2, 2);

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