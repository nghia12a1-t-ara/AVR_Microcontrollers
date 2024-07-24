#define F_CPU 8000000UL				/* Define CPU Frequency e.g. here its 8MHz */
#include <avr/io.h>					/* Include AVR std. library file */
#include <util/delay.h>				/* Include delay header file */


int main(void)
{
	int period;
	DDRD = 0x0F;					/* Make PORTD lower pins as output */
	period = 50;					/* Set period in between two steps of Stepper Motor */
	while (1)
	{
		/* Rotate Stepper Motor clockwise with Half step sequence; Half step angle 3.75 */
		for(int i = 0; i < 2; i++)		
		{
			PORTD = 0x09;
			_delay_ms(period);
			PORTD = 0x08;
			_delay_ms(period);
			PORTD = 0x0C;
			_delay_ms(period);
			PORTD = 0x04;
			_delay_ms(period);
			PORTD = 0x06;
			_delay_ms(period);
			PORTD = 0x02;
			_delay_ms(period);
			PORTD = 0x03;
			_delay_ms(period);
			PORTD = 0x01;
			_delay_ms(period);
		}
			/* last one step to acquire initial position */ 
			PORTD = 0x09;			
			_delay_ms(period);
			
			_delay_ms(500);
			
		/* Rotate Stepper Motor Anticlockwise with Full step sequence; Full step angle 7.5 */	
		for(int i = 0; i < 2; i++)		
		{
			PORTD = 0x09;
			_delay_ms(period);
			PORTD = 0x03;
			_delay_ms(period);
			PORTD = 0x06;
			_delay_ms(period);
			PORTD = 0x0C;
			_delay_ms(period);
		}
			PORTD = 0x09;
			_delay_ms(period);
			_delay_ms(500);
	}
}