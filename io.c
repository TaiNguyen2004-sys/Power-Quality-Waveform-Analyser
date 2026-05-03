//
// Created by nguye on 26/04/2026.
 // Description: Manages file input and output operations.
 //             Loads waveform samples from CSV into memory
 //             and exports final analysis results to results.txt.


#include "io.h"
#include <stdio.h>
#include <stdlib.h>
#include "waveform.h"

// Function to read data from CSV file into array of structs
int load_csv(const char *filename, WaveformSample *samples, int max_count) {
    // 1. Open file in read mode ("r")
    FILE *file = fopen(filename, "r");

    // PROJECT REQUIREMENT: Handle error gracefully if file doesn't exist
    if (file == NULL) {
        printf("Error: Cannot open file '%s'. Please check filename or path!\n", filename);
        return -1; // Return -1 to tell main() there was an error
    }

    // 2. Read and skip header line (first line with column names)
    char buffer[256]; // Temporary buffer to store each line
    if (fgets(buffer, sizeof(buffer), file) == NULL) {
        printf("Error: File '%s' is empty or header cannot be read.\n", filename);
        fclose(file);
        return -1;
    }

    // 3. Read data line by line
    int count = 0;
    // Loop until end of file or reach max_count
    while (count < max_count && fgets(buffer, sizeof(buffer), file) != NULL) {
        // Use sscanf to parse 8 columns (%lf for double type)
        int parsed = sscanf(buffer, "%lf,%lf,%lf,%lf,%lf,%lf,%lf,%lf",
                            &samples[count].timestamp,
                            &samples[count].phase_A_voltage,
                            &samples[count].phase_B_voltage,
                            &samples[count].phase_C_voltage,
                            &samples[count].line_current,
                            &samples[count].frequency,
                            &samples[count].power_factor,
                            &samples[count].thd_percent);

        // Check if current line has exactly 8 columns
        if (parsed == 8) {
            count++; // Increment counter if parsing successful
        } else {
            printf("Warning: Line %d in file has wrong format and was skipped.\n", count + 2);
        }
    }

    // 4. Close file and return number of successfully read lines
    fclose(file);
    return count;
}
// Function to save analysis results to a text file
void export_results(const char *filename, WaveformSample *samples, int sample_count) {
    FILE *output_file = fopen(filename, "w");
    if (output_file == NULL) {
        printf("ERROR: Could not create file '%s'\n", filename);
        printf("Make sure you have write permission in this folder!\n");
        return;
    }
    char phase_names[3] = {'A', 'B', 'C'};

    for (int phase_id = 0; phase_id < 3; phase_id++) {
        double rms = compute_rms(samples, sample_count, phase_id);
        double ptp = compute_peak_to_peak(samples, sample_count, phase_id);
        double dc = compute_dc_offset(samples, sample_count, phase_id);
        int clipped = count_clipped(samples, sample_count, phase_id);
        int pass = check_compliance(rms);

        fprintf(output_file, "=== PHASE %c RESULTS ===\n", phase_names[phase_id]);
        fprintf(output_file, "RMS Voltage: %.2f V -> %s (207-253V range)\n", rms, pass ? "PASS" : "FAIL");
        fprintf(output_file, "Peak-to-Peak: %.2f V\n", ptp);
        fprintf(output_file, "DC Offset: %.3f V\n", dc);
        fprintf(output_file, "Clipped Samples: %d out of %d\n", clipped, sample_count);
    }

    // Print overall system metrics
    double min_freq, max_freq;
    double min_pf, max_pf;
    double min_thd, max_thd;

    compute_frequency_range(samples, sample_count, &min_freq, &max_freq);
    compute_power_factor_range(samples, sample_count, &min_pf, &max_pf);
    compute_thd_range(samples, sample_count, &min_thd, &max_thd);

    fprintf(output_file, "=== OVERALL SYSTEM METRICS ===\n");
    fprintf(output_file, "Frequency range: %.3f Hz to %.3f Hz over the 200 ms window\n", min_freq, max_freq);
    fprintf(output_file, "Power factor range: %.3f to %.3f\n", min_pf, max_pf);
    fprintf(output_file, "THD range: %.2f%% to %.2f%%\n", min_thd, max_thd);

    // Close file and done
    fclose(output_file);
    printf("Successfully exported results to %s\n", filename);

    // Step 2: Analyze all 3 phases (A, B, C)
    for (int phase = 0; phase < 3; phase++) {
        // Calculate all measurements for this phase
        double rms_voltage = compute_rms(samples, sample_count, phase);
        double peak_to_peak = compute_peak_to_peak(samples, sample_count, phase);
        double dc_offset = compute_dc_offset(samples, sample_count, phase);
        int clipped_samples = count_clipped(samples, sample_count, phase);
        int is_compliant = check_compliance(rms_voltage);

        // Convert phase number to letter (0=A, 1=B, 2=C)
        char phase_letter = 'A' + phase;

        // Step 3: Write results for this phase
        fprintf(output_file, "=== PHASE %c RESULTS ===\n", phase_letter);

        // Show compliance status
        if (is_compliant) {
            fprintf(output_file, "RMS Voltage: %.2f V  -> PASS (207-253V range)\n", rms_voltage);
        } else {
            fprintf(output_file, "RMS Voltage: %.2f V  -> FAIL!\n", rms_voltage);
        }

        fprintf(output_file, "Peak-to-Peak: %.2f V\n", peak_to_peak);
        fprintf(output_file, "DC Offset: %.3f V\n", dc_offset);
        fprintf(output_file, "Clipped Samples: %d out of %d (%.1f%%)\n",
                clipped_samples, sample_count,
                (double)clipped_samples/sample_count*100);
        fprintf(output_file, "----------------------------------------\n\n");
    }

    // Step 4: Close the file (IMPORTANT!)
    fclose(output_file);

    // Tell user it worked
    printf("\n SUCCESS! Report saved to: '%s'\n", filename);
    printf("Check the file to see your analysis results!\n\n");
}