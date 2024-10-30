/*
 * EERPROM_AT24C256.h
 *
 * Created: 7/17/2024 9:08:15 PM
 * Author : Nghia Taarabt
 */
#ifndef __EEP_AT24C256_H__
#define __EEP_AT24C256_H__

#define F_CPU 8000000UL
#include "I2C.h"
#include <util/delay.h>

/* EEPROM AT24C256 I2C address (A0, A1, A2 pins connected to GND) */
#define EEPROM_I2C_ADDRESS 		(0xA0)
#define EEPROM_WRITE_TIMEMS		(5)		/* Delay Time to Write - See the DataSheet */
#define EEP_PAGE_SIZE 			(64U)

/* Write a byte to a specific address in EEPROM */
void EEP_WriteByte(uint16_t address, uint8_t data);

/* Read a byte from a specific address in EEPROM */
uint8_t EEP_ReadByte(uint16_t address);

/* Write a page (64 bytes) to EEPROM */
void EEP_WritePage(uint16_t address, uint8_t* pData, uint8_t length);

/* Read multiple bytes from EEPROM */
void EEP_ReadBuffer(uint16_t address, uint8_t* pBuffer, uint16_t length);

#endif	/* __EEP_AT24C256_H__ */
