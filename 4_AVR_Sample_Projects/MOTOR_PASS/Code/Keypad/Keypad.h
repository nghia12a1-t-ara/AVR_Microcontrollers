#ifndef  _KEYPAD_H_
#define  _KEYPAD_H_

#include <stdint.h>

#define PORT_KEYPAD      PORTB
#define PIN_KEYPAD       PINB 

/* Function Prototypes */
void Assign_Pass(uint8_t nguon[6], uint8_t dich[6]);
uint8_t keypass(void);
uint8_t check(uint8_t a[], uint8_t b[]);
void Enter_Pass(void);
void Change_Password(void);

#endif /* _KEYPAD_INCLUDED_ */

