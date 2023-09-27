#include <stdlib.h>
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
        flat_img_data,
        channel_size,
        input_size,
        input_size
    );
    float ****p_kernel = matrix_generator_4d(
        flat_kernel_data,
        num_filters,
        channel_size,
        filter_size,
        filter_size
    );
    float ***p_correct_result = matrix_generator_3d(
        flat_expected_result,
        1,
        3,
        3
    );
    
    float ***computed_result = convolution(p_image_data, channel_size, p_kernel, biases, num_filters, input_size, filter_size);
    
    compare_convc_matrices(computed_result, p_correct_result, num_filters, 3, 3);

    // 32 x 32
    // run medium size
    int med_input_size = 32;
    int med_data_size = med_input_size * med_input_size * channel_size;
    float med_flat_img_data[med_data_size];
    for (int i=0; i < med_data_size; i++) {
        med_flat_img_data[i] = rand();
    }
    float ***med_img = matrix_generator_3d(
        med_flat_img_data,
        channel_size,
        med_input_size,
        med_input_size
    );

    convolution(med_img, channel_size, p_kernel, biases, num_filters, med_input_size, filter_size);


    // 64 x 64
    // run large size
    int large_input_size = 64 * channel_size;
    int large_data_size = large_input_size * large_input_size * channel_size;
    float large_flat_img_data[large_data_size];
    for (int i=0; i<large_data_size; i++) {
        large_flat_img_data[i] = rand();
    }
    float ***large_img = matrix_generator_3d(
        large_flat_img_data,
        channel_size,
        large_input_size,
        large_input_size
    );

    convolution(large_img, channel_size, p_kernel, biases, num_filters, large_input_size, filter_size);


    // free image_data
    for (int i=0; i<channel_size; i++) {
        for (int j=0; j<input_size; j++) {
            for (int k=0; k<input_size; k++) {
                free(p_image_data[i][j][k]);
            }
            free(p_image_data[i][j]);
        }
        free(p_image_data[i]);
    }
    free(p_image_data);

    // free kernel
    for (int i=0; i<num_filters; i++) {
        for (int j=0; j<channel_size; j++) {
            for (int k=0; k<filter_size; k++) {
                for (int m=0; m<filter_size; m++) {
                    free(p_kernel[i][j][k][m]);
                }
                free(p_kernel[i][j][k]);
            }
            free(p_kernel[i][j]);
        }
        free(p_kernel[i]);
    }
    free(p_kernel);

    // free results
    for (int i = 0; i < 1; i++) {
        for (int j = 0; i < 3; i++) {
            for (int k = 0; k < 3; k++) {
                free(p_correct_result[i][j][k]);
                free(computed_result[i][j][k]);
            }
            free(p_correct_result[i][j]);
            free(computed_result[i][j]);
        }
        free(p_correct_result[i]);
        free(computed_result[i]);
    }
    free(p_correct_result);
    free(computed_result);
}

