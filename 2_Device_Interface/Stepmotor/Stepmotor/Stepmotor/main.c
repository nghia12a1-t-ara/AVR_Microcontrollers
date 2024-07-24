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
	
	sei();			/* Cho phép ng?t t?ng */
	TIMSK = (1 << TOIE1);	/* Cho phép ng?t tràn Timer1 */
	TCCR1A = 0;		/* Ch? ?? ho?t ??ng bình th??ng */
	
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
	/* Phát xung 10us t?i chân Trig */
	PORTA |= (1 << Trigger_pin);
	_delay_us(10);
	PORTA &= (~(1 << Trigger_pin));
	
	TCNT1 = 0;	/* Xóa b? ??m Timer */
	TCCR1B = 0x41;	/* ch? ?? b?t xung s??n lên chân Echo */
	TIFR = 1<<ICF1;	/* Xóa c? Input Capture */
	TIFR = 1<<TOV1;	/* Xóa c? tràn Timer */
}

double Khoangcach(void)
{
	/* Tính toán ?? r?ng xung Echo b?ng Input Capture */
	long count;
	double distance;
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
	
	return distance;
}
