/*
 * SPI.c
 *
 * Created: 03/04/2020 10:30:55 PM
 * Author : Admin
 */ 
#define  F_CPU 16000000UL
#define cbi(port, bit)	(port) &= ~(1 << (bit))
#define sbi(port, bit)	(port) |= (1 << (bit))

#define SPI		PORTB
#define	SCK		7
#define MISO	6
#define MOSI	5
#define SS		4

#include <avr/io.h>
#include <avr/sfr_defs.h>
#include <avr/interrupt.h>

#include "SPI.h"

int main(void)
{
    /* Replace with your application code */
    while (1) 
    {
    }
}

