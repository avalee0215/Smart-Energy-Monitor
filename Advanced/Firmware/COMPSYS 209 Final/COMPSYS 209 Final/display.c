/*
 * display.c
 *
 * Created: 14/10/2024 2:08:29 am
 * Author: admin
 */ 
#include <avr/io.h>
#include <util/delay.h>
#include "display.h"


// Define the digit select pins and SH_ pins
#define DS1 PD4
#define DS2 PD5
#define DS3 PD6
#define DS4 PD7

// Define the shift register control pins
#define SH_CP PC3
#define SH_DS PC4
#define SH_ST PC5

const uint8_t segment_codes[] = {
    0b00111111, // 0
    0b00000110, // 1
    0b01011011, // 2
    0b01001111, // 3
    0b01100110, // 4
    0b01101101, // 5
    0b01111101, // 6
    0b00000111, // 7
    0b01111111, // 8
    0b01101111  // 9
};


// DS1 to DS4
static volatile uint8_t disp_characters[4] = {0, 0, 0, 0};
// The current digit
static volatile uint8_t disp_position = 0;

// initialize the display
void init_display(void) {
	DDRC |= (1 << SH_CP) | (1 << SH_DS) | (1 << SH_ST); // Shift register control
	DDRD |= (1 << DS1) | (1 << DS2) | (1 << DS3) | (1 << DS4); // Digit selection

	// Disable all digits initially (1)
	PORTD |= (1 << DS1) | (1 << DS2) | (1 << DS3) | (1 << DS4);
}

// Function of the shift register to shift
void shift_out(uint8_t data) {
	for (int i = 7; i >= 0; i--) {
		// Set the SH_DS pin to 0 or 1 depending on the current bit
		if (data & (1 << i)) {
			PORTC |= (1 << SH_DS);
			} else {
			PORTC &= ~(1 << SH_DS);
		}
		// Toggle
		PORTC |= (1 << SH_CP);
		PORTC &= ~(1 << SH_CP);
	}
}

// Function to separate and load the digits into the `disp_characters` array
void seperate_and_load_characters(uint16_t number, uint8_t decimal_pos) {
	// Each digit
	disp_characters[0] = segment_codes[number / 1000 % 10];
	disp_characters[1] = segment_codes[number / 100 % 10];
	disp_characters[2] = segment_codes[number / 10 % 10];
	disp_characters[3] = segment_codes[number % 10];

	// If decimal point is needed
	if (decimal_pos < 4) {
		disp_characters[decimal_pos] |= 0x80; // Add the decimal point
	}
}

// send next character to display position
void send_next_character_to_display(void) {
	// Disable all digits initially
	PORTD |= (1 << DS1) | (1 << DS2) | (1 << DS3) | (1 << DS4);
	uint8_t current_digit = disp_characters[disp_position];
	shift_out(current_digit);

	// Latch the output by toggling SH_ST
	PORTC |= (1 << SH_ST);
	PORTC &= ~(1 << SH_ST);

	// Enable the corresponding digit for multiplexing
	switch (disp_position) {
		case 0:
		PORTD &= ~(1 << DS1);
		break;
		case 1:
		PORTD &= ~(1 << DS2);
		break;
		case 2:
		PORTD &= ~(1 << DS3);
		break;
		case 3:
		PORTD &= ~(1 << DS4);
		break;
	}

	// Increment disp_position for the next cycle
	disp_position = (disp_position + 1) % 4;
}

