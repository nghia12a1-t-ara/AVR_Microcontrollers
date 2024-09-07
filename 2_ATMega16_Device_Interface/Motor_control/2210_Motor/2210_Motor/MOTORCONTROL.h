#ifndef _MOTORCONTROL_H
#define _MOTORCONTROL_H

void PWM_Init(uint16_t);
void Left_Duty(uint16_t);
void Right_Duty(uint16_t);
void PWM_Start(void);
void Forward(uint16_t, uint16_t);
void Backward(uint16_t, uint16_t);
void Turnleft(uint16_t, uint16_t);
void TurnRight(uint16_t, uint16_t);
void Stop(void);
 
#endif