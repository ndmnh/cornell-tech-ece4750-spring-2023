#ifndef HELPERS_H
#define HELPERS_H

int compare_matrices(float **a, float **b, int rows, int cols);
float **matrix_generator_2d(float *val, int row_size, int col_size);
float ***matrix_generator_3d(float *val, int first_size, int second_size, int third_size);
float ****matrix_generator_4d(
    float* val,
    int first_size,
    int second_size,
    int third_size,
    int fourth_size
);

#endif // HELPERS_H