/*  
  ATmega16 ADC program
   http://www.electronicwings.com
*/

#define F_CPU 8000000UL 
#include <avr/io.h>
#include <util/delay.h>
#include <stdlib.h>
#include "LCD_16x2_H_file.h"

void ADC_Init()
{
	DDRA=0x0;			/* Make ADC port as input */
	ADCSRA = 0x87;		/*Enable ADC, fr/128  */
	ADMUX = 0x40;		/*Vref: Avcc, ADC channel: 0 */
	
}

int ADC_Read(char channel)
{
	int Ain,AinLow;
	
	ADMUX=ADMUX|(channel & 0x0f);		/* set input channel to read */

	ADCSRA |= (1<<ADSC);		/* start conversion */
	while((ADCSRA&(1<<ADIF))==0);	/*monitor end of conversion interrupt flag */
	
	_delay_us(10);
	AinLow = (int)ADCL;				/*read lower byte*/
	Ain = (int)ADCH*256;			/*read higher 2 bits, Multiply with weightage*/
	Ain = Ain + AinLow;				
	return(Ain);					/*return digital value*/
}

 
int main()
{
	char String[5];
	int value;

	ADC_Init();
	LCD_Init();						/* initialization of LCD */
	LCD_String("ADC value");		/* write string on 1st line of LCD */

	while(1)
	{
	
		LCD_Command(0xc4);						/* LCD16x2 cursor position */
		value=ADC_Read(0);						/* read ADC channel 0 */
		itoa(value,String,10);					/* int. to string conversion */ 
		LCD_String(String);						
		LCD_String("  ");			
	}
	return 0;
}
 
