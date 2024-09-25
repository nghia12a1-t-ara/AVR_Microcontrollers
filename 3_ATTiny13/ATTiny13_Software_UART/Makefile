# Created: 19/08/2021 9:42:31 PM
# Author : Nghia Taarabt

MCU=attiny13
FUSE_L=0x6A
FUSE_H=0xFF
F_CPU=1200000
CC=avr-gcc
LD=avr-ld
OBJCOPY=avr-objcopy
SIZE=avr-size
AVRDUDE=avrdude
CFLAGS=-std=c99 -Wall -g -Os -mmcu=${MCU} -DF_CPU=${F_CPU} -I. -I.. -DUART_RX_ENABLED -DUART_TX_ENABLED -DUART_BAUDRATE=19200
TARGET=main

SRCS=ATTiny13_SW_UART_Example.c ../ATTiny13_Software_UART.c

all:
	${CC} ${CFLAGS} -o ${TARGET}.o ${SRCS}
	${LD} -o ${TARGET}.elf ${TARGET}.o
	${OBJCOPY} -j .text -j .data -O ihex ${TARGET}.o ${TARGET}.hex
	${SIZE} -C --mcu=${MCU} ${TARGET}.elf

flash:
	${AVRDUDE} -p ${MCU} -c usbasp -U flash:w:${TARGET}.hex:i -F -P usb

fuse:
	$(AVRDUDE) -p ${MCU} -c usbasp -U hfuse:w:${FUSE_H}:m -U lfuse:w:${FUSE_L}:m

clean:
	rm -f *.c~ *.o *.elf *.hex
