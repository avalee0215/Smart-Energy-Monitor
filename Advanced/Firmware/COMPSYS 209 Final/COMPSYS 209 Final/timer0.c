/*
 * timer0.c
 *
 * Created: 16/09/2024 11:28:51 am
 *  Author: SamSung
 */ 

#include <avr/io.h>
#include <avr/interrupt.h>
#include "timer0.h"
#include "adc.h"

volatile uint8_t adc_channel = 0;            // 0 for ADC0 (voltage), 1 for ADC1 (current)
volatile uint8_t zero_crossing_detected = 0; // Flag for zero-crossing detection
volatile uint8_t sample_count = 0;           // Count of samples taken
volatile uint8_t data_ready = 0;             // Flag for main loop to process data


float ADC0_samples[SAMPLE_NUM];              // Array for voltage samples
float ADC1_samples[SAMPLE_NUM];              // Array for current samples

// Initialize Timer0 in CTC Mode with prescaler 64
void timer0_init(void) {
	TCCR0A |= (1 << WGM01);                 // Set Timer0 to CTC mode
	TCCR0B |= (1 << CS01) | (1 << CS00);    // Prescaler 64
	OCR0A = 125;                            // Compare match value (~4ms at 2 MHz F_CPU)
	TIMSK0 |= (1 << OCIE0A);                // Enable Timer0 Compare Match A interrupt
	TCNT0 = 0;                              // Reset Timer0 count
}

// Initialize INT0 for zero-crossing detection
void int0_init(void) {
	EICRA |= (1 << ISC00); // Trigger on any logical change
	EIMSK |= (1 << INT0);  // Enable external interrupt INT0
}

// ISR for Timer0 Compare Match A
