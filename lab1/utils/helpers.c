// assume no dimension mismatch
int compare_matrices(float **a, float **b, int rows, int cols) {
    for (int i = 0; i < rows; i++) {
        for (int j = 0; j < cols; j++) {
            if (a[i][j] != b[i][j]) {
                return 0;
            }
        }
    }
    return 1;
}

float **matrix_generator_2d(float *val, int row_size, int col_size) {
    float **res = (float **)malloc(row_size * sizeof(float *));
    for (int i = 0; i < row_size; i++) {
        res[i] = (float *)malloc(col_size * sizeof(float));
    }

    for(int j = 0; j < row_size; j++) {
        for(int k = 0; k < col_size; k++) {
            res[j][k] = val[j * row_size + k];
        }
    }

    return res;
}

float ***matrix_generator_3d(float* val, int first_size, int second_size, int third_size) {
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
                res[q][k][m] = val[q * first_size + k * second_size + k];
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
    float ****res = (float ****)malloc(first_size * sizeof(res));
    for (int i = 0; i < first_size; i++) {
        res[i] = (float ***)malloc(second_size * sizeof(float **));
        for (int j = 0; j < second_size; j++) {
            res[i][j] = (float **)malloc(third_size * sizeof(float *));
            for (int k = 0; k < third_size; k++) {
                res[i][j][k] = (float *)malloc(third_size * sizeof(float));
            }
        }
    }

    for (int q = 0; q < first_size; q++) {
        for (int p = 0; p < second_size; p++) {
            for (int m = 0; m < third_size; m++) {
                for (int n = 0; n < fourth_size; n++) {
                    res[q][p][m][n] = val[q * first_size + p * second_size + m * third_size + n];
                }
            }
        }
    }

    return res;
}