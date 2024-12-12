/*
 * RTC_DS1307_Write.c
 *
 * Created: 7/17/2024 9:08:15 PM
 * Author : Nghia Taarabt
 */ 

#include <avr/io.h>
#include <stdio.h>
#include "I2C_Master_H_file.h"

#define Device_Write_address	0xD0			/* Define RTC DS1307 slave address for write operation */
#define Device_Read_address		0xD1			/* Make LSB bit high of slave address for read operation */
#define hour_12_AM				0x40
#define hour_12_PM				0x60
#define hour_24					0x00

void RTC_Clock_Write(char _hour, char _minute, char _second, char AMPM)
{
	_hour |= AMPM;
	I2C_Start(Device_Write_address);			/* Start I2C communication with RTC */
	I2C_Write(0);								/* Write on 0 location for second value */
	I2C_Write(_second);							/* Write second value on 00 location */
	I2C_Write(_minute);							/* Write minute value on 01 location */
	I2C_Write(_hour);							/* Write hour value on 02 location */
	I2C_Stop();									/* Stop I2C communication */
}

void RTC_Calendar_Write(char _day, char _date, char _month, char _year)	/* function for calendar */
{
	I2C_Start(Device_Write_address);			/* Start I2C communication with RTC */
	I2C_Write(3);								/* Write on 3 location for day value */
	I2C_Write(_day);							/* Write day value on 03 location */
	I2C_Write(_date);							/* Write date value on 04 location */
	I2C_Write(_month);							/* Write month value on 05 location */
	I2C_Write(_year);							/* Write year value on 06 location */
	I2C_Stop();									/* Stop I2C communication */
}

int main(void)
{
	I2C_Init();
	RTC_Clock_Write(0x11, 0x59, 0x00, hour_12_PM);/* Write Hour Minute Second Format */
	RTC_Calendar_Write(0x07, 0x31, 0x12, 0x16);	/* Write day date month and year */
	while(1);
}