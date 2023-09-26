#include "unity/unity.h"
#include "../kernel/kernel.h"
#include "../utils/data_utils.h"
#include "test_conv.h"
#include "../utils/helpers.h"

void test_conv(void)
{
    // 3 channels
    int channel_size = 3;
    int input_size = 4;
    int filter_size = 2;
    int num_filters = 1;
    int output_size = input_size - filter_size + 1;
    
    // float image_data[][][] = {
    //     {
    //         {0, 1, 2, 3},
    //         {4, 5, 6, 7},
    //         {8, 9, 10, 11},
    //         {12, 13, 14, 15},
    //     },
    //     {
    //         {2, 4, 6, 8},
    //         {10, 12, 3, 2},
    //         {8, 2, 1, 1},
    //         {3, 4, 5, 1},
    //     },
    //     {
    //         {1, 4, 6, 8},
    //         {12, 13, 14, 15},
    //         {8, 9, 10, 11},
    //         {4, 5, 6, 7},
    //     },
    // };

    // float kernel[][][][] = {
    //     {
    //         {
    //             {1, 1},
    //             {1, 1}
    //         },
    //         {
    //             {1, 0},
    //             {0, 1}
    //         },
    //         {
    //             {1, 1},
    //             {1, 0}
    //         },
    //     }
    // };

    float biases[] = {2};

    // float expected_result[][][] = {
    //     {
    //         {43, 46, 56},
    //         {73, 81, 79},
    //         {77, 79, 81},
    //     },
    // };
    float flat_img_data[] = {
            0, 1, 2, 3, 4, 5, 6, 7, 8, 9, 10, 11, 12, 13, 14, 15,
            2, 4, 6, 8, 10, 12, 3, 2, 8, 2, 1, 1, 3, 4, 5, 1,
            1, 4, 6, 8, 12, 13, 14, 15, 8, 9, 10, 11, 4, 5, 6, 7
        };
    float flat_kernel_data[] = {
        1,1,1,1,1,0,0,1,1,1,1,0
    };
    float flat_expected_result[] = {
        43, 46, 56, 73, 81, 79, 77, 79, 81
    };
    

    float ***p_image_data = matrix_generator_3d(
        &flat_img_data,
        channel_size,
        input_size,
        input_size
    );
    float ****p_kernel = matrix_generator_4d(
        &flat_kernel_data,
        num_filters,
        channel_size,
        filter_size,
        filter_size
    );
    float *p_biases = &biases;
    float ***p_correct_result = matrix_generator_3d(
        &flat_expected_result,
        1,
        3,
        3
    );
    // TODO more cases
}

