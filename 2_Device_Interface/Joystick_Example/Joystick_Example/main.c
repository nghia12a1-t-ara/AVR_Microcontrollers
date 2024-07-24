/*
 * Joystick_Example.c
 *
 * Created: 05/11/2020 10:25:20 PM
 * Author : Admin
 */ 
#define F_CPU 16000000ul
#include <avr/io.h>
#include <util/delay.h>

void ADC_Init(void);
int ADC_Read(char);
void PWM_init(void);

int main(void)
{
	int ADC_Value;
	
	ADC_Init();		/* Initialize ADC */
	PWM_init();
    /* Replace with your application code */
    while (1) 
    {
		ADC_Value = ADC_Read(0);
		OCR0 = ADC_Value;
    }
}

void ADC_Init()
{
	DDRA=0x0;			/* Make ADC port as input */
	ADCSRA = 0x87;			/* Enable ADC, fr/128  */
	ADMUX = 0x40;			/* Vref: Avcc, ADC channel: 0 */
	
}

int ADC_Read(char channel)
{
	int Ain,AinLow;
	
	ADMUX=ADMUX|(channel & 0x0f);	/* Set input channel to read */

	ADCSRA |= (1<<ADSC);		/* Start conversion */
	while((ADCSRA&(1<<ADIF))==0);	/* Monitor end of conversion interrupt */
	
	_delay_us(10);
	AinLow = (int)ADCL;		/* Read lower byte*/
	Ain = (int)ADCH*256;		/* Read higher 2 bits and 
					Multiply with weight */
	Ain = Ain + AinLow;				
	return(Ain);			/* Return digital value*/
}

void PWM_init()
{
	/*set fast PWM mode with non-inverted output*/
	TCCR0 |= ((1 << WGM00) | (1 << WGM01) | (1 << COM01) | (1 << CS00));
	DDRB |= (1 << PORTB3);  
	/*set OC0 pin as output*/
}
