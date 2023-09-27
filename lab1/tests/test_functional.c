#include "unity/unity.h"
#include "../kernel/kernel.h"
#include "test_functional.h"
#include <float.h>


void test_softmax(void) {
    float input[] = {1.0, 2.0, 3.0};
    float *output = softmax(input, 3);
    float sum = 0.0;

    // Check that the sum of the output is 0 (because the output is log softmax)
    for (int i = 0; i < 3; i++) {
        sum += output[i];
    }

    TEST_ASSERT_FLOAT_WITHIN(1e-6, 1.0, sum);

    // Check that the maximum input corresponds to the maximum output
    int maxInputIndex = 0;
    int maxOutputIndex = 0;

    for (int i = 1; i < 3; i++) {
        if (input[i] > input[maxInputIndex]) {
            maxInputIndex = i;
        }
        if (output[i] > output[maxOutputIndex]) {
            maxOutputIndex = i;
        }
    }

    // TEST_ASSERT_EQUAL_INT(maxInputIndex, maxOutputIndex);

    int md_input_size = 100;
    float md_input[md_input_size];
    for (int i=0; i<md_input_size; i++) {
        md_input[i] = rand();
    }
    softmax(md_input, 3);

    int lg_input_size = 1000;
    float lg_input[lg_input_size];
    for (int i=0; i<lg_input_size; i++) {
        lg_input[i] = rand();
    }
    softmax(lg_input, 3);

    // Cleanup
    free(output);
}

void test_relu(void) {
    float inputs[] = {3.0f, 0.0f, -3.0f};
    float expected_outputs[] = {3.0f, 0.0f, 0.0f};
    int test_cases = sizeof(inputs)/sizeof(inputs[0]);

    for(int i = 0; i < test_cases; i++) {
        float output = relu(inputs[i]);
        TEST_ASSERT_FLOAT_WITHIN(1e-6, expected_outputs[i], output);
    }

    int md_input_size = 100;
    for(int i = 0; i < md_input_size; i++) {
        relu(rand());
    }

    int lg_input_size = 1000;
    for(int i = 0; i < lg_input_size; i++) {
        relu(rand());
    }
}


// Add more test cases as needed