/*
 * adc.h
 *
 * Created: 3/09/2024 2:06:05 pm
 *  Author: SamSung
 */ 


#ifndef ADC_H_
#define ADC_H_

#include <stdint.h> // Necessary for definitions of uint8_t etc

void adc_init();
uint16_t adc_read(uint8_t chan);
uint32_t adc_convert_mv(uint32_t raw_count);



#endif /* ADC_H_ */