#define F_CPU 8000000UL						/* Define CPU Frequency e.g. here its 8MHz */
#include <avr/io.h>							/* Include AVR std. library file */
#include <avr/interrupt.h>
#include <stdio.h>							/* Include std. library file */
#include <util/delay.h>						/* Include Delay header file */

volatile uint8_t Direction = 0; 

void ADC_Init()								/* ADC Initialization function */
{
	DDRA = 0x00;							/* Make ADC port as input */
	ADCSRA = 0x87;							/* Enable ADC, with freq/128  */
	ADMUX = 0x40;							/* Vref: Avcc, ADC channel: 0 */
}

int ADC_Read(char channel)					/* ADC Read function */
{
	ADMUX = 0x40 | (channel & 0x07);		/* set input channel to read */
	ADCSRA |= (1<<ADSC);					/* Start ADC conversion */
	while (!(ADCSRA & (1<<ADIF)));			/* Wait until end of conversion by polling ADC interrupt flag */
	ADCSRA |= (1<<ADIF);					/* Clear interrupt flag */
	_delay_ms(1);							/* Wait a little bit */
	return ADCW;							/* Return ADC word */
}

ISR(INT0_vect)
{
	Direction = ~Direction;					/* Toggle Direction */
	_delay_ms(50);							/* Software de-bouncing control delay */
}

int main(void)
{
	DDRC = 0xFF;							/* Make PORTC as output Port */
	DDRD &= ~(1<<PD2);						/* Make INT0 pin as Input */
	DDRB |= (1<<PB3);						/* Make OC0 pin as Output */
	GICR = (1<<INT0);						/* Enable INT0*/
	MCUCR = ((1<<ISC00)|(1<<ISC01));	    /* Trigger INT0 on Rising Edge triggered */	
	sei();									/* Enable Global Interrupt */
	ADC_Init();								/* Initialize ADC */
	TCNT0 = 0;								/* Set timer0 count zero */
	TCCR0 = (1<<WGM00)|(1<<WGM01)|(1<<COM01)|(1<<CS00)|(1<<CS01);/* Set Fast PWM with Fosc/64 Timer0 clock */
	while(1)
	{
		if (Direction !=0)					/* Rotate DC motor Clockwise */
			PORTC = 1;
		else								/* Else rotate DC motor Anticlockwise */
			PORTC = 2;
		OCR0 = (ADC_Read(0)/4);				/* Read ADC and map it into 0-255 to write in OCR0 register */
	}
}
