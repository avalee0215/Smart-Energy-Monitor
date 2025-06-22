/*
 * adc.c
 *
 * Created: 3/09/2024 2:05:44 pm
 *  Author: SamSung
 */ 

#include "common.h"
#include "adc.h"
#include <avr/io.h> // Necessary for definitions of ADMUX, ADCSRA, etc.

//initialisation
void adc_init(void) {
	ADMUX = (1 << REFS0); // Set reference voltage to AVCC, select ADC0 initially
	ADCSRA = (1 << ADEN) | (1 << ADATE) | (1 << ADPS2); // Enable ADC, auto trigger, prescaler = 16
	ADCSRB = (1 << ADTS1); // Set auto trigger source to Timer/Counter0 Compare Match A
	DIDR0 = 0x3F; // Buffers disable to save power
}

uint16_t adc_read(uint8_t chan) {
	// Set the ADC channel, keeping other bits of ADMUX unchanged
	ADMUX = (ADMUX & 0xF0) | (chan & 0x0F);
	// Start the ADC conversion
	ADCSRA |= (1 << ADSC);
	// Wait for the conversion to complete (polling)
	while (!(ADCSRA & (1 << ADIF)));
	// Clear the ADIF by writing a 1 (this is done by writing a 1 to it)
	ADCSRA |= (1 << ADIF);
	// Read and return the ADC value (combine ADCL and ADCH)
	return (ADCL | (ADCH << 8));
}

uint32_t adc_convert_mv(uint32_t raw_count) {
	uint16_t V_ref = 5000; // mv
	uint16_t ADC_resolution = 1024;
	uint32_t dc_voltage_mv = 0;
	dc_voltage_mv = (V_ref * raw_count) / ADC_resolution;
	return dc_voltage_mv;
}