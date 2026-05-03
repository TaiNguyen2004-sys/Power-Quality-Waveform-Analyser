//
// Created by nguye on 25/04/2026.
// Description: Contains mathematical analysis functions such as
//              RMS, peak-to-peak, DC offset, clipping detection,
//              and compliance checking for all phases.

#include "waveform.h"
#include <math.h>    // for sqrt() and fabs()
#include <stdio.h>

// Helper function to get voltage by phase (internal use only)
double get_voltage_by_phase(WaveformSample sample, int phase_id) {
    if (phase_id == 0) return sample.phase_A_voltage;
    else if (phase_id == 1) return sample.phase_B_voltage;
    else if (phase_id == 2) return sample.phase_C_voltage;
    else return 0.0;  // error case
}

// 1. Calculate RMS voltage
double compute_rms(WaveformSample* samples, int n, int phase_id) {
    double sum_squares = 0.0;

    for (int i = 0; i < n; i++) {
        double voltage = get_voltage_by_phase(samples[i], phase_id);
        sum_squares += voltage * voltage;  // v^2
    }

    // RMS = sqrt(average of squares)
    return sqrt(sum_squares / n);
}

// 2. Calculate Peak-to-Peak voltage (Vmax - Vmin)
double compute_peak_to_peak(WaveformSample* samples, int n, int phase_id) {
    double max_voltage = -999999.0;  // start with very small number
    double min_voltage = 999999.0;   // start with very big number

    for (int i = 0; i < n; i++) {
        double voltage = get_voltage_by_phase(samples[i], phase_id);

        if (voltage > max_voltage) {
            max_voltage = voltage;
        }
        if (voltage < min_voltage) {
            min_voltage = voltage;
        }
    }

    return max_voltage - min_voltage;
}

// 3. Calculate DC Offset (average voltage)
double compute_dc_offset(WaveformSample* samples, int n, int phase_id) {
    double total = 0.0;

    for (int i = 0; i < n; i++) {
        double voltage = get_voltage_by_phase(samples[i], phase_id);
        total += voltage;
    }

    return total / n;  // average
}

// 4. Count clipped samples (over 324.9V limit)
int count_clipped(WaveformSample* samples, int n, int phase_id) {
    int clipped_count = 0;
    double clip_limit = 324.9;  // clipping threshold

    for (int i = 0; i < n; i++) {
        double voltage = get_voltage_by_phase(samples[i], phase_id);

        // Check if absolute value exceeds limit
        if (fabs(voltage) >= clip_limit) {
            clipped_count++;
        }
    }

    return clipped_count;
}

// 5. Check if voltage is within compliance range (207V - 253V)
int check_compliance(double rms_voltage) {
    // Returns 1 if compliant, 0 if not
    if (rms_voltage >= 207.0 && rms_voltage <= 253.0) {
        return 1;  // PASS
    }
    return 0;  // FAIL
}
    // 6. Find min/max frequency
    void compute_frequency_range(WaveformSample* samples, int n, double* min_val, double* max_val) {
        *min_val = samples[0].frequency;
        *max_val = samples[0].frequency;

        for (int i = 0; i < n; i++) {
            if (samples[i].frequency < *min_val) {
                *min_val = samples[i].frequency;
            }
            if (samples[i].frequency > *max_val) {
                *max_val = samples[i].frequency;
            }
        }
    }

    // 7. Find min/max power factor
    void compute_power_factor_range(WaveformSample* samples, int n, double* min_val, double* max_val) {
        *min_val = samples[0].power_factor;
        *max_val = samples[0].power_factor;

        for (int i = 0; i < n; i++) {
            if (samples[i].power_factor < *min_val) {
                *min_val = samples[i].power_factor;
            }
            if (samples[i].power_factor > *max_val) {
                *max_val = samples[i].power_factor;
            }
        }
    }

    // 8. Find min/max THD
    void compute_thd_range(WaveformSample* samples, int n, double* min_val, double* max_val) {
        *min_val = samples[0].thd_percent;
        *max_val = samples[0].thd_percent;

        for (int i = 0; i < n; i++) {
            if (samples[i].thd_percent < *min_val) {
                *min_val = samples[i].thd_percent;
            }
            if (samples[i].thd_percent > *max_val) {
                *max_val = samples[i].thd_percent;
            }
        }
    }