#include <assert.h>
#include <stdio.h>
#include <stdlib.h>

void swap(int *i, int *j) {
    int placeholder = *i;
    *i = *j;
    *j = placeholder;
}

int partition(int *input, int start, int end) {
    // end is chosen as the pivot
    int i = start - 1;
    int j = start;

    while (j < end) {
        if (input[j] < input[end]) {
            i++;
            swap(&input[i], &input[j]);
        }
        j++;
    }
    
    // when j reaches pivot, swap input[i+1] and input[j]
    i++;
    swap(&input[i], &input[j]);

    return i;
}

void quicksort(int *input, int start, int end) {
    if (start < end) {
        int pivot_idx = partition(input, start, end);

        quicksort(input, start, pivot_idx-1);
        quicksort(input, pivot_idx+1, end);
    }
}

int *mysort(int *input, int n) {
    quicksort(input, 0, n-1);
    return input;
}

// verify() checks that the array is sorted
// DO NOT call verify() when profiling your code 
int verify(int *input, int n) {
    for (int i = 1; i < n; i++) {
        assert(input[i] >= input[i-1]);
    }
    printf("array is correctly sorted \n");
}

int main(int argc, char **argv) {
    if (argc != 3) {
        printf("Usage: ./mysort <input_size> <input_file>\n");
        return 1;
    }
    int n = atoi(argv[1]);
    int *input = (int *) malloc(sizeof(int)*n);
    int *output; // you will need to allocate memory for output if not sorting in place
    FILE *fp = fopen(argv[2], "r");
    
    for (int i = 0; i < n; i++) {
        fscanf(fp, "%d,", &input[i] );
    }

    output = mysort(input, n);

    // verify(output, n); // keep this line commented out when profiling

    free(input);
    return 0;
}