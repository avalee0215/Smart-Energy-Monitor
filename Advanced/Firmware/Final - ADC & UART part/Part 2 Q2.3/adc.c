/*
 * adc.c
 *
 * Created: 3/09/2024 2:05:44 pm
 *  Author: SamSung
 */ 

#include "common.h"
#include "adc.h"
#include <avr/io.h> // Necessary for definitions of ADMUX, ADCSRA, etc.

void adc_init(void) {

	ADMUX = (1 << REFS0); // Set reference voltage to AVCC, select ADC0 initially
	ADCSRA = (1 << ADEN) | (1 << ADATE) | (1 << ADPS2); // Enable ADC, auto trigger, prescaler = 16
	ADCSRB = (1 << ADTS1); // Set auto trigger source to Timer/Counter0 Compare Match A
	DIDR0 = 0x3F; // Buffers disable to save power
}

uint16_t adc_read(uint8_t channel)
{
	// Assign MUX[3..0] to 0 to clear channel selection
	ADMUX  &= 0xF0;

	// Set channel to input value 0~7 (0x00 ~ 0x07)
	ADMUX  |= channel;

	// Start ADC conversion
	ADCSRA |= (1 << ADSC);

	// Extract the value at ADIF bit and wait it to become 1
	while ( (ADCSRA & (1 << ADIF)) == 0 )
	{
		;
	}

	// Concatenate the conversion result into 16 bit and return
	return ( ADCL | (ADCH << 8) );
}

uint32_t adc_convert_mv(uint32_t raw_count) {
	uint16_t V_ref = 5000; // mv reference
	uint16_t ADC_resolution = 1024; // 10-bit ADC
	uint32_t dc_voltage_mv = (V_ref * raw_count) / ADC_resolution;
	return dc_voltage_mv;
}


float calculate_RMS(volatile uint32_t* voltage_readings)
{
	float voltage_to_mv = 0;
	
	
	for (uint16_t i = 0; i< SAMPLE_NUM; i++){
		if (voltage_to_mv < voltage_readings[i]){
			voltage_to_mv = voltage_readings[i];
		}
	}
	
	voltage_to_mv = (float)voltage_to_mv/sqrt(2);
	return voltage_to_mv;
}
uint32_t calculate_current(volatile uint32_t* current_readings) {
	uint32_t peak_current = 0;

	for (uint16_t i = 0; i < SAMPLE_NUM; i++) {
		if (current_readings[i] > peak_current) {
			peak_current = current_readings[i];
		}
	}
	return peak_current;
}



