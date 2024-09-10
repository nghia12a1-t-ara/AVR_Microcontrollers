/*
 * ATmega32_Slave.c
 * http://www.electronicwings.com
 *
 * Created: 7/17/2024 9:08:15 PM
 * Author : Nghia Taarabt
 */ 


#define F_CPU 8000000UL							/* Define CPU clock Frequency e.g. here its 8MHz */
#include <avr/io.h>								/* Include AVR std. library file */
#include <util/delay.h>							/* Include inbuilt defined Delay header file */
#include <stdio.h>								/* Include standard I/O header file */
#include <string.h>								/* Include string header file */
#include "LCD_16x2_H_file.h"					/* Include LCD header file */
#include "I2C_Slave_H_File.h"					/* Include I2C slave header file */

#define Slave_Address			0x20

int main(void)
{
	char buffer[10];
	int8_t count = 0;
	
	LCD_Init();
	I2C_Slave_Init(Slave_Address);
	
	LCD_String_xy(1, 0, "Slave Device");
	
	while (1)
	{
		switch(I2C_Slave_Listen())				/* Check for any SLA+W or SLA+R */
		{
			case 0:
			{
				LCD_String_xy(2, 0, "Receiving :       ");
				do
				{
					sprintf(buffer, "%d    ", count);
					LCD_String_xy(2, 13, buffer);
					count = I2C_Slave_Receive();/* Receive data byte*/
				} while (count != -1);			/* Receive until STOP/REPEATED START received */
				count = 0;
				break;
			}
			case 1:
			{
				int8_t Ack_status;
				LCD_String_xy(2, 0, "Sending :       ");
				do
				{
					Ack_status = I2C_Slave_Transmit(count);	/* Send data byte */
					sprintf(buffer, "%d    ",count);
					LCD_String_xy(2, 13, buffer);
					count++;
				} while (Ack_status == 0);		/* Send until Acknowledgment is received */
				break;
			}
			default:
				break;
		}
	}
}

