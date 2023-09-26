#include "unity/unity.h"
#include "../kernel/kernel.h"
#include "test_linear.h"
#include "../utils/helpers.h"


void test_linear(void)
{
    int input_size = 3;
    int output_size = 2;

    float input_arr[] = {3, 5, 1};
    float weight_list[] = {1, 1, 2, 3, 5, 2};
    float bias_list[] = {1, 2};
    float result[] = {11, 38};

    float *p_input = &input_arr;
    float **p_weights = matrix_generator_2d(
        &weight_list,
        output_size,
        input_size
    );
    float *p_biases = &bias_list;
    float *p_correct_result = &result;

    float *calculated_res = linear(p_input, p_weights, p_biases, 3, 2);

    int compare_res = 1;
    for (int i=0; i < output_size; i++) {
        if (calculated_res[i] != p_correct_result[i]) {
            compare_res = 0;
        }
    }

    UNITY_TEST_ASSERT_EQUAL_INT(1, compare_res, __LINE__, "Expected equality");
}

// TODO more test cases