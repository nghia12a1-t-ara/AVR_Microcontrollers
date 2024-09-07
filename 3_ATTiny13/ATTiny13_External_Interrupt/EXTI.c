/*
 * External_Interrupt.c
 *
 * Created: 21/07/2021 8:52:38 PM
 * Author : Nghia Taarabt
 */ 

#include <avr/io.h>
#include <avr/interrupt.h>

ISR(PCINT0_vect) 
{
	while ( (PINB & (1 << 0)) == 0 );
	PORTB ^= (1 << 4);
}

int main (void)
{
	DDRB &= ~(1 << 0);		// PB0 = Input	
	DDRB |= (1 << 4);		// PB4 = Output
	PORTB |= (1 << 0);		// PB0 = Pullup
	PORTB |= (1 << 4);		// PB4 = HIGH
	
	MCUCR |= 1 << ISC01;	//set INT0 as falling edge trigger
	PCMSK |= (1 << PCINT0);
	
	GIMSK |= (1 << PCIE);
	GIMSK |= 1 << INT0;		//enable INTO in global interrupt mask
	
	sei(); //enable global interrupt <=> SREG |= (1 << 7);

	while(1) 
	{
		// sleep mode
	}
}

