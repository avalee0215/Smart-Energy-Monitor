/*
 * timer1.c
 *
 * Created: 13/10/2024 12:30:38 am
 *  Author: SamSung
 */ 
// timer1.c
#include <avr/io.h>
#include <avr/interrupt.h>
#include "timer1.h"

volatile uint16_t time_stamp1 = 0;
volatile uint16_t half_period1 = 0;
volatile uint16_t full_period1 = 0;
volatile uint8_t period_count1 = 0;


// Initialize Timer1 for zero-crossing detection and period measurement
void timer1_init(void) {
	TCCR1B &= ~(1 << ICES1); // Input Capture on falling edge
	TCCR1B |= (1 << CS11);   // Prescaler = 8
	TIMSK1 |= (1 << ICIE1);  // Enable input capture interrupt
	TCNT1 = 0;               // Start Timer1 with a counter value of 0
}

