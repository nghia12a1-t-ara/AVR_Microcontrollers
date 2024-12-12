/*
 * LCD16x2_4Bit.h
 *
 * Created: 7/17/2024 9:08:15 PM
 * Author : Nghia Taarabt
 */ 


#ifndef LCD16X2_4BIT_H_
#define LCD16X2_4BIT_H_
#define  F_CPU 8000000UL
#include <avr/io.h>
#include <util/delay.h>
#define LCD_DPRT PORTB
#define LCD_DDDR DDRB
#define LCD_RS 0
#define LCD_EN 1

void lcdcommand(unsigned char cmnd);
void lcddata(unsigned char data);
void lcdinit();
void lcd_print_xy(char row, char pos, char* str);
void lcd_print(char *str);
void lcd_clear();




#endif /* LCD16X2_4BIT_H_ */