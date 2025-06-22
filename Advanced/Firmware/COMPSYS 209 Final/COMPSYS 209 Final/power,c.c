/*
 * power_c.c
 *
 * Created: 11/10/2024 11:45:13 am
 *  Author: SamSung
 */ 
#include "power.h"
#include "timer0.h"  // For access to ADC0_samples and ADC1_samples arrays

extern float ADC0_samples[SAMPLE_NUM];
extern float ADC1_samples[SAMPLE_NUM];

float calculate_real_power() {
	float power = 0.0;

	for (int i = 1; i < SAMPLE_NUM - 1; i++) {
		float V_avg = (ADC0_samples[i] + ADC0_samples[i + 1]) / 2.0;
		float I_avg = (ADC1_samples[i - 1] + ADC1_samples[i]) / 2.0;
		power += (ADC0_samples[i] * I_avg) + (V_avg * ADC1_samples[i]);
	}

	// Add boundary terms
	float V_avg_initial = (ADC0_samples[0] + ADC0_samples[1]) / 2.0;
	float I_avg_initial = (ADC1_samples[SAMPLE_NUM - 1] + ADC1_samples[0]) / 2.0;
	power += (ADC0_samples[0] * I_avg_initial) + (V_avg_initial * ADC1_samples[0]);

	float V_avg_final = (ADC0_samples[SAMPLE_NUM - 1] + ADC0_samples[0]) / 2.0;
	float I_avg_final = (ADC1_samples[SAMPLE_NUM - 2] + ADC1_samples[SAMPLE_NUM - 1]) / 2.0;
	power += (ADC0_samples[SAMPLE_NUM - 1] * I_avg_final) + (V_avg_final * ADC1_samples[SAMPLE_NUM - 1]);

	return (power / (2.0 * SAMPLE_NUM)) / 1000000;  // Normalize to watts
}
