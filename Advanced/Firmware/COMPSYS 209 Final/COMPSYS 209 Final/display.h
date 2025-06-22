#ifndef DISPLAY_H_
#define DISPLAY_H_

#include <stdint.h>

#define SEGMENT_PORTD PORTD  
#define SEGMENT_DDRD DDRD    

void init_display(void);
void shift_out(uint8_t data);
void send_next_character_to_display(void);
void seperate_and_load_characters(uint16_t number, uint8_t decimal_pos);


#endif /* DISPLAY_H_ */
