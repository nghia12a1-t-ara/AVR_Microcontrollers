/*
 * HC-SR04_CBSieuAm.c
 *
 * Created: 02/10/2020 10:41:12 PM
 * Author : Admin
 */ 

#define F_CPU 16000000UL
#include <avr/io.h>
#include <avr/interrupt.h>
#include <util/delay.h>
#include <stdlib.h>

#define  Trigger_pin	PORTA0	
// Use Input Capture - PD6 is ICP1 - ECHO_PIN

int TimerOverflow = 0;

ISR(TIMER1_OVF_vect)
{
	TimerOverflow ++;	/* T?ng b? ??m Timer Overflow */
}

int main(void)
{
/*	char string[10];*/
	long count;
	double distance;
	
	DDRA = 0x01;		/* Trigger pin = Output */
	PORTD = 0xFF;		/* Pull-up */
	
// 	LCD_Init();
// 	LCD_String_xy(1, 0, "Ultrasonic");
	
	sei();			/* Cho ph�p ng?t t?ng */
	TIMSK = (1 << TOIE1);	/* Cho ph�p ng?t tr�n Timer1 */
	TCCR1A = 0;		/* Ch? ?? ho?t ??ng b�nh th??ng */

	while(1)
	{
		/* Ph�t xung 10us t?i ch�n Trig */
		PORTA |= (1 << Trigger_pin);
		_delay_us(10);
		PORTA &= (~(1 << Trigger_pin));
		
		TCNT1 = 0;	/* X�a b? ??m Timer */
		TCCR1B = 0x41;	/* ch? ?? b?t xung s??n l�n ch�n Echo */
		TIFR = 1<<ICF1;	/* X�a c? Input Capture */
		TIFR = 1<<TOV1;	/* X�a c? tr�n Timer */

		/* T�nh to�n ?? r?ng xung Echo b?ng Input Capture */
		
		while ((TIFR & (1 << ICF1)) == 0);/* ??i s??n l�n */
		TCNT1 = 0;	/* X�a b? ??m Timer */
		TCCR1B = 0x01;	/* Ch? ?? b?t xung s??n xu?ng Echo */
		TIFR = 1<<ICF1;	/* X�a c? Input Capture */
		TIFR = 1<<TOV1;	/* X�a c? tr�n Timer */
		TimerOverflow = 0;/* X�a bi?n ??m Timer overflow */

		while ((TIFR & (1 << ICF1)) == 0);/* ??i s??ng xu?ng */
		count = ICR1 + (65535 * TimerOverflow);	/* T�nh to�n gi� tr? Timer*/
		/* 8MHz, Toc do song am = 343 m/s */
		distance = (double)count / 466.47;
		
		if ((distance < 10) && (distance > 0.5))
		{
			PORTD |= (1 << 0);
			distance = 0;
		}
		else
		{
			PORTD &= ~(1 << 0);
			distance = 0;
		}
	}
}