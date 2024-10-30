/**
 * I2C.c
 * 
 * Created: 7/17/2024 9:08:15 PM
 * Author : Nghia Taarabt
 */
#include "I2C.h"

/* Initialize I2C as master */
void I2C_Init(void)
{
    TWBR = ((F_CPU / SCL_FREQ) - 16) / 2;
    TWSR = 0x00; // Prescaler set to 1
}

/* Start I2C transmission */
void I2C_Start(void)
{
    TWCR = (1 << TWINT) | (1 << TWSTA) | (1 << TWEN);
    while (!(TWCR & (1 << TWINT)));
}

/* Stop I2C transmission */
void I2C_Stop(void)
{
    TWCR = (1 << TWINT) | (1 << TWSTO) | (1 << TWEN);
}

/* Write a byte to I2C bus */
void I2C_WriteByte(uint8_t data)
{
    TWDR = data;
    TWCR = (1 << TWINT) | (1 << TWEN);
    while (!(TWCR & (1 << TWINT)));
}

/* Read a byte from I2C bus with ACK */
uint8_t I2C_Read_ACK(void)
{
    TWCR = (1 << TWINT) | (1 << TWEN) | (1 << TWEA);
    while (!(TWCR & (1 << TWINT)));
    return TWDR;
}

/* Read a byte from I2C bus with NACK */
uint8_t I2C_Read_NACK(void)
{
    TWCR = (1 << TWINT) | (1 << TWEN);
    while (!(TWCR & (1 << TWINT)));
    return TWDR;
}
