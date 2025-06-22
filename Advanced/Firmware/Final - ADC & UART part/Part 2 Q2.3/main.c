/*
 * Part 2 Q2.3.c
 *
 * Created: 3/09/2024 1:57:30 pm
 * Author : SamSung
 */ 
#include <avr/io.h>
#include <stdio.h>
#include <stdlib.h>
#include <math.h>
#include "adc.h"
#include "common.h"
#include "uart.h"



static volatile uint32_t ADC0_samples[SAMPLE_NUM]; // Channel ADC0 (Vvs)
static volatile	uint32_t ADC1_samples[SAMPLE_NUM]; // Channel ADC1 (Vis)
	
int main(void) {
	uart_init(9600); // Set the UART to 9600 baud rate
	adc_init(); // Initialize ADC

	float real_power = 0.0; // Real power calculation
	float RMS_voltage = 0.0;
	uint32_t Peak_Current = 0;	
	
	// Main loop for continuous sampling
	while (1) {
		// Collect samples from ADC0 (voltage) and ADC1 (current)
		for (int i = 0; i < SAMPLE_NUM; i++) {
			ADC0_samples[i] = adc_read(0);
			ADC0_samples[i] = adc_convert_mv(ADC0_samples[i]);
			_delay_us(100);
		}
		for (int i = 0; i < SAMPLE_NUM; i++) {
						ADC1_samples[i] = adc_read(1);
						ADC1_samples[i] = adc_convert_mv(ADC1_samples[i]);
			_delay_us(100);
		}

		// Power Calculation
		real_power = 0.0; // Reset real_power before calculating
		float V_avg, I_avg;
		for (int i = 0; i < SAMPLE_NUM; i++) {
			V_avg = (ADC0_samples[i] + ADC0_samples[(i + 1) % SAMPLE_NUM]) / 2.0;
			I_avg = (ADC1_samples[(i - 1 + SAMPLE_NUM) % SAMPLE_NUM] + ADC1_samples[i]) / 2.0;
			real_power += (ADC0_samples[i] * I_avg) + (V_avg * ADC1_samples[i]);
		}
		real_power = (real_power / (2.0 * SAMPLE_NUM)) / 1000000;

		// RMS Voltage Calculation
		RMS_voltage = 0.0; // Reset RMS_voltage before calculating
		RMS_voltage = calculate_RMS(ADC0_samples)/1000.0;


		// Peak Current Calculation
		Peak_Current = 0; // Reset Peak_Current before calculating
			for (uint16_t i = 0; i < SAMPLE_NUM; i++) {
				if (ADC1_samples[i] > Peak_Current) {
					Peak_Current = ADC1_samples[i];
				}
			}
		Peak_Current = Peak_Current - 2100;
		Peak_Current = Peak_Current / sqrt(2);



		

		// Extract and transmit RMS Voltage (XY.Z format)
		int RMS_whole = (int)(RMS_voltage * 10);
		char hundreds, tens, ones;
		extract_digits_from_define(RMS_whole, &hundreds, &tens, &ones);
		uart_transmit_string("RMS Voltage(v) is: ");
		uart_transmit_data(convert_to_ascii(hundreds));
		uart_transmit_data(convert_to_ascii(tens));
		uart_transmit_data('.');
		uart_transmit_data(convert_to_ascii(ones));
		uart_transmit_string("\r\n");

		// Extract and transmit Peak Current (XYZ format)
		extract_digits_from_define((int)Peak_Current, &hundreds, &tens, &ones);
		uart_transmit_string("Peak Current(mA) is: ");
		uart_transmit_data(convert_to_ascii(hundreds));
		uart_transmit_data(convert_to_ascii(tens));
		uart_transmit_data(convert_to_ascii(ones));
		uart_transmit_string("\r\n");

		// Extract and transmit Real Power (X.YZ format)
		int power_whole = (int)(real_power * 100);
		extract_digits_from_define(power_whole, &hundreds, &tens, &ones);
		uart_transmit_string("Power(w) is: ");
		uart_transmit_data(convert_to_ascii(hundreds));
		uart_transmit_data('.');
		uart_transmit_data(convert_to_ascii(tens));
		uart_transmit_data(convert_to_ascii(ones));
		uart_transmit_string("\r\n\r\n");

		_delay_ms(1000); // 1s delay. It needs to be repeating
	}
	return 0;
}


