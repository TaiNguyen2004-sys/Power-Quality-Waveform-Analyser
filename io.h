//
// Created by nguye on 25/04/2026.
//Description: Header file for io.c.
 //           Declares file I/O functions for loading and exporting data.

#ifndef power_quality_waveform_analyser_IO_h
#define power_quality_waveform_analyser_IO_h
#include "waveform.h"


int load_csv(const char *filename, WaveformSample *samples, int max_count);


void export_results(const char *filename, WaveformSample *samples, int count);
#endif
