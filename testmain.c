//
// Created by nguye on 02/05/2026.
//
#include <stdio.h>
#include <math.h>
#include "waveform.h"

// Test check_compliance function
void test_check_compliance() {
    printf("\n--- Test check_compliance ---\n");

    // Test 230V (should PASS)
    if (check_compliance(230.0) == 1) {
        printf("230V: PASSED \n");
    } else {
        printf("230V: FAILED \n");
    }

    // Test 207V (lower limit, should PASS)
    if (check_compliance(207.0) == 1) {
        printf("207V: PASSED \n");
    } else {
        printf("207V: FAILED \n");
    }

    // Test 254V (over limit, should FAIL)
    if (check_compliance(254.0) == 0) {
        printf("254V: PASSED \n");
    } else {
        printf("254V: FAILED \n");
    }
}

// Test compute_rms function
void test_compute_rms() {

    WaveformSample test_data[4];

    // Test 1: All 230V on Phase A
    for(int i = 0; i < 4; i++) {
        test_data[i].phase_A_voltage = 230.0;
    }
    double rms1 = compute_rms(test_data, 4, 0);

    if (fabs(rms1 - 230.0) < 0.1) {
        printf("230V Phase A: PASSED  (%.2fV)\n", rms1);
    } else {
        printf("230V Phase A: FAILED  (%.2fV)\n", rms1);
    }

    // Test 2: 0V blackout on Phase C
    for(int i = 0; i < 4; i++) {
        test_data[i].phase_C_voltage = 0.0;
    }
    double rms2 = compute_rms(test_data, 4, 2);

    if (fabs(rms2 - 0.0) < 0.1) {
        printf("0V Phase C: PASSED  (%.2fV)\n", rms2);
    } else {
        printf("0V Phase C: FAILED  (%.2fV)\n", rms2);
    }
}

int main() {
    printf("=== STARTING TESTS ===\n");

    test_check_compliance();
    test_compute_rms();

    printf("\n=== TESTS FINISHED ===\n");
    return 0;
}