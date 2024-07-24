/*
 * Timer2_CTC_Mode.c
 *
 * Created: 03/03/2021 10:43:54 PM
 * Author : Admin
 */ 

#define F_CPU 8000000ul
#include <avr/io.h>
#include <util/delay.h>

int main(void)
{
    DDRD |= (1 << 7);
	PORTD &= ~(1 << 7);		//PD7 = output
	
    while (1) 
    {
		OCR2 = 69;
		TCCR2 = 0x39;
			// CTC, set on match, no prescaler
		while ((TIFR & (1 << OCF2)) == 0);		// monitor OCF2 flag 
		TIFR = (1 << OCF2);					// Clear OCF2 by writing 1
		OCR2 = 99;
		TCCR2 = 0x29;	
			// CTC, clear on match, no prescaler
		while ((TIFR & (1 << OCF2)) == 0);
		TIFR = (1 << OCF2);					// Clear OCF2 by writing 1
    }
}
