/*
 * timer0.h
 *
 * Created: 16/09/2024 11:27:21 am
 *  Author: SamSung
 */ 


#ifndef TIMER0_H
#define TIMER0_H

#include <stdint.h>

#define SAMPLE_NUM 40
#define ZERO_CROSSING_THRESHOLD 10  // Small threshold to detect zero-crossing

extern volatile uint8_t data_ready;  // Flag to signal main loop

void timer0_init(void);              // Function to initialize Timer0
void int0_init(void);

#endif

