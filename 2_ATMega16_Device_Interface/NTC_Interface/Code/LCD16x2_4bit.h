/*
 * LCD16x2_4bit.h
 *
 * http://www.electronicwings.com
 */ 


#ifndef LCD16X2_4BIT_H_
#define LCD16X2_4BIT_H_

#define F_CPU 8000000UL					/* Define CPU Frequency e.g. here its 8MHz */
#include <avr/io.h>						/* Include AVR std. library file */
#include <util/delay.h>					/* Include inbuilt defined Delay header file */

#define LCD_Dir DDRB					/* Define LCD data port direction */
#define LCD_Port PORTB					/* Define LCD data port */
#define RS PB0							/* Define Register Select (data reg./command reg.) signal pin */
#define EN PB1 							/* Define Enable signal pin */

void LCD_Init ();
void LCD_Clear();
void LCD_String (char *str);
void LCD_Char( unsigned char data );
void LCD_Command( unsigned char cmnd );
void LCD_String_xy (char row, char pos, char *str);

#endif /* LCD16X2_4BIT_H_ */