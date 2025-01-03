/*
 * INT0.c
 *
 * Created: 27/02/2021 7:18:50 PM
 * Author : Admin
 */ 

#define F_CPU 8000000UL
#include <avr/io.h>
#include <avr/interrupt.h>
#include <util/delay.h>

ISR(INT1_vect)
{
	PORTA ^= (1 << 0);		//toggle led
}

int main(void)
{
	//io
	DDRA |= (1 << 0);		//PC0 = output, 0
	PORTD |= (1 << 3);			// PD3 = input pullup
		
	GICR |= (1 << INT1);	//enable INT0
	MCUCR |= (1 << ISC11);	// falling edge 
	
	sei();			//enable global int
	
	while(1)
	{
		//sleep mode
	}
}

