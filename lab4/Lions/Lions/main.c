/*
 * Lions.c
 *
 * Created: 2022-02-28 13:53:14
 * Author : Jonas Andreasson
 */ 

#include <avr/io.h>
#include <stdint.h>
#include <avr/interrupt.h>
int counter = 0;
volatile uint8_t prev_states[4];
uint8_t legalMove1;
uint8_t legalMove2;
void wild(){
	counter++;
}
void den(){
	counter--;
}
void sensor_init(){
	legalMove2 = 0b00101101;
	legalMove1 = 0b00011110;
	for(int i = 1; i < 4; i++){
		prev_states[i] = 0;
	}
	DDRC |= 0x0f;
	PCICR |= (1 << PCIE1);     // set PCIE1 to enable PCMSK1 scan
	PCMSK1 |= (1 << PINC6) || (1<<PINC7);   // set pin C 6 & 7 to trigger an interrupt on state change
	sei();
}
int check_eligibility(){
	uint8_t temp = 0;
	for(int i = 0; i < 4; i++){
		temp |= (prev_states[i] >> (2*i));
	}
	if (temp == legalMove1){
		den();
	}
	if(temp == legalMove2){
		wild();
	}
}
ISR (PCINT1_vect){
	
	uint8_t pins = PINC;
	pins = (pins >> 6);
	if(pins == 0){
		check_eligibility();
	}
	for(int i = 0; i < 3; i++){
		prev_states[i] = prev_states[i+1];
	}
	pins = (pins << 6);
	prev_states[3] = pins;
}



int main(void)
{
    /* Replace with your application code */
	counter = 0;
	sensor_init();
    while (1) 
    {
	
    }
}

