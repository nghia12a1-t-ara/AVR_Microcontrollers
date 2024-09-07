/*
 * LCD+Keypad.c
 *
 * Created: 18/06/2020 10:35:36 AM
 * Author : Nghia
 */ 

#define  F_CPU 16000000UL
#include <stdlib.h>
#include <avr/io.h>
#include <util/delay.h>
#include "LCD_4.h"
#include "PORT_4.h"
#include "ADC.h"

unsigned char keypad[4][4] = {	{'7','8','9','/'},
								{'4','5','6','*'},
								{'1','2','3','-'},
								{' ','0','=','+'}};
									
int Key_Value[4][4] = {	{ 1023, 512, 341, 256 },
						{ 180 , 153, 133, 118 },
						{ 98  , 90 , 83 , 76  },
						{ 68  , 64 , 60 , 57  }};

int main(void)
{
	LCD_Init();
	ADC_Init();
	LCD_Clear();

	int ADC_Value;
	//char buffer[5];
	
    while (1) 
    {
		ADC_Value = ADC_Read(0);
		
		for (int i = 0; i < 4; i++)
		{
			for (int j = 0; j < 4; j++)
			{
				if (Key_Value[i][j] == ADC_Value)
				{
					_delay_ms(20);
					LCD_Char(keypad[i][j]);
				}
			}
		}
		
		if (Key_Value[3][0] == ADC_Value)
		{
			LCD_Clear();
		}
		
		//if (5 < ADC_Value)
		//{
			//LCD_Clear();
			//itoa(ADC_Value, buffer, 10);
			//LCD_String(buffer);
		//}
    }
}


