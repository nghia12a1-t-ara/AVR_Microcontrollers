#define F_CPU 8000000UL
#include <avr/io.h>
#include <util/delay.h>

// doc gia tri nhiet do tai chan AIN0 (PB2) và so sanh voi gia tri dat o chan PB3 - AIN1
// vuot qua thi bao = led tai pc7

int main()
{
	DDRC |= (1 << 7);			// output
	ADCSRA &= ~(1 << ADEN); 
	SFIOR |= (1 << ACME);
	ADMUX = 0x00;		//ADC0 = input 
	ACSR = 0x00;
	
	while(1)
	{
		if (ACSR & (1 << ACO))		// V_AIN0 > V_AIN1
			PORTC |= (1 << 7);   //led sang 
		else
			PORTC &= ~(1 << 7);
	}
}
