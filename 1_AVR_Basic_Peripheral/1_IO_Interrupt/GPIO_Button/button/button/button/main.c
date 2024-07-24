/*
 * button.c
 *
 * Created: 28/02/2021 8:44:12 PM
 * Author : Admin
 */ 
#define F_CPU 8000000ul
#include <avr/io.h>
#include <util/delay.h>

#define button	0
#define led		1

int main(void)
{
    DDRA |= (1 << led);			//led is output
	DDRA &= ~(1 << button);		//button is input
	
	PORTA |= (1 << button);		//button input pullup
	PORTA &= ~(1 << led);		//led = 0
	
    while (1) 
    {
		if ((PINA & (1 << button)) == 0)		//check button
		{
			_delay_ms(1);						//debouncing button
			while ((PINA & (1 << button)) == 0);		//wait for releasing the button 
			PORTA ^= (1 << led);			//toggle led
		}
    }
}

