#define F_CPU 8000000UL
#include <avr/io.h>
#include <util/delay.h>
#include <avr/interrupt.h>
#include <stdlib.h>
#include "LCD_16x2_H_file.h"

int main ( )
{
	unsigned int a, b, c, high, period;
	char frequency[14], duty_cy[7];
	
	LCD_Init();
	PORTD |= (1 << 6);		/* Turn ON Pull-UP resistor */
	
	while(1)
	{
		TCCR1A = 0;
		TCNT1 = 0;
		TIFR = (1<<ICF1);				/* clear Input Capture flag */

		TCCR1B |= (1 << ICES1) | (1 << CS10);	/* rising edge, No prescaler */
		while ((TIFR & (1 << ICF1)) == 0);
		a = ICR1;						/* take value of capture register */
		TIFR = (1<<ICF1);				/* clear ICP flag (Input Capture flag) */
		
		TCCR1B |= (1 << ICES1);			/* falling edge, No prescaler */
		while ((TIFR & (1 << ICF1)) == 0);
		b = ICR1;						/* take value of capture register */
		TIFR = (1<<ICF1);				/* clear Input Capture flag */
		
		TCCR1B |= (1 << ICES1) | (1 << CS10);	/* rising edge, No prescaler */
		while ((TIFR&(1<<ICF1)) == 0);
		c = ICR1;						/* take value of capture register */
		TIFR = (1<<ICF1);				/* clear Input Capture flag */

		TCCR1B = 0;			/* stop the timer */
		
		if(a < b && b < c)	
		/* check for valid condition, to avoide timer overflow reading */
		{
			high = b-a;
			period = c-a;
			/*----- calculate frequency & duty cycle --------*/
			long freq= F_CPU/period;
			float duty_cycle = ((float) high/ (float) period)*100;	
					
			ltoa(freq,frequency,10);
			
			itoa((int)duty_cycle,duty_cy,10);
			
			LCD_Command(0x80);
			LCD_String("Freq: ");
			LCD_String(frequency);
			LCD_String(" Hz    ");
			
			LCD_Command(0xC0);
			LCD_String("Duty: ");
			LCD_String(duty_cy);
			LCD_String(" %      ");
		}
		else
		{
			LCD_Clear();
			LCD_String("OUT OF RANGE!!");
		}
		_delay_ms(50);
	}
}
