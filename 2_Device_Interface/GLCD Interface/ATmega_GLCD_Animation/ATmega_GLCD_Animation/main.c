/*
 * ATmega_GLCD_Animation
 * http://electronicwings.com
 */ 

#define F_CPU 8000000UL				/* Define CPU clock Frequency 8MHz */
#include <avr/io.h>					/* Include AVR std. library file */
#include <util/delay.h>				/* Include defined delay header file */
#include <stdio.h>					/* Include standard i/o library file */
#include "Anim_Images.h"

#define Data_Port			PORTA	/* Define data port for GLCD */
#define Command_Port		PORTC	/* Define command port for GLCD */
#define Data_Port_Dir		DDRA	/* Define data port for GLCD */
#define Command_Port_Dir	DDRC	/* Define command port for GLCD */

#define RS					PC0		/* Define control pins */
#define RW					PC1
#define EN					PC2
#define CS1					PC3
#define CS2					PC4
#define RST					PC5

#define TotalPage			8

void GLCD_Command(char Command)		/* GLCD command function */
{
	Data_Port = Command;			/* Copy command on data pin */
	Command_Port &= ~(1 << RS);		/* Make RS LOW to select command register */
	Command_Port &= ~(1 << RW);		/* Make RW LOW to select write operation */
	Command_Port |=  (1 << EN);		/* Make HIGH to LOW transition on Enable pin */
	_delay_us(5);
	Command_Port &= ~(1 << EN);
	_delay_us(5);
}

void GLCD_Data(char Data)			/* GLCD data function */
{
	Data_Port = Data;				/* Copy data on data pin */
	Command_Port |=  (1 << RS);		/* Make RS HIGH to select data register */
	Command_Port &= ~(1 << RW);		/* Make RW LOW to select write operation */
	Command_Port |=  (1 << EN);		/* Make HIGH to LOW transition on Enable pin */
	_delay_us(5);
	Command_Port &= ~(1 << EN);
	_delay_us(5);
}

void GLCD_Init()					/* GLCD initialize function */
{
	Data_Port_Dir = 0xFF;
	Command_Port_Dir = 0xFF;
	/* Select both left & right half of display & Keep reset pin high */
	Command_Port |= (1 << CS1) | (1 << CS2) | (1 << RST);
	_delay_ms(20);
	GLCD_Command(0x3E);				/* Display OFF */
	GLCD_Command(0x40);				/* Set Y address (column=0) */
	GLCD_Command(0xB8);				/* Set x address (page=0) */
	GLCD_Command(0xC0);				/* Set z address (start line=0) */
	GLCD_Command(0x3F);				/* Display ON */
}

void GLCD_ClearAll()				/* GLCD all display clear function */
{
	int i,j;
	/* Select both left & right half of display */
	Command_Port |= (1 << CS1) | (1 << CS2);
	for(i = 0; i < TotalPage; i++)
	{
		GLCD_Command((0xB8) + i);	/* Increment page each time after 64 column */
		for(j = 0; j < 64; j++)
		{
			GLCD_Data(0);			/* Write zeros to all 64 column */
		}
	}
	GLCD_Command(0x40);				/* Set Y address (column=0) */
	GLCD_Command(0xB8);				/* Set x address (page=0) */
}

void GLCD_String(const char* image)	/* GLCD string write function */
{
	int column,page,page_add=0xB8,k=0;
	float page_inc=0.5;
	char byte;

	Command_Port |= (1 << CS1);		/* Select first Left half of display */
	Command_Port &= ~(1 << CS2);
	
	for(page=0;page<16;page++)		/* Print 16 pages i.e. 8 page of each half of display */
	{
		for(column=0;column<64;column++)
		{
			byte = pgm_read_byte(&image[k+column]);
			GLCD_Data(byte);		/* Print 64 column of each page */
		}
		Command_Port ^= (1 << CS1);	/* If yes then change segment controller */
		Command_Port ^= (1 << CS2);
		GLCD_Command((page_add+page_inc));/* Increment page address */
		page_inc=page_inc+0.5;
		k=k+64;						/* Increment pointer */
	}
	GLCD_Command(0x40);				/* Set Y address (column=0) */
	GLCD_Command(0xB8);				/* Set x address (page=0) */
}

int main(void)
{
	GLCD_Init();					/* Initialize GLCD */
	GLCD_ClearAll();				/* Clear all GLCD display */
	while(1)
	{
		GLCD_String(img);
		_delay_ms(500);
		GLCD_String(img1);
		_delay_ms(500);
	}
}
