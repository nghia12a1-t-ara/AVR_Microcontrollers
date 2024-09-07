/*
 * ATTiny13_ADC.c
 *
 * Created: 19/07/2021 9:42:31 PM
 * Author : Nghia Taarabt
 */ 

#include <avr/io.h>
#include <util/delay.h>

void ADC_Init(uint8_t channel);		// Choose ADC channel & Enable ADC
uint16_t ADC_Read(void);			// Read ADC Voltage 

int main(void)
{
	DDRB |= (1 << 1);
	PORTB |= (1 << 1);
	
    ADC_Init(3);
	uint16_t ADC_Value = 0;
	float Voltage = 0;
	
    while (1) 
    {
		ADC_Value = ADC_Read();
		Voltage = (float)ADC_Value * 5 / 1024;
		
		if ((Voltage >= 0) && (Voltage < 1.5))
		{
			for (int i = 0; i < 5; i++)
			{
				PORTB ^= (1 << 1);
				_delay_ms(100);
			}
		}
		else if (Voltage < 3.5)
		{
			for (int i = 0; i < 3; i++)
			{
				PORTB ^= (1 << 1);
				_delay_ms(500);
			}
		}
		else if (Voltage < 5)
		{
			for (int i = 0; i < 2; i++)
			{
				PORTB ^= (1 << 1);
				_delay_ms(1000);
			}
		}
		else
		{
			PORTB &= ~(1 << 1);
		}
    }
}

void ADC_Init(uint8_t channel)		/* Channel = 0 -> 3 */
{
	switch(channel) 
	{
		case PB2: ADMUX = (1 << MUX0); break;				// ADC1
		case PB4: ADMUX = (1 << MUX1); break;				// ADC2
		case PB3: ADMUX = (1 << MUX0) | (1 << MUX1); break; // ADC3
		case PB5:											// ADC0
		default: ADMUX = 0; break;
	}
	
	ADMUX &= ~(1 << REFS0);		// explicit set VCC as reference voltage (5V)
	ADCSRA |= (1 << ADEN);		// Enable ADC
}

uint16_t ADC_Read(void)
{
	uint8_t low, high;		// ADCH & ADCL
	uint16_t ADC_Value;		
	
	ADCSRA |= (1 << ADSC);					// Run single conversion
	while( (ADCSRA & (1 << ADSC)) == 1 );	// Wait conversion is done

	// Read values
	low = ADCL;
	high = ADCH;
	ADC_Value = (high << 8) | low;

	// combine two bytes
	return ADC_Value;
} 
