#define F_CPU 8000000UL
#include <avr/io.h>						
#include <util/delay.h>					
#include <avr/eeprom.h>					/* Include AVR EEPROM header file */
#include <string.h>						
#include "LCD_16x2_H_file.h"				

// ghi mot chuoi ky tu vao cac o nho cua EEPROM 
// Doc cac ky tu do va in ra LCD

int main()
{
	char R_array[16], W_array[16] = "EEPROM TEST";
	LCD_Init();
	
	/* Gan gia tri cho 16 o nho lien tiep ma R_array tro toi = 'a'*/
	memset(R_array, 'a', 16);		//R_array[16] = "aaaaaaaaaaaaaaaa"
	eeprom_busy_wait();							//  "EEPROM TESTaaaaa"
	
	/* Ghi gia tri vao EEPROM */		
	eeprom_write_block(W_array, 0, strlen(W_array));
	
	/* Doc gia tri tu EEPROM va dat vao R_array */
	eeprom_read_block(R_array, 0, strlen(W_array));
	
	LCD_String(R_array);					
	return(0);
}