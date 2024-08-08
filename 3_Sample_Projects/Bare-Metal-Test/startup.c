#include <stdint.h>

// #define SRAM_START	0x20000000U

typedef unsigned short uint16;
typedef unsigned char uint8; 

// extern uint16 _etext;
extern uint16 _sdata;
extern uint16 _edata;
extern uint16 _la_data;

extern uint16 _sbss;
extern uint16 _ebss;

/* function prototypes for main function */
void main(void);

/* function prototypes of STM32F407x system exception and IRQ handlers */
void Reset_Handler(void);
void Default_Handler(void);

uint16 vectors[] __attribute__((section(".isr_vector"))) = {
	(uint16)&Reset_Handler,
	(uint16)&Default_Handler
	/*....*/
};

void Reset_Handler()
{
	/* Copy .data section to SRAM */
	// uint16 size = (uint16)&_edata - (uint16)&_sdata;
	
	// uint8 *pDst = (uint8*)&_sdata;		// SRAM
	// uint8 *pSrc = (uint8*)&_la_data;	// FLASH
	
	// for(uint16 i = 0; i < size; i++)
	// {
		// *pDst++ = *pSrc++;
	// }
	
	// /* Init the .bss section to zero in SRAM */
	// size = (uint16)&_ebss - (uint16)&_sbss;
	// pDst = (uint8*)&_sbss;
	
	// for(uint16 i = 0; i < size; i++)
	// {
		// *pDst++ = 0;
	// }
	
	/* Call main() function */
	main();
}

void Default_Handler(void)
{
	while(1);
}
