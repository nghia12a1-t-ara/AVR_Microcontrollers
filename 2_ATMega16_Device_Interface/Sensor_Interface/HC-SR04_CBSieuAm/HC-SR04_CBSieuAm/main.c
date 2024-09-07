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
	
	sei();			/* Cho phép ng?t t?ng */
	TIMSK = (1 << TOIE1);	/* Cho phép ng?t tràn Timer1 */
	TCCR1A = 0;		/* Ch? ?? ho?t ??ng bình th??ng */

	while(1)
	{
		/* Phát xung 10us t?i chân Trig */
		PORTA |= (1 << Trigger_pin);
		_delay_us(10);
		PORTA &= (~(1 << Trigger_pin));
		
		TCNT1 = 0;	/* Xóa b? ??m Timer */
		TCCR1B = 0x41;	/* ch? ?? b?t xung s??n lên chân Echo */
		TIFR = 1<<ICF1;	/* Xóa c? Input Capture */
		TIFR = 1<<TOV1;	/* Xóa c? tràn Timer */

		/* Tính toán ?? r?ng xung Echo b?ng Input Capture */
		
		while ((TIFR & (1 << ICF1)) == 0);/* ??i s??n lên */
		TCNT1 = 0;	/* Xóa b? ??m Timer */
		TCCR1B = 0x01;	/* Ch? ?? b?t xung s??n xu?ng Echo */
		TIFR = 1<<ICF1;	/* Xóa c? Input Capture */
		TIFR = 1<<TOV1;	/* Xóa c? tràn Timer */
		TimerOverflow = 0;/* Xóa bi?n ??m Timer overflow */

		while ((TIFR & (1 << ICF1)) == 0);/* ??i s??ng xu?ng */
		count = ICR1 + (65535 * TimerOverflow);	/* Tính toán giá tr? Timer*/
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