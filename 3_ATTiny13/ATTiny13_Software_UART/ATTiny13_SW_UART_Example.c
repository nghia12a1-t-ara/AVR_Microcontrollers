/**
 * ATTiny13_SW_UART_Example.c
 *
 * Created: 19/07/2021 9:42:31 PM
 * Author : Nghia Taarabt
 */ 

#include <avr/io.h>
#include <util/delay.h>
#include <avr/interrupt.h>
#include "uart.h"

int
main(void)
{
	char c;

	uart_puts("Hello Parrot!\n");

	while (1) {
		c = uart_getc();
		uart_putc(c);
	}
}
