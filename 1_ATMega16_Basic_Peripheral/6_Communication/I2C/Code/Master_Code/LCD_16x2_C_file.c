/*
 * LCD_16x2_C_file.c
 *
 * Created: 7/17/2024 9:08:15 PM
 * Author : Nghia Taarabt
 */ 


#include "LCD_16x2_H_file.h"						/* Include LCD header file */


void LCD_Command (char cmd)							/* LCD command write function */
{
	LCD_Data_Port = cmd;							/* Write command data to LCD data port */	
	LCD_Command_Port = (0<<RS)|(0<<RW)|(1<<EN);		/* Make rs LOW (command reg.), rw LOW (Write), en HIGH (Enable) */
	_delay_ms(1);									/* Wait a ms to enable pulse and data latch */
	LCD_Command_Port = (0<<RS)|(0<<RW)|(0<<EN);		/* Make rs LOW (command reg.), rw LOW (Write), en LOW (Disable) */
	_delay_ms(5);									/* Wait little bit to get internal LCD data operation done */
}

void LCD_Char (char char_data)						/* LCD data write function */
{
	LCD_Data_Port = char_data;						/* Write data to LCD data port */
	LCD_Command_Port = (1<<RS)|(0<<RW)|(1<<EN);		/* Make rs HIGH (data reg.), rw LOW (Write), en HIGH (Enable) */
	_delay_ms(1);									/* Wait a ms to enable pulse and data latch */
	LCD_Command_Port = (1<<RS)|(0<<RW)|(0<<EN);		/* Make rs HIGH (data reg.), rw LOW (Write), en HIGH (Disable) */
	_delay_ms(5);									/* Wait little bit to get internal LCD data operation done */
}

void LCD_Init (void)								/* LCD Initialize function */
{
	LCD_Command_Dir = 0xFF;							/* Make LCD command port direction as o/p */
	LCD_Data_Dir = 0xFF;							/* Make LCD data port direction as o/p */
	
	_delay_ms(20);									/* LCD Initialization time must to get things ready should always >15ms */
	LCD_Command (0x38);								/* Initialization of 16X2 LCD in 8bit mode */
	LCD_Command (0x01);								/* Clear LCD */
	LCD_Command (0x0C);								/* Cursor OFF */
	LCD_Command (0x80);								/* 8 is for first line and 0 is for 0th position */
}

void LCD_String (char *str)							/* Send string to LCD function */
{
	int i;
	for(i=0;str[i]!=0;i++)							/* Send each char of string till the NULL */
	{
		LCD_Char (str[i]);							/* Call LCD data write */
	}
}

void LCD_String_xy (char row, char pos, char *str)	/* Send string to LCD function */
{
	if (row == 1)
		LCD_Command((pos & 0x0F)|0x80);				/* Command of first row and required position<16 */
	else if (row == 2)
		LCD_Command((pos & 0x0F)|0xC0);				/* Command of Second row and required position<16 */
	LCD_String(str);								/* Call LCD string function */
}
