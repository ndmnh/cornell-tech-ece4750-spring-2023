#include "linear.h"

float *linear(float *input, float **weights, float *biases, int inputSize, int outputSize)
{
    // Check for empty input
    if (input == NULL || inputSize == 0 || outputSize == 0)
    {
    return NULL;
    }

    float *output = malloc(outputSize * sizeof(*output));

    /**** YOUR CODE HERE ****/

    return output;
}
