#include <stdio.h>
#include <stdlib.h>
#include "waveform.h"
#include "io.h"

int main(int argc, char *argv[]) {
    // Check if we have filename
    if(argc < 2) {
        printf("How to use: %s <filename.csv>\n", argv[0]);
        return 1;
    }

    // Create space for 1000 data samples
    int num_samples = 1000;
    WaveformSample *sample_list = malloc(num_samples * sizeof(WaveformSample));

    // Check if memory created OK
    if(sample_list == NULL) {
        printf("Error: Not enough memory!\n");
        return 1;
    }

    printf("Created memory for %d samples.\n", num_samples);

    // TODO: Will write file reading code here later

    // Free memory (very important!)
    free(sample_list);
    printf("Freed memory. Program finished.\n");

    return 0;
}