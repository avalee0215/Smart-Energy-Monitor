/*
 * uart.h
 *
 * Created: 20/08/2024 3:37:01 pm
 *  Author: Group 14
 
 */ 
#ifndef UART_H // if not defined,
#define UART_H //define uart_h

#include <stdio.h>  // Use for the printf function

// Function prototypes
void uart_init(uint32_t baud_rate);
void uart_transmit_data(char data);
void uart_transmit_string(const char* str);
int uart_printf(char var, FILE *stream);
void extract_digits_from_define(int value, char* hundreds, char* tens, char* ones);
char convert_to_ascii(char digit);

#endif

