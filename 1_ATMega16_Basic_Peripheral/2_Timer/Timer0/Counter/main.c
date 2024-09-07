/*
 * Counter.c
 *
 * Created: 31/03/2020 8:03:54 PM
 * Author : Admin
 */ 

#include <avr/io.h>


int main(void)
{	
	DDRC = 0xFF;
	PORTC = 0x00;
	TCCR0 |= (1 << CS02) | (1 << CS01) | (1 << CS00);
	TCNT0 = 0; 
    /* Replace with your application code */
    while (1) 
    {
		PORTC = TCNT0;
    }
}

