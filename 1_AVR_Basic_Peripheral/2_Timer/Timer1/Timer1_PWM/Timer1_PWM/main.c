/*
 * Timer1_PWM.c
 *
 * Created: 01/04/2020 10:03:04 AM
 * Author : Admin
 */ 

// xuat xung PWM o 2 chan OC1A va OC1B khac nhau 

#define F_CPU 8000000ul
#include <avr/io.h>

void PWM_Init(uint16_t);
void PWM_Start(void);
void PWM_Set_Duty(uint16_t);

int main(void)
{	
	PWM_Init(2400);		//T = 2400 * 0.125us = 300us = 0.3ms
	PWM_Set_Duty(800);	//duty A = 0.3/3, B = 0.3/6
	
	PWM_Start();
    
    while (1) 
    {
    }
}

void PWM_Init(uint16_t period)
{
	DDRD = 0xFF;
	TCCR1A |= (1 << WGM11) | (1 << COM1A1) | (1 << COM1B1);	
	TCCR1B |= (1 << WGM12) | (1 << WGM13);  // chia 1
	//Fast PWM Mode, no - prescaler, ICR1 = TOP, Clear OCR pin on Compare Match
	// CS12 = CS11 = 0, CS10 = 1
	ICR1 = period;			// F_CPU = 8Mhz => T_CPU = 1/8M = 0.125us
							// T = period * 0.125us 
}

void PWM_Set_Duty(uint16_t duty)
{
	OCR1A = duty;
	OCR1B = duty/2;
}

void PWM_Start(void)
{
	TCCR1B |= (1 << CS10);
}
