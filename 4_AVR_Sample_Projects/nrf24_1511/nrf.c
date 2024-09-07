#include <avr/io.h>
#include <util/delay.h>
#include <avr/interrupt.h>

#include "nrf.h"

#define BIT(x) (1 << (x))
#define SETBITS(x,y) ((x) |= (y))
#define CLEARBITS(x,y) ((x) &= (~(y)))
#define SETBIT(x,y) SETBITS((x), (BIT((y))))
#define CLEARBIT(x,y) CLEARBITS((x), (BIT((y))))

//CE = PB3, CSN = PB4

void Init_SPI()
{
	DDRB |= (1 << 3);  //chip enable
	DDRB |= (1 << 4);  //ss pin c?k?s
	DDRB |= (1 << 5);  //mosi pin cikis
	DDRB |= (1 << 7);  //sck pin ç?k??
	DDRB &= ~(1 << 6); //miso pin giri?
	SPCR |= (1 << SPE) | (1 << MSTR) | (1 << SPR0);  //enable spi as master
	SPCR &= ~(1 << SPI2X) & ~(1 << SPR1); //set clock rate but not too important
	PORTB |= (1 << 4); // SS high to start with CSN
	PORTB &= ~(1 << 3); //CE
}

unsigned char spi_tranceiver (unsigned char data)
{
	// Load data into the buffer
	SPDR = data;

	//Wait until transmission complete
	while(!(SPSR & (1<<SPIF)));   // Return received data

	return(SPDR);
}

unsigned char Read_Byte(unsigned char reg)
{
	_delay_ms(10);
	PORTB &= ~(1 << 4);
	spi_tranceiver(R_REGISTER+reg);
	_delay_ms(10);
	reg=spi_tranceiver(RF24_NOP);
	_delay_ms(10);
	PORTB |= (1 << 4);
	return reg;
}

void Write_byte(unsigned char reg, unsigned char data)
{
	_delay_ms(10);
	PORTB &= ~(1 << 4);
	_delay_ms(10);
	spi_tranceiver(W_REGISTER+reg);
	_delay_ms(10);
	spi_tranceiver(data);
	_delay_ms(10);
	PORTB |= (1 << 4);
}

void Init_nrf(void)
{
	_delay_ms(100);

	Write_byte(EN_AA, 0x01); //Enable auto acknowledgement Transmiter gets automatic response For data pipe 0

	Write_byte(EN_RXADDR, 0x01); //enable data pipe 0

	Write_byte(SETUP_AW, 0x03);  //adress width is 5 byte

	Write_byte(RF_CH, 0x01);  //2.401GHz

	Write_byte(RF_SETUP, 0x07);  // 1Mbps 00gain

	_delay_ms(10);
	PORTB &= ~(1 << 4);
	_delay_ms(10);
	spi_tranceiver(W_REGISTER + RX_ADDR_P0); //setup p0 pipe adress for receiveing
	_delay_ms(10);
	spi_tranceiver(0x01);
	_delay_ms(10);
	spi_tranceiver(0x02);
	_delay_ms(10);
	spi_tranceiver(0x03);
	_delay_ms(10);
	spi_tranceiver(0x04);
	_delay_ms(10);
	spi_tranceiver(0x05);
	_delay_ms(10);
	PORTB |= (1 << 4);

	_delay_ms(10);
	PORTB &= ~(1 << 4);
	_delay_ms(10);
	spi_tranceiver(W_REGISTER + TX_ADDR);  //transmitter adress
	_delay_ms(10);
	spi_tranceiver(0x01);
	_delay_ms(10); 
	spi_tranceiver(0x02);
	_delay_ms(10);
	spi_tranceiver(0x03);
	_delay_ms(10);
	spi_tranceiver(0x04);
	_delay_ms(10);
	spi_tranceiver(0x05);
	_delay_ms(10);
	PORTB |= (1 << 4);

	Write_byte(RX_PW_P0, 0x01); //only 1 byte for transceiving

	Write_byte(SETUP_RETR, 0x2F); //750us delay with 15 retries

	Write_byte(NRF_CONFIG, 0x1E); //boot up nrf as transmitter MAX_RETR interrupt disabled

	_delay_ms(100);
}

void Flush_tx(void)
{
	_delay_ms(10);
	PORTB &= ~(1 << 4);
	_delay_ms(10);
	spi_tranceiver(FLUSH_TX);
	_delay_ms(10);
	PORTB |= (1 << 4);
	_delay_ms(10);
}

void Flush_rx(void)
{
	_delay_ms(10);
	PORTB &= ~(1 << 4);
	_delay_ms(10);
	spi_tranceiver(FLUSH_RX);
	_delay_ms(10);
	PORTB |= (1 << 4);
	_delay_ms(10);
}

void transmit_data(unsigned char tdata)
{
	Flush_tx();
	Write_byte(W_TX_PAYLOAD, tdata);
	_delay_ms(10);
	PORTB |= (1 << 3);
	_delay_ms(20);
	PORTB &= ~(1 << 3);
	_delay_ms(10);
}

void receive_payload()
{
	SETBIT(PORTB, 3);	//CE IR_High = "Lyssnar"
	_delay_ms(1000);	//lyssnar i 1s och om mottaget går int0-interruptvektor igång
	CLEARBIT(PORTB, 3); //ce låg igen -sluta lyssna
}

void reset(void)
{
	_delay_ms(10);
	PORTB &= ~(1 << 4);
	_delay_ms(10);
	spi_tranceiver(NRF_STATUS);
	_delay_ms(10);
	spi_tranceiver(0x70);   //reset all IRQ after every succesfull transmit and receive
	_delay_ms(10);
	PORTB |= (1 << 4);
}



