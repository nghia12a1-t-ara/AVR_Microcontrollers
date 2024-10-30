/**
 * UART.c
 * 
 * Created: 7/17/2024 9:08:15 PM
 * Author : Nghia Taarabt
 */
#include "UART.h"

#ifndef F_CPU
	#define F_CPU	8000000UL
#endif

/* Initialize UART as master */
void UART_Init(uint32_t Baudrate)
{
    uint32_t ubrr = F_CPU / 16 / Baudrate - 1;
    UBRRH = (uint8_t)(ubrr >> 8);
    UBRRL = (uint8_t)(ubrr);
    UCSRB &= ~((1U << RXEN) | (1U << TXEN));
    UCSRC = (1 << URSEL) | (3 << UCSZ0); // 8-bit Data, 1-bit stop
}

void UART_SendByteSync(uint8_t data)
{
	UCSRB |= (1U << TXEN);
    while (!( UCSRA & (1 << UDRE)));  // Wait Transmit Buffer is Empty
    UDR = data;
	UCSRB &= ~(1U << TXEN);
}

uint8_t UART_ReceiveSync(void)
{
	uint8_t Data;
	
	UCSRB &= ~(1U << TXEN);
    while (!(UCSRA & (1 << RXC)));  // Wait Data Register is Full
    Data = UDR;
	UCSRB &= ~(1U << TXEN);
	
	return Data;
}

void UART_SendStringSync(const char *pStr, uint8_t len)
{
	uint8_t idx;
	
	UCSRB |= (1U << TXEN);
    for( idx = 0U; idx < len; idx++ )
	{
        while (!( UCSRA & (1 << UDRE)));  // Wait Transmit Buffer is Empty
		UDR = pStr[idx];
    }
	UCSRB &= ~(1U << TXEN);
}
