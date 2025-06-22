/*
 * COMPSYS 209 Software.c
 *
 * Created: 20/08/2024 3:34:02 pm
 * Author : Group 14
 */ 

#define F_CPU 2000000UL  // Defining system clock frequency

#include <avr/io.h>
#include <util/delay.h>
#include "uart.h"

// Hard code
#define RMSVoltage  14.5
#define PeakCurrent 125
#define Power 1.65

int main(void) {
	uart_init(9600);  // Set the UART as 9600 baud rate
	
	// As we are going to separate each digit, make as the whole numbers
	int RMS_whole = (int)( RMSVoltage  * 10);  
	int power_whole = (int)(Power * 100);             

	char hundreds, tens, ones; // save each digit with different name
	
	while (1) {
		extract_digits_from_define(RMS_whole, &hundreds, &tens, &ones); // uart.c function to extract each digit
		//transmit the RMS Voltage as XY.Z format
		uart_transmit_string("RMS Voltage is: ");
		uart_transmit_data(convert_to_ascii(hundreds));
		uart_transmit_data(convert_to_ascii(tens));
		uart_transmit_data('.');
		uart_transmit_data(convert_to_ascii(ones));
		uart_transmit_string("\r\n");

		//transmit the RMS Voltage as XYZ format
		uart_transmit_string("Peak Current is: ");
		extract_digits_from_define(PeakCurrent, &hundreds, &tens, &ones);
		uart_transmit_data(convert_to_ascii(hundreds));
		uart_transmit_data(convert_to_ascii(tens));
		uart_transmit_data(convert_to_ascii(ones));
		uart_transmit_string("\r\n");

		// transmit the RMS Voltage as X.YZ format
		uart_transmit_string("Power is: ");
		extract_digits_from_define(power_whole, &hundreds, &tens, &ones);
		uart_transmit_data(convert_to_ascii(hundreds));
		uart_transmit_data('.');
		uart_transmit_data(convert_to_ascii(tens));
		uart_transmit_data(convert_to_ascii(ones));
		uart_transmit_string("\r\n");
		uart_transmit_string("\r\n");

		_delay_ms(1000);  // 1s delay. It needs to be repeating
	}
}
