/*
 * Step 2.c
 *
 * Created: 15/10/2024 10:03:45 am
 * Author : Minseo421
 */ 

#include <avr/io.h>
#include <avr/interrupt.h> // For sei() and ISR declarations
#include <stdio.h>
#include <stdlib.h>
#include <math.h> // Include math.h for sqrt()
#include "adc.h"
#include "common.h"
#include "uart.h"
#include "timer0.h"
#include "timer1.h" // Add this to ensure timer1_init is declared
#include "display.h"
#include "interrupts.h"

volatile uint16_t counter = 0;    // 4-digit counter is needed for 0 to 9999
volatile uint8_t decimal_pos = 4; // decimal points managing

// ISR for Timer0
ISR(TIMER0_COMPA_vect) {
	send_next_character_to_display();
}

float calculateVoltage(){
	float array[40];
	float adcValue = 0;
	float totalVoltage = 0;
	for (int i = 0; i < 40; i++){
		adcValue =  adc_convert_mv((uint32_t) adc_read(0));
		array[i] = adcValue;
		totalVoltage = totalVoltage + (array[i]*array[i]);
	}
	
	float RMS_V  = sqrt(totalVoltage); 
	
	float Gvs = 4.7/(4.7+100);
	float Gvo = 1;
	
	float Vvfinal = Gvs * Gvo * RMS_V + 2.1;
	
	return Vvfinal;
}

float calculateCurrent(){
	float array[40];
	float adcValue = 0;
	float Vif_pk = 0;
	for (int i = 0; i < 40; i++){
		adcValue =  adc_convert_mv((uint32_t) adc_read(1));
		array[i] = adcValue;
		
		for (int i = 0 ;i<40 ; i++){ // getting pk of I
			if(array[i]>Vif_pk){
				Vif_pk = array[i];
			}
		}
	}
	
	float Gis = 0.56;
	float Gio = 2.1026;
	
	float I_pk = (Vif_pk - 2.1)/(Gis * Gio);
	
	return I_pk;
}

float calculatePower(){
	float V = calculateVoltage();
	
	// get RMS_I
	float array[40];
	float adcValue = 0;
	float totalVoltage = 0;
	for (int i = 0; i < 40; i++){
		adcValue =  adc_convert_mv((uint32_t) adc_read(1));
		array[i] = adcValue;
		totalVoltage = totalVoltage + (array[i]*array[i]);
	}
	
	float RMS_V  = sqrt(totalVoltage);
	
	float Gis = 0.56;
	float Gio = 2.1026;
	
	float RMS_I = (RMS_V - 2.1)/(Gis * Gio);
	
	//return power
	return V*RMS_I;
}

int main(void) {
	// Initialize the display and the timer
	init_display();
	timer0_init();
	sei();

	while (1) {
		// counter delay time
		_delay_ms(1000000);
		counter = (counter + 1) % 4;  // reset after 9999
		
		switch (counter) {
			case 0:
			seperate_and_load_characters(calculateVoltage() * 1000, 0); //voltage
			break;
			case 1:
			seperate_and_load_characters(calculateCurrent()*10000, 2); //current
			break;
			case 2:
			seperate_and_load_characters(calculatePower() * 1000, 0); //power
			break;
		}
}
}