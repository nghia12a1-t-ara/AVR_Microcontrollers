CC 		:=	"C://Program Files (x86)//Atmel//Studio//7.0//toolchain//avr8//avr8-gnu-toolchain//bin//avr-gcc.exe"
OBJ_COPY:=	"C://Program Files (x86)//Atmel//Studio//7.0//toolchain//avr8//avr8-gnu-toolchain//bin//avr-objcopy"
CC_OPTS	:=	-x c -funsigned-char -funsigned-bitfields -DDEBUG -O1 -ffunction-sections -fdata-sections -fpack-struct -fshort-enums -g2 -Wall -mmcu=atmega16 -c -std=gnu99 -MD -MP -MF "$(@:%.o=%.d)" -MT"$(@:%.o=%.d)" -MT"$(@:%.o=%.o)" \
			-I"C:\Program Files (x86)\Atmel\Studio\7.0\Packs\atmel\ATmega_DFP\1.3.300\include" \
			-B "C:\Program Files (x86)\Atmel\Studio\7.0\Packs\atmel\ATmega_DFP\1.3.300\gcc\dev\atmega16"

LD_OPTS	:=	-Wl,-Map="test.map" -Wl,--start-group -Wl,-lm  -Wl,--end-group -Wl,--gc-sections -mmcu=atmega16 \
			-B "C:\Program Files (x86)\Atmel\Studio\7.0\Packs\atmel\ATmega_DFP\1.3.300\gcc\dev\atmega16"

all:main.o test.elf

main.o:main.c
	$(CC) $(CC_OPTS) -o $@ $^
startup.o:startup.c
	$(CC) $(CC_OPTS) -o $@ $^
test.elf:main.o startup.o
	$(CC) $(LD_OPTS) -o $@ $^
	$(OBJ_COPY) -O ihex -R .eeprom -R .fuse -R .lock -R .signature -R .user_signatures  "test.elf" "test.hex"

clean:
	rm -rf *.o *.elf