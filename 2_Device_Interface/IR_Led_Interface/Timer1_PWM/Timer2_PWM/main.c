#define  F_CPU 16000000ul
#include <avr/io.h>
#include "util/delay.h"
#include "stdio.h"

#define KEY_PRT 	PORTA
#define KEY_DDR		DDRA
#define KEY_PIN		PINA

unsigned char keypad[4][4] = {	{'7','8','9','/'},
{'4','5','6','*'},
{'1','2','3','-'},
{' ','0','=','+'}};

unsigned char colloc, rowloc;

char keyfind();
void PWM_init();
void Gui_Byte(unsigned char);
void UART_Init();
void UART_Write_Chr(char);
void UART_Write_Str(char*);

int main(void)
{
	UART_Init();
	
	DDRD |= (1 << DDD4);			
	PORTD &= ~(1 << PORTD4);
	DDRD &= ~(1 << DDD2);
	PORTD |= (1 << PORTD2);	
	
	UART_Init();
	PWM_init();
	OCR1B = 210;
	
	UART_Write_Chr('1');
	
	while(1)
	{
		UART_Write_Chr(keyfind());
	}
}

char keyfind()
{
	while(1)
	{
	    KEY_DDR = 0xF0;           /* set port direction as input-output */
	    KEY_PRT = 0xFF;

	    do
	    {
		KEY_PRT &= 0x0F;      /* mask PORT for column read only */
		asm("NOP");
		colloc = (KEY_PIN & 0x0F); /* read status of column */
	    }while(colloc != 0x0F);
		
	    do
	    {
		do
		{
	            _delay_ms(20);             /* 20ms key debounce time */
		    colloc = (KEY_PIN & 0x0F); /* read status of column */
		}while(colloc == 0x0F);        /* check for any key press */
			
		_delay_ms (40);	            /* 20 ms key debounce time */
		colloc = (KEY_PIN & 0x0F);
	    }while(colloc == 0x0F);

	   /* now check for rows */
	    KEY_PRT = 0xEF;            /* check for pressed key in 1st row */
	    asm("NOP");
	    colloc = (KEY_PIN & 0x0F);
	    if(colloc != 0x0F)
            {
		rowloc = 0;
		break;
	    }

	    KEY_PRT = 0xDF;		/* check for pressed key in 2nd row */
	    asm("NOP");
	    colloc = (KEY_PIN & 0x0F);
	    if(colloc != 0x0F)
	    {
		rowloc = 1;
		break;
	    }
		
	    KEY_PRT = 0xBF;		/* check for pressed key in 3rd row */
	    asm("NOP");
            colloc = (KEY_PIN & 0x0F);
	    if(colloc != 0x0F)
	    {
		rowloc = 2;
		break;
	    }

	    KEY_PRT = 0x7F;		/* check for pressed key in 4th row */
	    asm("NOP");
	    colloc = (KEY_PIN & 0x0F);
	    if(colloc != 0x0F)
	    {
		rowloc = 3;
		break;
	    }
	}

	if(colloc == 0x0E)
	   return(keypad[rowloc][0]);
	else if(colloc == 0x0D)
	   return(keypad[rowloc][1]);
	else if(colloc == 0x0B) 
	   return(keypad[rowloc][2]);
	else
	   return(keypad[rowloc][3]);
}
/*
char Check_Pad()
{
	char i, j, keyin;
	for (i = 0; i < 4; i++)
	{
		Keyboard_Data = 0xFF-(1 << (i+4));
		_delay_ms(10);
		keyin = Keyboard_PIN & 0x0F;
		if (keyin != 0x0F)
		{
			for (i = 0; i < 4; i++)
			{
				if (keyin == scan_code[j])
				{
					return ascii_code[j][i];
				}
			}
		}
	}
	return 0;
}
*/
// initialize timer, interrupt and variable
void PWM_init()
{
	TCCR1A = 0;
	TCCR1B = 0;
	// RESET l?i 2 thanh ghi
	// ??u ra PB2 là OUTPUT ( pin 10)
	
	TCCR1A |= (1 << WGM11);
	TCCR1B |= (1 << WGM12)|(1 << WGM13);
	// ch?n Fast PWM ch? ?? ch?n TOP_value t? do  ICR1
	TCCR1A |= (1 << COM1B1);
	// So sánh th??ng( none-inverting)
	TCCR1B |= (1 << CS10);
	// F_clock/1=16mhz
	//F_pwm=16mhz/(ICR1 + 1)
	ICR1 = 421;
	// xung r?ng c?a tràn sau 30000 P_clock
}

void Gui_Byte(unsigned char c)
{
	unsigned char i;
	for (i = 0; i < 8; i++)
	{
		if (c&0x80)
		{
			OCR1B = 210;
			_delay_ms(1);
			OCR1B = 0;
			_delay_ms(3);
		}
		else
		{
			OCR1B = 210;
			_delay_ms(3);
			OCR1B = 0;
			_delay_ms(1);
		}
		c <<= 1;
	}
}

void UART_Init()
{
	UBRRL = 102;
	UCSRB |= (1 << RXEN) | (1 << TXEN) | (1 << RXCIE);
	UCSRC |= (1 << UCSZ1) | (1 << UCSZ0);						//Baud = 9600, U2X = 0, F = 16MHz
}

void UART_Write_Chr(char c)
{
	while(bit_is_clear(UCSRA, UDRE));
	UDR = c;
}

void UART_Write_Str(char *str)
{
	unsigned char i = 0;
	while (str[i] != 0)
	{
		UART_Write_Chr(str[i]);
		i++;
	}
}
