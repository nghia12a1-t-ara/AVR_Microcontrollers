/**
 * ATTiny13_IR_NEC_Decoder.c
 *
 * Created: 19/08/2021 9:42:31 PM
 * Author : Nghia Taarabt
 */
/**
 *  FUSE_L=0x7A
 *  FUSE_H=0xFF
 *  F_CPU=9600000
 */

#include <avr/io.h>
#include <util/delay.h>
#include <avr/interrupt.h>

#define	LED1_PIN		PB0
#define	LED2_PIN		PB2
#define	LED3_PIN		PB3
#define	LED4_PIN		PB4

#define	IR_IN_PIN		PB1
#define	IR_IN_PORT		PORTB
#define	IR_OCR0A		(122)

#define	LOW				(0)
#define	HIGH			(1)

#define	IR_SUCCESS		(0)
#define	IR_ERROR		(1)

typedef enum {
	IR_STATE_IDLE		= 0x0U,
	IR_STATE_INIT		= 0x1U,
	IR_STATE_FINISH		= 0x2U,
	IR_STATE_PROCESS	= 0x3U,
} IR_State_t;

#define	IR_PROTO_EVENT_INIT				(0)
#define	IR_PROTO_EVENT_DATA				(1)
#define	IR_PROTO_EVENT_FINISH			(2)
#define	IR_PROTO_EVENT_HOOK				(3)

/* a 9ms leading pulse burst, NEC Infrared Transmission Protocol detected,
	counter = 0.009/(1.0/38222.) * 2 = 343.998 * 2 = 686 (+/- 30) */
#define IR_NEC_START_BURST_MIN			(655U)
#define IR_NEC_START_BURST_MAX			(815U)
/* a 4.5ms space for regular transmition of NEC Code; counter => 0.0045/(1.0/38222.0) * 2 = 344 (+/- 15) */
#define IR_NEC_START_SPACE_MIN			(330U)
#define IR_NEC_START_SPACE_MAX			(360U)
/* a 2.25ms space for NEC Code repeat; counter => 0.00225/(1.0/38222.0) * 2 = 172 (+/- 15) */
#define IR_NEC_REPEAT_SPACE_MIN			(155U)
#define IR_NEC_REPEAT_SPACE_MAX			(185U)

#define IR_NEC_BIT_NUM_MAX				(32U)
#define IR_NEC_TIMEOUT					(7400U)
#define isNEC_START_BURST(time)			(time > IR_NEC_START_BURST_MIN && time < IR_NEC_START_BURST_MAX)
#define isNEC_START_SPACE(time)			(time > IR_NEC_START_SPACE_MIN && time < IR_NEC_START_SPACE_MAX)
#define isNEC_REPEAT_SPACE(time)		(time > IR_NEC_REPEAT_SPACE_MIN && time < IR_NEC_REPEAT_SPACE_MAX)

volatile uint16_t IR_timeout = 0U;
volatile uint16_t IR_Counter = 0U;
volatile uint32_t IR_rawdata = 0U;
static IR_State_t IR_State = IR_STATE_IDLE;
uint8_t IR_proto_event = 0U;
uint8_t IR_index = 0U;
uint32_t IR_data = 0U;

void IR_init()
{
	DDRB &= ~_BV(IR_IN_PIN); // set IR IN pin as INPUT
	PORTB &= ~_BV(IR_IN_PIN); // set LOW level to IR IN pin
	TCCR0A |= _BV(WGM01); // set timer counter mode to CTC
	TCCR0B |= _BV(CS00); // set prescaler to 1
	TIMSK0 |= _BV(OCIE0A); // enable Timer COMPA interrupt
	OCR0A = IR_OCR0A; // set OCR0n to get ~38.222kHz timer frequency
	GIMSK |= _BV(INT0); // enable INT0 interrupt handler
	MCUCR &= ~_BV(ISC01); // trigger INTO interrupt on raising and falling edge
	MCUCR |= _BV(ISC00);
        sei(); // enable global interrupts
}

int8_t IR_NEC_process(uint16_t counter, uint8_t value)
{
	int8_t retval = IR_ERROR;

	switch( IR_proto_event )
	{
		case IR_PROTO_EVENT_INIT:
			IR_data = IR_index = 0U;
			retval = IR_SUCCESS;
			break;
		case IR_PROTO_EVENT_DATA:
			/* Reading 4 octets (32bits) of data:
			 1) the 8-bit address for the receiving device
			 2) the 8-bit logical inverse of the address
			 3) the 8-bit command
			 4) the 8-bit logical inverse of the command
			Logical '0' – a 562.5µs pulse burst followed by a 562.5µs (<90 IR counter cycles) space, with a total transmit time of 1.125ms
			Logical '1' – a 562.5µs pulse burst followed by a 1.6875ms(>=90 IR counter cycles) space, with a total transmit time of 2.25ms */
			if( IR_index < IR_NEC_BIT_NUM_MAX )
			{
				if( value == HIGH )
				{
					IR_data |= ((uint32_t)((counter < 90U) ? 0U : 1U) << IR_index++);
					if( IR_index == IR_NEC_BIT_NUM_MAX )
					{
						IR_proto_event = IR_PROTO_EVENT_HOOK;
					}
				}
				retval = IR_SUCCESS;
			}
			break;
		case IR_PROTO_EVENT_HOOK:
			/* expecting a final 562.5µs pulse burst to signify the end of message transmission */
			if( value == LOW )
			{
				IR_proto_event = IR_PROTO_EVENT_FINISH;
				retval = IR_SUCCESS;
			}
			break;
		case IR_PROTO_EVENT_FINISH:
			/* copying data to volatile variable; raw data is ready */
			IR_rawdata = IR_data;
			break;
		default:
			break;
	}

	return retval;
}

void IR_process(uint8_t pinIRValue)
{
	/* load IR counter value to local variable, then reset counter */
	uint16_t counter = IR_Counter;
	IR_Counter = 0;

	switch( IR_State )
	{
		case IR_STATE_IDLE:
			/* awaiting for an initial signal */
			if( pinIRValue == HIGH )
			{
				IR_State = IR_STATE_INIT;
			}
			break;
		case IR_STATE_INIT:
			/* consume leading pulse burst */
			if( pinIRValue == LOW )
			{
				if( !isNEC_START_BURST(counter) )
				{
					IR_State 	= IR_STATE_FINISH;
				}
				IR_timeout 	= IR_NEC_TIMEOUT;
			}
			else	/* pinIRValue == HIGH */
			{
				if( isNEC_START_SPACE(counter) )
				{
					IR_State = IR_STATE_PROCESS;
					IR_proto_event = IR_PROTO_EVENT_INIT;
				}
				else if( isNEC_REPEAT_SPACE(counter) )
				{
					IR_proto_event = IR_PROTO_EVENT_FINISH;
				}
				else
				{
					IR_State = IR_STATE_FINISH;
				}
			}
			break;
		case IR_STATE_PROCESS:
			/* read and decode NEC Protocol data */
			if( IR_SUCCESS != IR_NEC_process(counter, pinIRValue) )
			{
				IR_State = IR_STATE_FINISH;
			}
			break;
		case IR_STATE_FINISH:
			/* clear timeout and set idle mode */
			IR_State = IR_STATE_IDLE;
			IR_timeout = 0U;
			break;
		default:
			break;
	}

}

static int8_t IR_read(uint8_t *address, uint8_t *command)
{
	if( !IR_rawdata )
		return IR_ERROR;

	*address = IR_rawdata;
	*command = IR_rawdata >> 16;
	IR_rawdata = 0;

	return IR_SUCCESS;
}

ISR(INT0_vect)
{
	uint8_t pinIRValue;
	/* read IR_IN_PIN digital value (NOTE: logical inverse value = value ^ 1 due to sensor used) */
	pinIRValue = ((PINB & (1 << IR_IN_PIN)) > 0) ? LOW : HIGH;
	IR_process(pinIRValue);
}

ISR(TIM0_COMPA_vect)
{
	/* When transmitting or receiving remote control codes using the NEC IR transmission protocol,
	the communications performs optimally when the carrier frequency (used for modulation/demodulation)
 	is set to 38.222kHz. */
	if( IR_Counter++ > 10000 )
		IR_State = IR_STATE_IDLE;
	if( IR_timeout && --IR_timeout == 0 )
		IR_State = IR_STATE_IDLE;
}

int main(void)
{
	uint8_t addr, cmd;

	/* setup */
	DDRB |= _BV(LED1_PIN)|_BV(LED2_PIN)|_BV(LED3_PIN)|_BV(LED4_PIN); // set LED pins as OUTPUT
	IR_init();

	/* loop */
	while(1)
	{
		if( IR_read(&addr, &cmd) == IR_SUCCESS )
		{
			if( addr != 0x01 )
				continue;
			switch( cmd )
			{
				case 0x01:
					PORTB &= ~(_BV(LED1_PIN)|_BV(LED2_PIN)|_BV(LED3_PIN)|_BV(LED4_PIN)); // turn all LEDs off
					break;
				case 0x00:
					PORTB ^= _BV(LED1_PIN); // toggle LED1
					break;
				case 0x07:
					PORTB ^= _BV(LED2_PIN); // toggle LED2
					break;
				case 0x06:
					PORTB ^= _BV(LED3_PIN); // toggle LED3
					break;
				case 0x04:
					PORTB ^= _BV(LED4_PIN); // toggle LED4
					break;
				default:
					break;
			};
		}
	}
}
