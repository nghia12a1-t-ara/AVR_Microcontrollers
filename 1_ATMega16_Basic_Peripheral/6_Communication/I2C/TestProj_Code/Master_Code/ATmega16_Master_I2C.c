/*
 * ATmega16_Master_I2C.c
 *
 * Created: 7/17/2024 9:08:15 PM
 * Author : Nghia Taarabt
 */ 


#define F_CPU 8000000UL						/* Define CPU clock Frequency e.g. here its 8MHz */
#include <avr/io.h>							/* Include AVR std. library file */
#include <util/delay.h>						/* Include inbuilt defined Delay header file */
#include <string.h>							/* Include string header file */
#include "I2C_Master_H_file.h"				/* Include I2C header file */
#include "LCD_16x2_H_file.h"				/* Include LCD header file */

#define EEPROM_Write_Addess		0xA0
#define EEPROM_Read_Addess		0xA1

int main(void)
{
	char array[10] = "test";				/* Declare array to be print */
	LCD_Init();								/* Initialize LCD */
	I2C_Init();								/* Initialize I2C */
	I2C_Start(EEPROM_Write_Addess);			/* Start I2C with device write address */
	I2C_Write(0x00);						/* Write start memory address for data write */
	for (int i = 0; i<strlen(array); i++)	/* Write array data */
		{
			I2C_Write(array[i]); 
		}
	I2C_Stop();								/* Stop I2C */
	_delay_ms(10);
	I2C_Start(EEPROM_Write_Addess);			/* Start I2C with device write address */
	I2C_Write(0x00);						/* Write start memory address */
	I2C_Repeated_Start(EEPROM_Read_Addess);	/* Repeat start I2C with device read address */
	for (int i = 0; i<strlen(array); i++)	/* Read data with acknowledgment(ack) */
		{
			LCD_Char(I2C_Read_Ack());
		}
	I2C_Read_Nack();						/* Read flush data with nack */
	I2C_Stop();								/* Stop I2C */
	return 0;
}