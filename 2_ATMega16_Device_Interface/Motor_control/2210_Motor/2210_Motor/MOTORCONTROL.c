#define F_CPU 16000000ul
#include "avr/io.h"
#include "util/delay.h"
#include "MOTORCONTROL.h"

#define IN1 PORTD0
#define IN2 PORTD1
#define IN3 PORTD2
#define IN4 PORTD3


void PWM_Init(uint16_t period)
{
	DDRD |= (1 << 4) | (1 << 5);
	TCCR1A |= (1 << WGM11) | (1 << COM1A1) | (1 << COM1B1);
	TCCR1B |= (1 << WGM12) | (1 << WGM13);  // chia 1
	ICR1 = period;
}

void Left_Duty(uint16_t duty)
{
	OCR1A = duty;
}

void Right_Duty(uint16_t duty)
{
	OCR1B = duty;
}

void PWM_Start()
{
	TCCR1B |= (1 << CS10);
}

void Forward(uint16_t left, uint16_t right)
{
	PORTD |= (1 << IN3);
	PORTD &= ~(1 << IN4);
	PWM_Init(1000);
	Left_Duty(left);
	PORTD |= (1 << IN1);
	PORTD &= ~(1 << IN2);
	Right_Duty(right);
	//PWM_Start();
}

void Backward(uint16_t left, uint16_t right)
{
	PORTD &= ~(1 << IN3);
	PORTD |= (1 << IN4);
	PWM_Init(1000);
	Left_Duty(left);
	PORTD &= ~(1 << IN1);
	PORTD |= (1 << IN2);
	Right_Duty(right);
	//PWM_Start();
}

void Turnleft(uint16_t left, uint16_t right)
{
	PORTD &= ~(1 << IN3);
	PORTD |= (1 << IN4);
	PWM_Init(1000);
	Left_Duty(left);
	PORTD |= (1 << IN1);
	PORTD &= ~(1 << IN2);
	Right_Duty(right);
	PWM_Start();
}

void TurnRight(uint16_t left, uint16_t right)
{
	PORTD |= (1 << IN3);
	PORTD &= ~(1 << IN4);
	PWM_Init(1000);
	Left_Duty(left);
	PORTD &= ~(1 << IN1);
	PORTD |= (1 << IN2);
	Right_Duty(right);
	PWM_Start();
}

void Stop()
{
	TCCR1A &= ~((1 << COM1A1) | (1 << COM1B1));
}

