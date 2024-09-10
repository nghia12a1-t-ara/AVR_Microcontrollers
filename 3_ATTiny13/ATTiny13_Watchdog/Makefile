# 
# ATTiny13_GPIO.c
#
# Created: 19/07/2021 8:28:53 PM
# Author : Nghia Taarabt

MCU=attiny13
FUSE_L=0x6A
FUSE_H=0xFF
F_CPU=1200000
CC=avr-gcc
LD=avr-ld
OBJCOPY=avr-objcopy
AVRDUDE=avrdude
CFLAGS=-std=c99 -Wall -g -Os -mmcu=${MCU} -DF_CPU=${F_CPU} -I.
TARGET=ATTiny13_Watchdog

SRCS = ATTiny13_Watchdog.c
	
all:
	${CC} ${CFLAGS} -o ${TARGET}.o ${SRCS}
	${LD} -o ${TARGET}.elf ${TARGET}.o
	${OBJCOPY} -j .text -j .data -O ihex ${TARGET}.o ${TARGET}.hex	

flash:
	${AVRDUDE} -p ${MCU} -c usbasp -B10 -U flash:w:${TARGET}.hex:i -F -P usb

fuse:
	$(AVRDUDE) -p ${MCU} -c usbasp -B10 -U hfuse:w:${FUSE_H}:m -U lfuse:w:${FUSE_L}:m
	
clean:
	rm -f *.c~ *.o *.elf *.hex
