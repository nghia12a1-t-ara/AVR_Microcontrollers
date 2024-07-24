/*
 * Timer0_delay.c
 *
 * Created: 31/03/2020 2:23:56 PM
 * Author : Admin
 */ 
#define F_CPU 8000000ul
#include <avr/io.h>

void T0delay();

int main(void)
{
	DDRB |= (1 << 0);		/* PORTB as output*/
	
	while(1)  		/* Repeat forever*/
	{
		PORTB |= (1 << 0) ;
		T0delay();  	/* Give some delay */
		PORTB &= ~(1 << 0) ;
		T0delay();
	}
}

void T0delay()
{
	TCNT0 = 0x00 ;  		/* Load TCNT0*/ //TCNT0 => 0xFF
	TCCR0 |= (1 << CS00) ;  		/* Timer0, normal mode, no pre-scalar */
	
	/*
		f = 8MHz => T = 1/8M = 0.125us
		count = 255 - 0 = 255 lan dem
		t = 255 * 0.125us = 31.875us
		
		delay 10us => t = 10us => count = 10/0.125 = 80
		=> 255 - 80 = 175 = 0xAF
	*/
	
	while((TIFR & 0x01) == 0);  /* Wait for TOV0 to roll over */ //0 => 1
	TCCR0 = 0;
	TIFR = 0x1;  		/* Clear TOV0 flag*/
}
