#include "conv.h"

// Basic convolution operation
// image: 3D array: channel (RGB), row, col
// kernel: 4D array: filter idx, channel, row, col
// convOutput: 3D array: filter, row, col
float ***convolution(float ***image, int numChannels, float ****kernel, float *biasData, int numFilters, int inputSize, int kernelSize)
{
    int outputSize = inputSize - kernelSize + 1;

    // Allocate memory for the convolution output
    float ***convOutput = malloc(numFilters * sizeof(*convOutput));
    for (int i = 0; i < numFilters; i++)
    {
        convOutput[i] = malloc(outputSize * sizeof(*convOutput[i]));
        for (int j = 0; j < outputSize; j++)
        {
            convOutput[i][j] = malloc(outputSize * sizeof(*convOutput[i][j]));
        }
    }

    // Perform the convolution operation
    for (int filter_idx = 0; filter_idx < numFilters; filter_idx++) {
        for (int out_row = 0; out_row < outputSize; out_row++) {
            for (int out_col = 0; out_col < outputSize; out_col++) {
                float sum = 0;
                for (int ch = 0; ch < numChannels; ch++) {
                    for (int ker_row = 0; ker_row < kernelSize; ker_row++) {
                        for (int ker_col = 0; ker_col < kernelSize; ker_col++) {
                            int in_row = out_row + ker_row;
                            int in_col = out_col + ker_col;
                            sum += image[ch][in_row][in_col] * kernel[filter_idx][ch][ker_row][ker_col];
                        }
                    }
                }
                convOutput[filter_idx][out_row][out_col] = relu(sum + biasData[filter_idx]);
            }
        }
    }

    return convOutput;
}
