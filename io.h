//
// Created by nguye on 25/04/2026.
//

#ifndef POWER_QUALITY_WAVEFORM_ANALYSER_IO_H
#define POWER_QUALITY_WAVEFORM_ANALYSER_IO_H
#include "waveform.h"

// Hàm đọc dữ liệu từ file CSV vào mảng struct
// Trả về số lượng dòng đã đọc được thực tế
int load_csv(const char *filename, WaveformSample *samples, int max_count);

// Hàm ghi kết quả phân tích ra file results.txt
void export_results(const char *filename, WaveformSample *samples, int count);
#endif //POWER_QUALITY_WAVEFORM_ANALYSER_IO_H
