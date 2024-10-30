/*
 * EERPROM_AT24C256.c
 *
 * Created: 7/17/2024 9:08:15 PM
 * Author : Nghia Taarabt
 */ 
#include "EERPROM_AT24C256.h"

/* Write a byte to a specific address in EEPROM */
void EEP_WriteByte(uint16_t address, uint8_t data)
{
    I2C_Start();
    I2C_WriteByte(EEPROM_I2C_ADDRESS | 0); 		/* Write operation */
    I2C_WriteByte((uint8_t)(address >> 8)); 	/* Address High Byte */
    I2C_WriteByte((uint8_t)(address & 0xFF)); 	/* Address Low Byte */
    I2C_WriteByte(data);
    I2C_Stop();
    _delay_ms(EEPROM_WRITE_TIMEMS); 	/* Wait for write cycle to complete */
}

/* Read a byte from a specific address in EEPROM */
uint8_t EEP_ReadByte(uint16_t address)
{
    uint8_t data;
    
    I2C_Start();
    I2C_WriteByte(EEPROM_I2C_ADDRESS | 0); 		/* Write operation for address setting */
    I2C_WriteByte((uint8_t)(address >> 8)); 	/* Address High Byte */
    I2C_WriteByte((uint8_t)(address & 0xFF)); 	/* Address Low Byte */
    
    I2C_Start(); 						/* Repeated start */
    I2C_WriteByte(EEPROM_I2C_ADDRESS | 1);	/* Read operation */
    data = I2C_Read_NACK(); 			/* Read one byte and send NACK */
    I2C_Stop();
    
    return data;
}

/* Write a page (64 bytes) to EEPROM */
void EEP_WritePage(uint16_t address, uint8_t* pData, uint8_t length)
{
	uint8_t page_idx;

	if( length > EEP_PAGE_SIZE )
	{
		length = EEP_PAGE_SIZE;		/* Max page size is 64 bytes */
    }
    I2C_Start();
    I2C_WriteByte(EEPROM_I2C_ADDRESS | 0); 		/* Write operation */
    I2C_WriteByte((uint8_t)(address >> 8)); 	/* Address High Byte */
    I2C_WriteByte((uint8_t)(address & 0xFF)); 	/* Address Low Byte */
    
    for( page_idx = 0U; page_idx < length; page_idx++ )
	{
        I2C_WriteByte(pData[page_idx]);
    }
    
    I2C_Stop();
    _delay_ms(EEPROM_WRITE_TIMEMS);		/* Wait for write cycle to complete */
}

/* Read multiple bytes from EEPROM */
void EEP_ReadBuffer(uint16_t address, uint8_t* pBuffer, uint16_t length)
{
	uint16_t dataIdx;
	
    I2C_Start();
    I2C_WriteByte(EEPROM_I2C_ADDRESS | 0); 		/* Write operation for address setting */
    I2C_WriteByte((uint8_t)(address >> 8)); 	/* Address High Byte */
    I2C_WriteByte((uint8_t)(address & 0xFF)); 	/* Address Low Byte */
    
    I2C_Start(); 		/* Repeated start */
    I2C_WriteByte(EEPROM_I2C_ADDRESS | 1); 		/* Read operation */
    
    for( dataIdx = 0; dataIdx < length - 1; dataIdx++ )
	{
        pBuffer[dataIdx] = I2C_Read_ACK(); 	/* Read with ACK for all but last byte */
    }
	
    pBuffer[length - 1] = I2C_Read_NACK(); 	/* Read last byte with NACK */
    I2C_Stop();
}
