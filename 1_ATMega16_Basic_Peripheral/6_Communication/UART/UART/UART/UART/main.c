/*
 * UART.c
 *
 * Created: 02/04/2020 10:22:11 PM
 * Author : Admin
 */ 

#include <avr/io.h>
#define F_CPU 8000000UL
#include "avr/sfr_defs.h"
#include "util/delay.h"
#include <stdlib.h>
#include <stdio.h>

void UART_Init()
{
	UBRRL = 51;	
	UCSRB |= (1 << RXEN) | (1 << TXEN) | (1 << RXCIE);
	UCSRC |= (1 << UCSZ1) | (1 << UCSZ0);						//Baud = 9600, U2X = 0, F = 8MHz	
}

void send(unsigned char c)
{
	while(bit_is_clear(UCSRA, UDRE));
	UDR = c;
}

void UART_Write_Str(char *str)
{
	unsigned char i = 0;
	while (str[i] != 0)
	{
		send(str[i]);
		i++;
	}
}

unsigned char recei()
{
	while(bit_is_clear(UCSRA, RXC));
	return UDR;
}

int main(void)
{
	DDRA &= ~(1 << 1);
	PORTA |= (1 << 1);
	DDRA |= (1 << 2);
	PORTA &= ~(1 << 2);
	//unsigned char c;
	
	UART_Init();
	
	send('1');
    /* Replace with your application code */
    while (1) 
    {
		if (recei() == '1')
		{
			send('a');
		}
		if (!(PINA & (1 << 1)))
		{
			PORTA |= (1 << 2);
			UART_Write_Str("Hello");
			while (!(PINA & (1 << 1)));
		}
    }
	return 0;
}

