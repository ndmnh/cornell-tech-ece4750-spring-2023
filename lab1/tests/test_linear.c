#include <stdlib.h>
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

    float **p_weights = matrix_generator_2d(
        weight_list,
        output_size,
        input_size
    );
    float *p_correct_result = result;

    float *calculated_res = linear(input_arr, p_weights, bias_list, input_size, output_size);

    for (int i=0; i < output_size; i++) {
        if (calculated_res[i] != p_correct_result[i]) {
            TEST_ASSERT_FLOAT_WITHIN(1e-6, calculated_res[i], p_correct_result[i]);
        }
    }

    // medium
    int med_input_size = 32;
    float med_input_arr[med_input_size];
    for(int i = 0; i < med_input_size; i++) {
        med_input_arr[i] = rand();
    }
    float med_weight_list[med_input_size * 2];
    for(int i = 0; i < med_input_size; i++) {
        med_weight_list[i] = rand();
    }
    float med_bias_list[output_size];
    for(int i = 0; i < output_size; i++) {
        med_bias_list[i] = rand();
    }
    float **med_weights = matrix_generator_2d(
        med_weight_list,
        output_size,
        med_input_size
    );

    linear(med_input_arr, med_weights, med_bias_list, med_input_size, output_size);

    // large
    int lg_input_size = 1024;
    float lg_input_arr[lg_input_size];
    for(int i = 0; i < lg_input_size; i++) {
        lg_input_arr[i] = rand();
    }
    float lg_weight_list[lg_input_size * 2];
    for(int i = 0; i < lg_input_size; i++) {
        lg_weight_list[i] = rand();
    }
    float lg_bias_list[output_size];
    for(int i = 0; i < output_size; i++) {
        lg_bias_list[i] = rand();
    }
    float **lg_weights = matrix_generator_2d(
        lg_weight_list,
        output_size,
        lg_input_size
    );

    linear(lg_input_arr, lg_weights, lg_bias_list, lg_input_size, output_size);

}
