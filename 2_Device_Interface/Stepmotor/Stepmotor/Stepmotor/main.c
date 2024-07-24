/*
 * Stepmotor.c
 *
 * Created: 19/11/2020 8:39:54 PM
 * Author : Admin
 */ 

#define F_CPU 16000000UL		/* Define CPU Frequency 8MHz */
#include <avr/io.h>		/* Include AVR std. library file */
#include <util/delay.h>		/* Include delay header file */
#include <avr/interrupt.h>

#define  Trigger_pin	PORTA0
// Use Input Capture - PD6 is ICP1 - ECHO_PIN
int t_period = 10;
int TimerOverflow = 0;

ISR(TIMER1_OVF_vect)
{
	TimerOverflow ++;	/* T?ng b? ??m Timer Overflow */
}

void Step_Thurac(void);
void PhatxungTrigger(void);
void Step_Trove(void);
double Khoangcach(void);

int main(void)
{
	/*	char string[10];*/
	double ketqua = 0;
	
	DDRA = 0x01;		/* Trigger pin = Output */
	DDRD = 0x0F;		/* Make PORTD lower pins as output */
	PORTD |= (1 << 4) | (1 << 5) | (1 << 6);
	
	sei();			/* Cho ph�p ng?t t?ng */
	TIMSK = (1 << TOIE1);	/* Cho ph�p ng?t tr�n Timer1 */
	TCCR1A = 0;		/* Ch? ?? ho?t ??ng b�nh th??ng */
	
	while (1)
	{
		PhatxungTrigger();
		ketqua = Khoangcach();
		if ((ketqua < 10) && (ketqua > 0.5))
		{
			Step_Thurac();
			_delay_ms(1500);
			Step_Trove();
		}
	}
}

void Step_Thurac(void)
{
	for(int i = 0; i < 12; i++)
	{
		PORTD = 0x09;
		_delay_ms(t_period);
		PORTD = 0x08;
		_delay_ms(t_period);
		PORTD = 0x0C;
		_delay_ms(t_period);
		PORTD = 0x04;
		_delay_ms(t_period);
		PORTD = 0x06;
		_delay_ms(t_period);
		PORTD = 0x02;
		_delay_ms(t_period);
		PORTD = 0x03;
		_delay_ms(t_period);
	 	PORTD = 0x01;
		_delay_ms(t_period);
	}
	PORTD = 0x09;		/* Last step to initial position */
	_delay_ms(t_period);
}

void Step_Trove(void)
{
	for(int i = 0; i < 12; i++)
	{
		PORTD = 0x09;
		_delay_ms(t_period);
		PORTD = 0x03;
		_delay_ms(t_period);
		PORTD = 0x06;
		_delay_ms(t_period);
		PORTD = 0x0C;
		_delay_ms(t_period);
		}
	PORTD = 0x09;
	_delay_ms(t_period);
}

void PhatxungTrigger(void)
{
	/* Ph�t xung 10us t?i ch�n Trig */
	PORTA |= (1 << Trigger_pin);
	_delay_us(10);
	PORTA &= (~(1 << Trigger_pin));
	
	TCNT1 = 0;	/* X�a b? ??m Timer */
	TCCR1B = 0x41;	/* ch? ?? b?t xung s??n l�n ch�n Echo */
	TIFR = 1<<ICF1;	/* X�a c? Input Capture */
	TIFR = 1<<TOV1;	/* X�a c? tr�n Timer */
}

double Khoangcach(void)
{
	/* T�nh to�n ?? r?ng xung Echo b?ng Input Capture */
	long count;
	double distance;
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
	
	return distance;
}
