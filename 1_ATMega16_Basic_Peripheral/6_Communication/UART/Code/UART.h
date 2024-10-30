/*
 * UART.h
 *
 * Created: 7/17/2024 9:08:15 PM
 * Author : Nghia Taarabt
 */ 
#ifndef __UART_H__
#define __UART_H__

#include <avr/io.h>

void UART_Init(uint32_t Baudrate);
void UART_SendByteSync(uint8_t data);
uint8_t UART_ReceiveSync(void);
void UART_SendStringSync(const char *pStr, uint8_t len);

#endif	/* __UART_H__ */
