/*
 * nrf.c
 *
 * Created: 15/11/2020 3:25:35 PM
 * Author : Admin
 */ 
#define F_CPU 16000000UL
#include <avr/io.h>
#include <util/delay.h>
#include <avr/interrupt.h>

#include "nrf.h"

#define BIT(x) (1 << (x))
#define SETBITS(x,y) ((x) |= (y))
#define CLEARBITS(x,y) ((x) &= (~(y)))
#define SETBIT(x,y) SETBITS((x), (BIT((y))))
#define CLEARBIT(x,y) CLEARBITS((x), (BIT((y))))

int main(void)
{
	DDRA = 0x00;
	PORTA = 0xFF;
	DDRD = 0xff;
	PORTD = 0x00;
	Init_SPI();
	Init_nrf();
	unsigned char data = 40;

	while (1)
	{
		if (!(PINA & (1 << PINA1)))
		{
			_delay_ms(20);
			if (!(PINA & (1 << PINA1)))
			{
				PORTD |= (1 << 6);
				transmit_data(data);
				_delay_ms(500);
				PORTD &= ~(1 << 6);
				reset();
			}
		}
	}
}
