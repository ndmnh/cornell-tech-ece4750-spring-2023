#include "linear.h"

float *linear(float *input, float **weights, float *biases, int inputSize, int outputSize)
{
    // Check for empty input
    if (input == NULL || inputSize == 0 || outputSize == 0)
    {
    return NULL;
    }

    float *output = malloc(outputSize * sizeof(*output));

    for (int i = 0; i < outputSize; i++) {
        float val = 0;
        for (int j=0; j < inputSize; j++) {
            val += weights[i][j] * input[j];
        }
        output[i] = val + biases[i];
    }

    return output;
}
