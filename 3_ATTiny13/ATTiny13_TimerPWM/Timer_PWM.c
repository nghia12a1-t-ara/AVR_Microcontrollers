/*
 * Timer_PWM.c
 *
 * Created: 21/07/2021 6:36:09 PM
 * Author : Nghia Taarabt
 */ 

#include <avr/io.h>
#include <util/delay.h>

#define N_1    ((1 << CS00))
#define N_8    ((1 << CS01))
#define N_64   ((1 << CS01) | (1 << CS00))
#define N_256  ((1 << CS02))
#define N_1024 ((1 << CS02) | (1 << CS00))

void pwm_init(void);
void pwm_set_frequency(uint32_t PresN);
void pwm_set_duty(uint8_t duty);
void pwm_set_duty(uint8_t duty);

int main(void)
{
	uint8_t duty = 0;

	/* setup */
	pwm_init();
	pwm_set_frequency(N_8);

	/* loop */
	while (1) {
		pwm_set_duty(duty++);
		_delay_ms(100);
	}
}

void pwm_init(void)
{
	DDRB |= (1 << PB0);			// set PWM pin as OUTPUT
	TCCR0A |= (1 << WGM01) | (1 << WGM00);		// set timer mode to FAST PWM
	TCCR0A |= (1 << COM0A1);		// connect PWM signal to pin (AC0A => PB0)
}

void pwm_set_frequency(uint32_t PresN)
{
	TCCR0B &= ~( (1<<CS02)|(1<<CS01)|(1<<CS00) );	// set prescaler
	TCCR0B |= PresN;
}
 
void pwm_set_duty(uint8_t duty)
{
	OCR0A = duty; // set the OCRnx
}

void pwm_stop(void)
{
	TCCR0B &= ~((1<<CS02)|(1<<CS01)|(1<<CS00));		// stop the timer
}
 