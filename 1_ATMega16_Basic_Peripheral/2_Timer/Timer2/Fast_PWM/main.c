/*
 * Fast_PWM.c
 *
 * Created: 31/03/2020 11:10:04 PM
 * Author : Admin
 */ 

#include <avr/io.h>


int main(void)
{
	DDRB |= (1 << DDB3);
	
	TCCR0 |= (1 << WGM01) | (1 << WGM00) | (1 << COM01) | (1 << CS01); 
	OCR0 = 100; 
    /* Replace with your application code */
    while (1) 
    {
    }
}

