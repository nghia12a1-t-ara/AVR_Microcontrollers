/*
 * I2C.h
 *
 * Created: 7/17/2024 9:08:15 PM
 * Author : Nghia Taarabt
 */ 
#ifndef __I2C_H__
#define __I2C_H__

#include <avr/io.h>
#include <util/delay.h>

#ifndef F_CPU
	#define F_CPU	8000000UL
#endif

#define SCL_FREQ 100000L		/* I2C clock frequency (100kHz) */

void I2C_Init(void);
void I2C_Start(void);
void I2C_Stop(void);
void I2C_WriteByte(uint8_t data);
uint8_t I2C_Read_ACK(void);
uint8_t I2C_Read_NACK(void);

#endif	/* __I2C_H__ */
