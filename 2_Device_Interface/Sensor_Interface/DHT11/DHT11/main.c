#define F_CPU 8000000ul
#include <avr/io.h>
#include <util/delay.h>
#include <stdlib.h>
#include <stdio.h>
#include "LCD_4.h"

#define DHT11_PIN 6
uint8_t c = 0, I_RH, D_RH, I_temp, D_temp, Checksum;

// Dinh nghia cac chan, cac bien

// Gui xung Start
void Request()
{
	DDRD |= (1 << DHT11_PIN);
	DDRD &= ~(1 << DHT11_PIN);
	_delay_ms(20);
	DDRD |= (1 << DHT11_PIN);
}

// Doi xung phan hoi tu CB
void Response()
{
	DDRD &= ~(1 << DHT11_PIN); // input
	while (PIND & (1 << DHT11_PIN));
	while (PIND & (1 <<DHT11_PIN) == 0);
	while (PIND & (1 << DHT11_PIN));
}

// Nhan 40-bits du lieu tu Cam bien
uint8_t Receive_data()
{
	for (int q = 0; q < 8; q++)
	{
		while((PIND & (1 << DHT11_PIN)) == 0);
		_delay_ms(30);
		if (PIND & (1 << DHT11_PIN))
		{
			c = (c << 1) | 0x01;
		}
		else
		{
			c = c << 1; 
		}
		while (PIND & (1 << DHT11_PIN));
	}
	return c;
}

int main(void)
{
	char data[5];
	LCD_Init();
	LCD_Clear();
	LCD_String_xy(0, 0, "Humidity =");
	LCD_String_xy(0, 1, "Temp = ");
	
	while(1)
	{
		// Gui xung Start
		Request();
		// Doi xung phan hoi
		Response();
		// Doc 40-bit du lieu tu cam bien
		I_RH = Receive_data();
		D_RH = Receive_data();
		I_temp = Receive_data();
		D_temp = Receive_data();
		Checksum = Receive_data(); 
		// Kiem tra loi
		if ((I_RH + I_temp + D_RH + D_temp) != Checksum)
		{
			LCD_String_xy(0, 0, "ERROR!");
		}
		// Xu ly du lieu & hien thi
		else
		{
			itoa (I_RH, data, 10);
			LCD_String_xy(0, 11, data);
			
			itoa (D_RH, data, 10);
			LCD_String_xy(0, 12, data);
			
			itoa (I_temp, data, 10);
			LCD_String_xy(1, 6, data);
			
			itoa (D_temp, data, 10);
			LCD_String_xy(1, 7, data);		
		}
		_delay_ms(10);
	}
}