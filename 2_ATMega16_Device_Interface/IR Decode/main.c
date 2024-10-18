/*
 * IR_Decoder.c
 *
 * Created: 10/17/2024 5:52:14 PM
 * Author : ADMIN
 */ 
#define F_CPU	1000000UL
#include <avr/io.h>
#include <stdio.h>
#include <avr/interrupt.h>
#include <util/delay.h>

#define TIM_TOGGLE_CAPTURE_PULSE()		TCCR1B^=(1<<ICES1)
#define	IR_SUCCESS		(0)
#define	IR_ERROR		(1)
#define	LOW				(0)
#define	HIGH			(1)

typedef enum {
	IR_STATE_IDLE		= 0x0U,
	IR_STATE_INIT		= 0x1U,
	IR_STATE_FINISH		= 0x2U,
	IR_STATE_PROCESS	= 0x3U,
} IR_State_t;

volatile uint16_t u16Before_Time;
volatile uint16_t u16Measure_Time;
volatile uint32_t u16Pulse_Width;

void UART_Write_Str(char *str, uint8_t len);
void UART_SendChar(unsigned char c);

void IR_Init(void)
{
	/* Port Pin IR Initialization - ICPn = PD6 */
	DDRD &= ~(1 << 6);		// Input
	PORTD |= (1 << 6);		// Pull-up remain the default state of SIGNAL Pin
	
	/* Timer 1 Input Capture Initialization */
	TCCR1A = 0U;
	TIFR |= (1 << ICF1);					/* Clear input capture flag */
	TCCR1B |= (1 << ICNC1) | (1 << CS10);	/* Clock No-Prescaler */
	TCCR1B &= ~(1 << ICES1);				/* Capture on Falling Edge First */
	TIMSK |= (1 << TICIE1) | (1 << TOIE1);					/* Input Capture Interrupt */
	OCR1A = 0xFFFFUL;
	TCCR1B |= (1 << WGM12);
	sei();
}

void IR_Decode(uint16_t u16CapTime)
{
	
}
volatile int a = 0, change = 0;
volatile uint32_t overflow_count = 0; // declare a global variable

ISR(TIMER1_CAPT_vect)
{
	u16Measure_Time = ICR1;
	TCNT1 = 0;		/* Reset Timer */
	TIFR |= (1 << ICF1);	/* Clear ICP Flag */
	if(overflow_count)
	{
		u16Pulse_Width = (uint32_t)(65536 * overflow_count) + (uint32_t)u16Measure_Time - (uint32_t)u16Before_Time;
	}
	else
	{
		u16Pulse_Width = (uint32_t)u16Measure_Time - (uint32_t)u16Before_Time;
	}
	
	change = 1;
	overflow_count = 0;
	u16Before_Time = u16Measure_Time;

	TIM_TOGGLE_CAPTURE_PULSE();		/* Toggle Capture Pulse to detect next Pulse */
}

/* ISR for Timer1 overflow interrupt */
ISR(TIMER1_OVF_vect)
{
	overflow_count++;	/* increment overflow count */
	TCNT1 = 0;		/* Reset Timer */
	TIFR |= (1 << TOV1);
	/* Other Tasks */

}

void IR_NEC_Read()
{

}

void UART_Init()
{
	UBRRL = 12;
	UCSRA |= (1 << U2X);
	UCSRC |= (1 << UCSZ1) | (1 << UCSZ0);						//Baud = 9600, U2X = 1, F = 1MHz
	UCSRB |= (1 << TXEN);
}

void UART_SendChar(unsigned char c)
{
	while( !(UCSRA & (1 << UDRE)) );
	UDR = c;
}

void UART_Write_Str(char *str, uint8_t len)
{
	unsigned char i = 0;
	for(i = 0U; i < len; i++)
	{
		UART_SendChar(str[i]);
	}
}

int main(void)
{
	IR_Init();
	
	DDRD |= (1 << 2);
	PORTD &= ~(1 << 2);		// LOW
	UART_Init();
	
    /* Replace with your application code */
    while (1) 
    {
		char buffer[10] = {0};
		
		if(change)
		{
			snprintf(buffer, 10, "%u", u16Pulse_Width);
			UART_Write_Str(buffer, 10);
			UART_SendChar(' ');
			change = 0;
		}
    }
}

