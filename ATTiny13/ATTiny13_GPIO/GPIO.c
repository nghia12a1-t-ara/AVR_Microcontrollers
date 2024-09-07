/*
 * ATTiny13_GPIO.c
 *
 * Created: 19/07/2021 8:28:53 PM
 * Author : Nghia Taarabt
 */ 

#include <avr/io.h>
#include <util/delay.h>

int main(void)
{
	DDRB |= (1 << 0);		// PB0 Output
	DDRB &= ~(1 << 1);		// PB1 Input
	
	PORTB &= ~(1 << 0);		// PB0 = 0
	PORTB |= (1 << 1);		// PB1 = Input_Pullup	
	
    while (1) 
    {
		if ( (PINB & (1 << 1)) == 0 )
		{
			_delay_ms(200);
			if ( (PINB & (1 << 1)) == 0 )
			{
				PORTB ^= (1 << 0);		// toggle PB0
			}
		}
    }
}

