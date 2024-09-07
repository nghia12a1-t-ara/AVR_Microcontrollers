#include "SPI.h"

#include <avr/io.h>
#include <avr/sfr_defs.h>
#include <avr/interrupt.h>

#define SPI		PORTB
#define	SCK		7
#define MISO	6
#define MOSI	5
#define SS		4

#define cbi(port, bit)	(port) &= ~(1 << (bit))
#define sbi(port, bit)	(port) |= (1 << (bit))

void SPI_MasterInit(void)
{
	SPI |= (1 << SCK) | (1 << MOSI) | (1 << SS);
	SPCR |= (1 << SPE) | (1 << MSTR) | (1 << SPR0);		//Master, F_CPU/4
	sbi(SPI, SS);
}

void SPI_Transmit(char data)
{
	SPDR = data;
	while(bit_is_clear(SPSR, SPIF));
}