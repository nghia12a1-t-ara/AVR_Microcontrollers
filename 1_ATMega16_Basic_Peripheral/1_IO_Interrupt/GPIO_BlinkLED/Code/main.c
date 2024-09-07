/*
 * GPIO_LedBlink.c
 *
 * Created: 7/17/2024 9:08:15 PM
 * Author : Nghia Taarabt
 */ 

#define F_CPU 8000000UL
#include <avr/io.h>
#include <util/delay.h>

int main(void)
{
    DDRA |= (1U << 0);				/* Making Pin A0 as output pins */
	
    while(1)
    {
        PORTA |= (1U << 0);			/* Making PA0 high. This will make LED ON */
        _delay_ms(100);
		PORTA &= ~(1U << 0);		/* Making PA0 low. This will make LED OFF */
        _delay_ms(100);
    }
	return 0;
}
