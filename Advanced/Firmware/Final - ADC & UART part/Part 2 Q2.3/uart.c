/* uart.c
*
* Created: 20/08/2024 3:36:48 pm
*  Author: Group 14
*/
#define F_CPU 2000000UL  // Define system clock frequency

#include "uart.h"
#include <avr/io.h> // access to low level control

void uart_init(uint32_t baud_rate) {
uint16_t ubrr = (F_CPU / (16UL * baud_rate)) - 1; // ubrr = 2000000/(16*9600) - 1
//UBRR is divided into two 8-bit registers because the total size of the register is 16 bits
UBRR0L = (uint8_t)ubrr;
UBRR0H = (uint8_t)(ubrr >> 8);

UCSR0B = (1 << TXEN0); // enable transmitter. UCSR0B = 0b00001000
UCSR0C = (1 << UCSZ01) | (1 << UCSZ00);  // 8 data bits, 1 stop bit, no parity. UCSR0C = 0b00000110
}

void extract_digits_from_define(int value, char* hundreds, char* tens, char* ones) {
*hundreds = value / 100;
*tens = (value / 10) % 10;
*ones = value % 10;
}

char convert_to_ascii(char digit) {
	if (digit >= 0 && digit <= 9) {
		return digit + '0'; // digit + 48
		} else {
		return '?'; // Return '?' for invalid digits to help identify errors
	}
}


// Function to transmit a single byte of data
void uart_transmit_data(char data) {
while (!(UCSR0A & (1 << UDRE0)));
// waits until the UART data register is ready to accept new data and transmit
UDR0 = data;
}

//pointer to a constant character array (string)
void uart_transmit_string(const char* str) {
while (*str) {
//each character in the string is transmit
uart_transmit_data(*str++);
}
}


float format_XY_Z(float voltage) {
	int xy = (int)voltage / 10;
	int z = (int)(voltage * 10) % 10;
	return xy + (float)z / 10.0;
}

float format_XYZ(float current) {
	int xyz = (int)current;
	return xyz;
}

float format_X_YZ(float power) {
	int x = (int)power;
	int yz = (int)(power * 100) % 100;
	return x + (float)yz / 100.0;
}


