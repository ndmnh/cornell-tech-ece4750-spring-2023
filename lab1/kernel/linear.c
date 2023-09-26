#include "linear.h"

float *linear(float *input, float **weights, float *biases, int inputSize, int outputSize)
{
    // Check for empty input
    if (input == NULL || inputSize == 0 || outputSize == 0)
    {
    return NULL;
    }

    float *output = malloc(outputSize * sizeof(*output));

    float **res = matmul(weights, input, outputSize, inputSize, 1);

    for (int i = 0; i < outputSize; i++) {
        output[i] = res[i][0] + biases[i];
        free(res[i]);
    }
    free(res);

    return output;
}
