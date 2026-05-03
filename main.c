/*
 * Description: The entry point of the Power Quality Waveform Analyser.
 *              Handles command-line input, memory allocation,
 *              CSV data loading, calls analysis functions,
 *              and exports results to the output file.
 */

#include <stdio.h>
#include <stdlib.h>
#include "io.h"
#include "waveform.h"

#define MAX_ROWS 1000  // Sample dataset has 1000 rows

int main(int argc, char *argv[]) {
    // 1. Handle command-line argument (Project requirement)
    // Use provided filename, otherwise use default
    const char *filename = "power_quality_log.csv";
    if (argc > 1) {
        filename = argv[1];
    }
    printf("Using data file: %s\n", filename);

    // 2. Dynamic memory allocation (Pass 2 requirement)
    // Ask OS for memory to hold 1000 WaveformSample structs
    WaveformSample *samples = (WaveformSample *)malloc(MAX_ROWS * sizeof(WaveformSample));

    // Check if allocation worked
    if (samples == NULL) {
        printf("Error: Cannot allocate dynamic memory!\n");
        return 1;  // Exit with error code
    }

    // 3. Read data from CSV file
    printf("Reading file: %s\n", filename);
    int count = load_csv(filename, samples, MAX_ROWS);

    // If load_csv returns -1 (file error), clean up and exit
    if (count < 0) {
        free(samples);  // MUST free memory even if error to avoid memory leak
        printf("Failed to load data. Exiting...\n");
        return 1;
    }

    printf("Success! Loaded %d data samples.\n", count);

    // 4. Signal analysis section
    printf("Analyzing power quality and generating report...\n");

    // 5. EXPORT RESULTS TO FILE

    export_results("results.txt", samples, count);



    printf(" [SUCCESS] Report saved to: 'results.txt'\n");
    printf(" Please open the file in your project folder to view.\n");



    free(samples);
    return 0;
}