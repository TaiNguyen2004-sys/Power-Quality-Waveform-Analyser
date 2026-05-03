
 // Description: Header file for waveform.c.
 //             Defines the WaveformSample struct and declares
 //             all waveform analysis functions.
#ifndef waveform_h
#define waveform_h

typedef struct {
    double timestamp;
    double phase_A_voltage;
    double phase_B_voltage;
    double phase_C_voltage;
    double line_current;
    double frequency;
    double power_factor;
    double thd_percent;
} WaveformSample;

double compute_rms(WaveformSample* samples, int n, int phase_id);
double compute_peak_to_peak(WaveformSample* samples, int n, int phase_id);
double compute_dc_offset(WaveformSample* samples, int n, int phase_id);
int count_clipped(WaveformSample* samples, int n, int phase_id);
int check_compliance(double rms);
void compute_frequency_range(WaveformSample* samples, int n, double* min_val, double* max_val);
void compute_power_factor_range(WaveformSample* samples, int n, double* min_val, double* max_val);
void compute_thd_range(WaveformSample* samples, int n, double* min_val, double* max_val);

#endif