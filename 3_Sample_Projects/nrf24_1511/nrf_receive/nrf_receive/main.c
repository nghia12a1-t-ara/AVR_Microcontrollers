/*
 * nrf_receive.c
 *
 * Created: 15/11/2020 3:39:32 PM
 * Author : Admin
 */ 
#define F_CPU 16000000UL
#include <avr/io.h>
#include <util/delay.h>

#include "nrf.h"

#define BIT(x) (1 << (x))
#define SETBITS(x,y) ((x) |= (y))
#define CLEARBITS(x,y) ((x) &= (~(y)))
#define SETBIT(x,y) SETBITS((x), (BIT((y))))
#define CLEARBIT(x,y) CLEARBITS((x), (BIT((y))))

int main(void)
{
	DDRD = 0xff;
	PORTD = 0x00;
	Init_SPI();
	Init_nrf();
	unsigned char data;

	while (1)
	{
		receive_payload();
		spi_tranceiver(R_RX_PAYLOAD);
		_delay_ms(10);
		data = spi_tranceiver(RF24_NOP);
		if(data == 40)
		{
			PORTD ^= (1 << 0);
		}
		_delay_ms(10);
		reset();
	}
}
