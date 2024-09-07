/*
 * 2210_Motor_Control.c
 *
 * Created: 22/10/2020 2:13:55 PM
 * Author : Admin
 */ 
#define F_CPU 16000000ul
#include <avr/io.h>
#include <util/delay.h>
#include "MOTORCONTROL.h"

int main(void)
{
	DDRD = 0xFF;
	PORTD = 0x00;
	DDRA = 0x00;
	PORTA = 0xFF;

    /* Replace with your application code */
    while (1) 
    {
		if (!(PINA & (1 << 0)))
		{
			Forward(500,500);
		}
		if (!(PINA & (1 << 1)))
		{
			Backward(500,500);
		}
		if (!(PINA & (1 << 2)))
		{
			Turnleft(500,0);
		}
		if (!(PINA & (1 << 3)))
		{
			TurnRight(0,500);
		}
		if (!(PINA & (1 << 4)))
		{
			Stop();
		}
    }
	return 1;
}

