#ifndef PORT_H_
#define PORT_H_

#define LCD_Data_Dir DDRB		/* Define LCD data port direction */
#define LCD_Command_Dir DDRC		/* Define LCD command port direction register */
#define LCD_Data_Port PORTB		/* Define LCD data port */
#define LCD_Command_Port PORTC		/* Define LCD data port */

#define RS 0				/* Define Register Select (data/command reg.)pin */
#define RW 1				/* Define Read/Write signal pin */
#define EN 2				/* Define Enable signal pin */

#endif