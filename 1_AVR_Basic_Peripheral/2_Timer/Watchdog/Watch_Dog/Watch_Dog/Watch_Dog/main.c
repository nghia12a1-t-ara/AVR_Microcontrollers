/*
 * Watch_Dog.c
 *
 * Created: 04/03/2021 11:00:47 PM
 * Author : Admin
 */ 

#define F_CPU 8000000UL
#include <avr/io.h>
#include <util/delay.h>
#include <avr/interrupt.h>

#define LED_DDR DDRD
#define LED_PORT PORTD

void WDT_ON()
{
	/*
	Watchdog timer enables with typical timeout period 2.1 
	second.
	*/
	WDTCR = (1<<WDE)|(1<<WDP2)|(1<<WDP1)|(1<<WDP0);
}

void WDT_OFF()
{
	/*
	This function use for disable the watchdog timer.
	*/
	WDTCR = (1<<WDTOE)|(1<<WDE);
	WDTCR = 0x00;
}

int main(void)
{	
	DDRD &= ~(1 << 3);
	PORTD |= (1 << 3);
	LED_DDR |= 0xC0;
	
	// interrupt 1 set-up
	MCUCR |= (1 << ISC11);
	GICR |= (1 << INT1);
	sei();

    while(1)
	{
		WDT_ON();		/* Enable the watchdog timer */
		LED_PORT |= (1<<6);	/* Set PD6 pin to logic high */
		//_delay_ms(500);	/* Wait for 1 second */
		//LED_PORT &= ~(1<<6);	/* Clear PD6 pin */
		//_delay_ms(500);
		WDT_OFF();
	}
}

ISR(INT1_vect)
{
	LED_PORT &= ~(1<<6);
	while((PIND & (1 << 3)) == 0);
}
