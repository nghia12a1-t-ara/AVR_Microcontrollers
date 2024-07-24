/*
	LM35 Interfacing with ATmega16/32
	http://www.electronicwings.com
 */ 

#define F_CPU 8000000UL
#include <avr/io.h>
#include <util/delay.h>
#include <string.h>
#include <stdio.h>
#include "LCD_16x2_H_file.h"

#define degree_sysmbol 0xdf

void ADC_Init(){										
	DDRA = 0x00;							        /* Make ADC port as input */
	ADCSRA = 0x87;									/* Enable ADC, with freq/128  */
	ADMUX = 0x40;									/* Vref: Avcc, ADC channel: 0 */
}

int ADC_Read(char channel)							
{
	ADMUX = 0x40 | (channel & 0x07);				/* set input channel to read */
	ADCSRA |= (1<<ADSC);							/* Start ADC conversion */
	while (!(ADCSRA & (1<<ADIF)));					/* Wait until end of conversion by polling ADC interrupt flag */
	ADCSRA |= (1<<ADIF);							/* Clear interrupt flag */
	_delay_ms(1);									/* Wait a little bit */
	return ADCW;									/* Return ADC word */
}


int main()
{
	char Temperature[10];
	float celsius;

	LCD_Init();                 /* initialize 16x2 LCD*/
	ADC_Init();                 /* initialize ADC*/
	
	while(1)
	{
		LCD_String_xy(1,0,"Temperature");
		celsius = (ADC_Read(0)*4.88);
		celsius = (celsius/10.00);
		sprintf(Temperature,"%d%cC  ", (int)celsius, degree_sysmbol);               /* convert integer value to ASCII string */
		LCD_String_xy(2,0,Temperature);                /* send string data for printing */
		_delay_ms(1000);
		memset(Temperature,0,10);
	}
	return 0;
}

