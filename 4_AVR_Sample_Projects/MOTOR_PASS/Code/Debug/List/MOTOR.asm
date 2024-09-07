
;CodeVisionAVR C Compiler V3.32 Evaluation
;(C) Copyright 1998-2017 Pavel Haiduc, HP InfoTech s.r.l.
;http://www.hpinfotech.com

;Build configuration    : Debug
;Chip type              : ATmega16
;Program type           : Application
;Clock frequency        : 8.000000 MHz
;Memory model           : Small
;Optimize for           : Size
;(s)printf features     : int, width
;(s)scanf features      : int, width
;External RAM size      : 0
;Data Stack size        : 256 byte(s)
;Heap size              : 0 byte(s)
;Promote 'char' to 'int': Yes
;'char' is unsigned     : Yes
;8 bit enums            : Yes
;Global 'const' stored in FLASH: Yes
;Enhanced function parameter passing: Mode 2
;Enhanced core instructions: On
;Automatic register allocation for global variables: On
;Smart register allocation: On

	#define _MODEL_SMALL_

	#pragma AVRPART ADMIN PART_NAME ATmega16
	#pragma AVRPART MEMORY PROG_FLASH 16384
	#pragma AVRPART MEMORY EEPROM 512
	#pragma AVRPART MEMORY INT_SRAM SIZE 1024
	#pragma AVRPART MEMORY INT_SRAM START_ADDR 0x60

	#define CALL_SUPPORTED 1

	.LISTMAC
	.EQU UDRE=0x5
	.EQU RXC=0x7
	.EQU USR=0xB
	.EQU UDR=0xC
	.EQU SPSR=0xE
	.EQU SPDR=0xF
	.EQU EERE=0x0
	.EQU EEWE=0x1
	.EQU EEMWE=0x2
	.EQU EECR=0x1C
	.EQU EEDR=0x1D
	.EQU EEARL=0x1E
	.EQU EEARH=0x1F
	.EQU WDTCR=0x21
	.EQU MCUCR=0x35
	.EQU GICR=0x3B
	.EQU SPL=0x3D
	.EQU SPH=0x3E
	.EQU SREG=0x3F

	.DEF R0X0=R0
	.DEF R0X1=R1
	.DEF R0X2=R2
	.DEF R0X3=R3
	.DEF R0X4=R4
	.DEF R0X5=R5
	.DEF R0X6=R6
	.DEF R0X7=R7
	.DEF R0X8=R8
	.DEF R0X9=R9
	.DEF R0XA=R10
	.DEF R0XB=R11
	.DEF R0XC=R12
	.DEF R0XD=R13
	.DEF R0XE=R14
	.DEF R0XF=R15
	.DEF R0X10=R16
	.DEF R0X11=R17
	.DEF R0X12=R18
	.DEF R0X13=R19
	.DEF R0X14=R20
	.DEF R0X15=R21
	.DEF R0X16=R22
	.DEF R0X17=R23
	.DEF R0X18=R24
	.DEF R0X19=R25
	.DEF R0X1A=R26
	.DEF R0X1B=R27
	.DEF R0X1C=R28
	.DEF R0X1D=R29
	.DEF R0X1E=R30
	.DEF R0X1F=R31

	.EQU __SRAM_START=0x0060
	.EQU __SRAM_END=0x045F
	.EQU __DSTACK_SIZE=0x0100
	.EQU __HEAP_SIZE=0x0000
	.EQU __CLEAR_SRAM_SIZE=__SRAM_END-__SRAM_START+1

	.MACRO __CPD1N
	CPI  R30,LOW(@0)
	LDI  R26,HIGH(@0)
	CPC  R31,R26
	LDI  R26,BYTE3(@0)
	CPC  R22,R26
	LDI  R26,BYTE4(@0)
	CPC  R23,R26
	.ENDM

	.MACRO __CPD2N
	CPI  R26,LOW(@0)
	LDI  R30,HIGH(@0)
	CPC  R27,R30
	LDI  R30,BYTE3(@0)
	CPC  R24,R30
	LDI  R30,BYTE4(@0)
	CPC  R25,R30
	.ENDM

	.MACRO __CPWRR
	CP   R@0,R@2
	CPC  R@1,R@3
	.ENDM

	.MACRO __CPWRN
	CPI  R@0,LOW(@2)
	LDI  R30,HIGH(@2)
	CPC  R@1,R30
	.ENDM

	.MACRO __ADDB1MN
	SUBI R30,LOW(-@0-(@1))
	.ENDM

	.MACRO __ADDB2MN
	SUBI R26,LOW(-@0-(@1))
	.ENDM

	.MACRO __ADDW1MN
	SUBI R30,LOW(-@0-(@1))
	SBCI R31,HIGH(-@0-(@1))
	.ENDM

	.MACRO __ADDW2MN
	SUBI R26,LOW(-@0-(@1))
	SBCI R27,HIGH(-@0-(@1))
	.ENDM

	.MACRO __ADDW1FN
	SUBI R30,LOW(-2*@0-(@1))
	SBCI R31,HIGH(-2*@0-(@1))
	.ENDM

	.MACRO __ADDD1FN
	SUBI R30,LOW(-2*@0-(@1))
	SBCI R31,HIGH(-2*@0-(@1))
	SBCI R22,BYTE3(-2*@0-(@1))
	.ENDM

	.MACRO __ADDD1N
	SUBI R30,LOW(-@0)
	SBCI R31,HIGH(-@0)
	SBCI R22,BYTE3(-@0)
	SBCI R23,BYTE4(-@0)
	.ENDM

	.MACRO __ADDD2N
	SUBI R26,LOW(-@0)
	SBCI R27,HIGH(-@0)
	SBCI R24,BYTE3(-@0)
	SBCI R25,BYTE4(-@0)
	.ENDM

	.MACRO __SUBD1N
	SUBI R30,LOW(@0)
	SBCI R31,HIGH(@0)
	SBCI R22,BYTE3(@0)
	SBCI R23,BYTE4(@0)
	.ENDM

	.MACRO __SUBD2N
	SUBI R26,LOW(@0)
	SBCI R27,HIGH(@0)
	SBCI R24,BYTE3(@0)
	SBCI R25,BYTE4(@0)
	.ENDM

	.MACRO __ANDBMNN
	LDS  R30,@0+(@1)
	ANDI R30,LOW(@2)
	STS  @0+(@1),R30
	.ENDM

	.MACRO __ANDWMNN
	LDS  R30,@0+(@1)
	ANDI R30,LOW(@2)
	STS  @0+(@1),R30
	LDS  R30,@0+(@1)+1
	ANDI R30,HIGH(@2)
	STS  @0+(@1)+1,R30
	.ENDM

	.MACRO __ANDD1N
	ANDI R30,LOW(@0)
	ANDI R31,HIGH(@0)
	ANDI R22,BYTE3(@0)
	ANDI R23,BYTE4(@0)
	.ENDM

	.MACRO __ANDD2N
	ANDI R26,LOW(@0)
	ANDI R27,HIGH(@0)
	ANDI R24,BYTE3(@0)
	ANDI R25,BYTE4(@0)
	.ENDM

	.MACRO __ORBMNN
	LDS  R30,@0+(@1)
	ORI  R30,LOW(@2)
	STS  @0+(@1),R30
	.ENDM

	.MACRO __ORWMNN
	LDS  R30,@0+(@1)
	ORI  R30,LOW(@2)
	STS  @0+(@1),R30
	LDS  R30,@0+(@1)+1
	ORI  R30,HIGH(@2)
	STS  @0+(@1)+1,R30
	.ENDM

	.MACRO __ORD1N
	ORI  R30,LOW(@0)
	ORI  R31,HIGH(@0)
	ORI  R22,BYTE3(@0)
	ORI  R23,BYTE4(@0)
	.ENDM

	.MACRO __ORD2N
	ORI  R26,LOW(@0)
	ORI  R27,HIGH(@0)
	ORI  R24,BYTE3(@0)
	ORI  R25,BYTE4(@0)
	.ENDM

	.MACRO __DELAY_USB
	LDI  R24,LOW(@0)
__DELAY_USB_LOOP:
	DEC  R24
	BRNE __DELAY_USB_LOOP
	.ENDM

	.MACRO __DELAY_USW
	LDI  R24,LOW(@0)
	LDI  R25,HIGH(@0)
__DELAY_USW_LOOP:
	SBIW R24,1
	BRNE __DELAY_USW_LOOP
	.ENDM

	.MACRO __GETD1S
	LDD  R30,Y+@0
	LDD  R31,Y+@0+1
	LDD  R22,Y+@0+2
	LDD  R23,Y+@0+3
	.ENDM

	.MACRO __GETD2S
	LDD  R26,Y+@0
	LDD  R27,Y+@0+1
	LDD  R24,Y+@0+2
	LDD  R25,Y+@0+3
	.ENDM

	.MACRO __PUTD1S
	STD  Y+@0,R30
	STD  Y+@0+1,R31
	STD  Y+@0+2,R22
	STD  Y+@0+3,R23
	.ENDM

	.MACRO __PUTD2S
	STD  Y+@0,R26
	STD  Y+@0+1,R27
	STD  Y+@0+2,R24
	STD  Y+@0+3,R25
	.ENDM

	.MACRO __PUTDZ2
	STD  Z+@0,R26
	STD  Z+@0+1,R27
	STD  Z+@0+2,R24
	STD  Z+@0+3,R25
	.ENDM

	.MACRO __CLRD1S
	STD  Y+@0,R30
	STD  Y+@0+1,R30
	STD  Y+@0+2,R30
	STD  Y+@0+3,R30
	.ENDM

	.MACRO __POINTB1MN
	LDI  R30,LOW(@0+(@1))
	.ENDM

	.MACRO __POINTW1MN
	LDI  R30,LOW(@0+(@1))
	LDI  R31,HIGH(@0+(@1))
	.ENDM

	.MACRO __POINTD1M
	LDI  R30,LOW(@0)
	LDI  R31,HIGH(@0)
	LDI  R22,BYTE3(@0)
	LDI  R23,BYTE4(@0)
	.ENDM

	.MACRO __POINTW1FN
	LDI  R30,LOW(2*@0+(@1))
	LDI  R31,HIGH(2*@0+(@1))
	.ENDM

	.MACRO __POINTD1FN
	LDI  R30,LOW(2*@0+(@1))
	LDI  R31,HIGH(2*@0+(@1))
	LDI  R22,BYTE3(2*@0+(@1))
	LDI  R23,BYTE4(2*@0+(@1))
	.ENDM

	.MACRO __POINTB2MN
	LDI  R26,LOW(@0+(@1))
	.ENDM

	.MACRO __POINTW2MN
	LDI  R26,LOW(@0+(@1))
	LDI  R27,HIGH(@0+(@1))
	.ENDM

	.MACRO __POINTD2M
	LDI  R26,LOW(@0)
	LDI  R27,HIGH(@0)
	LDI  R24,BYTE3(@0)
	LDI  R25,BYTE4(@0)
	.ENDM

	.MACRO __POINTW2FN
	LDI  R26,LOW(2*@0+(@1))
	LDI  R27,HIGH(2*@0+(@1))
	.ENDM

	.MACRO __POINTD2FN
	LDI  R26,LOW(2*@0+(@1))
	LDI  R27,HIGH(2*@0+(@1))
	LDI  R24,BYTE3(2*@0+(@1))
	LDI  R25,BYTE4(2*@0+(@1))
	.ENDM

	.MACRO __POINTBRM
	LDI  R@0,LOW(@1)
	.ENDM

	.MACRO __POINTWRM
	LDI  R@0,LOW(@2)
	LDI  R@1,HIGH(@2)
	.ENDM

	.MACRO __POINTBRMN
	LDI  R@0,LOW(@1+(@2))
	.ENDM

	.MACRO __POINTWRMN
	LDI  R@0,LOW(@2+(@3))
	LDI  R@1,HIGH(@2+(@3))
	.ENDM

	.MACRO __POINTWRFN
	LDI  R@0,LOW(@2*2+(@3))
	LDI  R@1,HIGH(@2*2+(@3))
	.ENDM

	.MACRO __GETD1N
	LDI  R30,LOW(@0)
	LDI  R31,HIGH(@0)
	LDI  R22,BYTE3(@0)
	LDI  R23,BYTE4(@0)
	.ENDM

	.MACRO __GETD2N
	LDI  R26,LOW(@0)
	LDI  R27,HIGH(@0)
	LDI  R24,BYTE3(@0)
	LDI  R25,BYTE4(@0)
	.ENDM

	.MACRO __GETB1MN
	LDS  R30,@0+(@1)
	.ENDM

	.MACRO __GETB1HMN
	LDS  R31,@0+(@1)
	.ENDM

	.MACRO __GETW1MN
	LDS  R30,@0+(@1)
	LDS  R31,@0+(@1)+1
	.ENDM

	.MACRO __GETD1MN
	LDS  R30,@0+(@1)
	LDS  R31,@0+(@1)+1
	LDS  R22,@0+(@1)+2
	LDS  R23,@0+(@1)+3
	.ENDM

	.MACRO __GETBRMN
	LDS  R@0,@1+(@2)
	.ENDM

	.MACRO __GETWRMN
	LDS  R@0,@2+(@3)
	LDS  R@1,@2+(@3)+1
	.ENDM

	.MACRO __GETWRZ
	LDD  R@0,Z+@2
	LDD  R@1,Z+@2+1
	.ENDM

	.MACRO __GETD2Z
	LDD  R26,Z+@0
	LDD  R27,Z+@0+1
	LDD  R24,Z+@0+2
	LDD  R25,Z+@0+3
	.ENDM

	.MACRO __GETB2MN
	LDS  R26,@0+(@1)
	.ENDM

	.MACRO __GETW2MN
	LDS  R26,@0+(@1)
	LDS  R27,@0+(@1)+1
	.ENDM

	.MACRO __GETD2MN
	LDS  R26,@0+(@1)
	LDS  R27,@0+(@1)+1
	LDS  R24,@0+(@1)+2
	LDS  R25,@0+(@1)+3
	.ENDM

	.MACRO __PUTB1MN
	STS  @0+(@1),R30
	.ENDM

	.MACRO __PUTW1MN
	STS  @0+(@1),R30
	STS  @0+(@1)+1,R31
	.ENDM

	.MACRO __PUTD1MN
	STS  @0+(@1),R30
	STS  @0+(@1)+1,R31
	STS  @0+(@1)+2,R22
	STS  @0+(@1)+3,R23
	.ENDM

	.MACRO __PUTB1EN
	LDI  R26,LOW(@0+(@1))
	LDI  R27,HIGH(@0+(@1))
	CALL __EEPROMWRB
	.ENDM

	.MACRO __PUTW1EN
	LDI  R26,LOW(@0+(@1))
	LDI  R27,HIGH(@0+(@1))
	CALL __EEPROMWRW
	.ENDM

	.MACRO __PUTD1EN
	LDI  R26,LOW(@0+(@1))
	LDI  R27,HIGH(@0+(@1))
	CALL __EEPROMWRD
	.ENDM

	.MACRO __PUTBR0MN
	STS  @0+(@1),R0
	.ENDM

	.MACRO __PUTBMRN
	STS  @0+(@1),R@2
	.ENDM

	.MACRO __PUTWMRN
	STS  @0+(@1),R@2
	STS  @0+(@1)+1,R@3
	.ENDM

	.MACRO __PUTBZR
	STD  Z+@1,R@0
	.ENDM

	.MACRO __PUTWZR
	STD  Z+@2,R@0
	STD  Z+@2+1,R@1
	.ENDM

	.MACRO __GETW1R
	MOV  R30,R@0
	MOV  R31,R@1
	.ENDM

	.MACRO __GETW2R
	MOV  R26,R@0
	MOV  R27,R@1
	.ENDM

	.MACRO __GETWRN
	LDI  R@0,LOW(@2)
	LDI  R@1,HIGH(@2)
	.ENDM

	.MACRO __PUTW1R
	MOV  R@0,R30
	MOV  R@1,R31
	.ENDM

	.MACRO __PUTW2R
	MOV  R@0,R26
	MOV  R@1,R27
	.ENDM

	.MACRO __ADDWRN
	SUBI R@0,LOW(-@2)
	SBCI R@1,HIGH(-@2)
	.ENDM

	.MACRO __ADDWRR
	ADD  R@0,R@2
	ADC  R@1,R@3
	.ENDM

	.MACRO __SUBWRN
	SUBI R@0,LOW(@2)
	SBCI R@1,HIGH(@2)
	.ENDM

	.MACRO __SUBWRR
	SUB  R@0,R@2
	SBC  R@1,R@3
	.ENDM

	.MACRO __ANDWRN
	ANDI R@0,LOW(@2)
	ANDI R@1,HIGH(@2)
	.ENDM

	.MACRO __ANDWRR
	AND  R@0,R@2
	AND  R@1,R@3
	.ENDM

	.MACRO __ORWRN
	ORI  R@0,LOW(@2)
	ORI  R@1,HIGH(@2)
	.ENDM

	.MACRO __ORWRR
	OR   R@0,R@2
	OR   R@1,R@3
	.ENDM

	.MACRO __EORWRR
	EOR  R@0,R@2
	EOR  R@1,R@3
	.ENDM

	.MACRO __GETWRS
	LDD  R@0,Y+@2
	LDD  R@1,Y+@2+1
	.ENDM

	.MACRO __PUTBSR
	STD  Y+@1,R@0
	.ENDM

	.MACRO __PUTWSR
	STD  Y+@2,R@0
	STD  Y+@2+1,R@1
	.ENDM

	.MACRO __MOVEWRR
	MOV  R@0,R@2
	MOV  R@1,R@3
	.ENDM

	.MACRO __INWR
	IN   R@0,@2
	IN   R@1,@2+1
	.ENDM

	.MACRO __OUTWR
	OUT  @2+1,R@1
	OUT  @2,R@0
	.ENDM

	.MACRO __CALL1MN
	LDS  R30,@0+(@1)
	LDS  R31,@0+(@1)+1
	ICALL
	.ENDM

	.MACRO __CALL1FN
	LDI  R30,LOW(2*@0+(@1))
	LDI  R31,HIGH(2*@0+(@1))
	CALL __GETW1PF
	ICALL
	.ENDM

	.MACRO __CALL2EN
	PUSH R26
	PUSH R27
	LDI  R26,LOW(@0+(@1))
	LDI  R27,HIGH(@0+(@1))
	CALL __EEPROMRDW
	POP  R27
	POP  R26
	ICALL
	.ENDM

	.MACRO __CALL2EX
	SUBI R26,LOW(-@0)
	SBCI R27,HIGH(-@0)
	CALL __EEPROMRDD
	ICALL
	.ENDM

	.MACRO __GETW1STACK
	IN   R30,SPL
	IN   R31,SPH
	ADIW R30,@0+1
	LD   R0,Z+
	LD   R31,Z
	MOV  R30,R0
	.ENDM

	.MACRO __GETD1STACK
	IN   R30,SPL
	IN   R31,SPH
	ADIW R30,@0+1
	LD   R0,Z+
	LD   R1,Z+
	LD   R22,Z
	MOVW R30,R0
	.ENDM

	.MACRO __NBST
	BST  R@0,@1
	IN   R30,SREG
	LDI  R31,0x40
	EOR  R30,R31
	OUT  SREG,R30
	.ENDM


	.MACRO __PUTB1SN
	LDD  R26,Y+@0
	LDD  R27,Y+@0+1
	SUBI R26,LOW(-@1)
	SBCI R27,HIGH(-@1)
	ST   X,R30
	.ENDM

	.MACRO __PUTW1SN
	LDD  R26,Y+@0
	LDD  R27,Y+@0+1
	SUBI R26,LOW(-@1)
	SBCI R27,HIGH(-@1)
	ST   X+,R30
	ST   X,R31
	.ENDM

	.MACRO __PUTD1SN
	LDD  R26,Y+@0
	LDD  R27,Y+@0+1
	SUBI R26,LOW(-@1)
	SBCI R27,HIGH(-@1)
	CALL __PUTDP1
	.ENDM

	.MACRO __PUTB1SNS
	LDD  R26,Y+@0
	LDD  R27,Y+@0+1
	ADIW R26,@1
	ST   X,R30
	.ENDM

	.MACRO __PUTW1SNS
	LDD  R26,Y+@0
	LDD  R27,Y+@0+1
	ADIW R26,@1
	ST   X+,R30
	ST   X,R31
	.ENDM

	.MACRO __PUTD1SNS
	LDD  R26,Y+@0
	LDD  R27,Y+@0+1
	ADIW R26,@1
	CALL __PUTDP1
	.ENDM

	.MACRO __PUTB1PMN
	LDS  R26,@0
	LDS  R27,@0+1
	SUBI R26,LOW(-@1)
	SBCI R27,HIGH(-@1)
	ST   X,R30
	.ENDM

	.MACRO __PUTW1PMN
	LDS  R26,@0
	LDS  R27,@0+1
	SUBI R26,LOW(-@1)
	SBCI R27,HIGH(-@1)
	ST   X+,R30
	ST   X,R31
	.ENDM

	.MACRO __PUTD1PMN
	LDS  R26,@0
	LDS  R27,@0+1
	SUBI R26,LOW(-@1)
	SBCI R27,HIGH(-@1)
	CALL __PUTDP1
	.ENDM

	.MACRO __PUTB1PMNS
	LDS  R26,@0
	LDS  R27,@0+1
	ADIW R26,@1
	ST   X,R30
	.ENDM

	.MACRO __PUTW1PMNS
	LDS  R26,@0
	LDS  R27,@0+1
	ADIW R26,@1
	ST   X+,R30
	ST   X,R31
	.ENDM

	.MACRO __PUTD1PMNS
	LDS  R26,@0
	LDS  R27,@0+1
	ADIW R26,@1
	CALL __PUTDP1
	.ENDM

	.MACRO __PUTB1RN
	MOVW R26,R@0
	SUBI R26,LOW(-@1)
	SBCI R27,HIGH(-@1)
	ST   X,R30
	.ENDM

	.MACRO __PUTW1RN
	MOVW R26,R@0
	SUBI R26,LOW(-@1)
	SBCI R27,HIGH(-@1)
	ST   X+,R30
	ST   X,R31
	.ENDM

	.MACRO __PUTD1RN
	MOVW R26,R@0
	SUBI R26,LOW(-@1)
	SBCI R27,HIGH(-@1)
	CALL __PUTDP1
	.ENDM

	.MACRO __PUTB1RNS
	MOVW R26,R@0
	ADIW R26,@1
	ST   X,R30
	.ENDM

	.MACRO __PUTW1RNS
	MOVW R26,R@0
	ADIW R26,@1
	ST   X+,R30
	ST   X,R31
	.ENDM

	.MACRO __PUTD1RNS
	MOVW R26,R@0
	ADIW R26,@1
	CALL __PUTDP1
	.ENDM

	.MACRO __PUTB1RON
	MOV  R26,R@0
	MOV  R27,R@1
	SUBI R26,LOW(-@2)
	SBCI R27,HIGH(-@2)
	ST   X,R30
	.ENDM

	.MACRO __PUTW1RON
	MOV  R26,R@0
	MOV  R27,R@1
	SUBI R26,LOW(-@2)
	SBCI R27,HIGH(-@2)
	ST   X+,R30
	ST   X,R31
	.ENDM

	.MACRO __PUTD1RON
	MOV  R26,R@0
	MOV  R27,R@1
	SUBI R26,LOW(-@2)
	SBCI R27,HIGH(-@2)
	CALL __PUTDP1
	.ENDM

	.MACRO __PUTB1RONS
	MOV  R26,R@0
	MOV  R27,R@1
	ADIW R26,@2
	ST   X,R30
	.ENDM

	.MACRO __PUTW1RONS
	MOV  R26,R@0
	MOV  R27,R@1
	ADIW R26,@2
	ST   X+,R30
	ST   X,R31
	.ENDM

	.MACRO __PUTD1RONS
	MOV  R26,R@0
	MOV  R27,R@1
	ADIW R26,@2
	CALL __PUTDP1
	.ENDM


	.MACRO __GETB1SX
	MOVW R30,R28
	SUBI R30,LOW(-@0)
	SBCI R31,HIGH(-@0)
	LD   R30,Z
	.ENDM

	.MACRO __GETB1HSX
	MOVW R30,R28
	SUBI R30,LOW(-@0)
	SBCI R31,HIGH(-@0)
	LD   R31,Z
	.ENDM

	.MACRO __GETW1SX
	MOVW R30,R28
	SUBI R30,LOW(-@0)
	SBCI R31,HIGH(-@0)
	LD   R0,Z+
	LD   R31,Z
	MOV  R30,R0
	.ENDM

	.MACRO __GETD1SX
	MOVW R30,R28
	SUBI R30,LOW(-@0)
	SBCI R31,HIGH(-@0)
	LD   R0,Z+
	LD   R1,Z+
	LD   R22,Z+
	LD   R23,Z
	MOVW R30,R0
	.ENDM

	.MACRO __GETB2SX
	MOVW R26,R28
	SUBI R26,LOW(-@0)
	SBCI R27,HIGH(-@0)
	LD   R26,X
	.ENDM

	.MACRO __GETW2SX
	MOVW R26,R28
	SUBI R26,LOW(-@0)
	SBCI R27,HIGH(-@0)
	LD   R0,X+
	LD   R27,X
	MOV  R26,R0
	.ENDM

	.MACRO __GETD2SX
	MOVW R26,R28
	SUBI R26,LOW(-@0)
	SBCI R27,HIGH(-@0)
	LD   R0,X+
	LD   R1,X+
	LD   R24,X+
	LD   R25,X
	MOVW R26,R0
	.ENDM

	.MACRO __GETBRSX
	MOVW R30,R28
	SUBI R30,LOW(-@1)
	SBCI R31,HIGH(-@1)
	LD   R@0,Z
	.ENDM

	.MACRO __GETWRSX
	MOVW R30,R28
	SUBI R30,LOW(-@2)
	SBCI R31,HIGH(-@2)
	LD   R@0,Z+
	LD   R@1,Z
	.ENDM

	.MACRO __GETBRSX2
	MOVW R26,R28
	SUBI R26,LOW(-@1)
	SBCI R27,HIGH(-@1)
	LD   R@0,X
	.ENDM

	.MACRO __GETWRSX2
	MOVW R26,R28
	SUBI R26,LOW(-@2)
	SBCI R27,HIGH(-@2)
	LD   R@0,X+
	LD   R@1,X
	.ENDM

	.MACRO __LSLW8SX
	MOVW R30,R28
	SUBI R30,LOW(-@0)
	SBCI R31,HIGH(-@0)
	LD   R31,Z
	CLR  R30
	.ENDM

	.MACRO __PUTB1SX
	MOVW R26,R28
	SUBI R26,LOW(-@0)
	SBCI R27,HIGH(-@0)
	ST   X,R30
	.ENDM

	.MACRO __PUTW1SX
	MOVW R26,R28
	SUBI R26,LOW(-@0)
	SBCI R27,HIGH(-@0)
	ST   X+,R30
	ST   X,R31
	.ENDM

	.MACRO __PUTD1SX
	MOVW R26,R28
	SUBI R26,LOW(-@0)
	SBCI R27,HIGH(-@0)
	ST   X+,R30
	ST   X+,R31
	ST   X+,R22
	ST   X,R23
	.ENDM

	.MACRO __CLRW1SX
	MOVW R26,R28
	SUBI R26,LOW(-@0)
	SBCI R27,HIGH(-@0)
	ST   X+,R30
	ST   X,R30
	.ENDM

	.MACRO __CLRD1SX
	MOVW R26,R28
	SUBI R26,LOW(-@0)
	SBCI R27,HIGH(-@0)
	ST   X+,R30
	ST   X+,R30
	ST   X+,R30
	ST   X,R30
	.ENDM

	.MACRO __PUTB2SX
	MOVW R30,R28
	SUBI R30,LOW(-@0)
	SBCI R31,HIGH(-@0)
	ST   Z,R26
	.ENDM

	.MACRO __PUTW2SX
	MOVW R30,R28
	SUBI R30,LOW(-@0)
	SBCI R31,HIGH(-@0)
	ST   Z+,R26
	ST   Z,R27
	.ENDM

	.MACRO __PUTD2SX
	MOVW R30,R28
	SUBI R30,LOW(-@0)
	SBCI R31,HIGH(-@0)
	ST   Z+,R26
	ST   Z+,R27
	ST   Z+,R24
	ST   Z,R25
	.ENDM

	.MACRO __PUTBSRX
	MOVW R30,R28
	SUBI R30,LOW(-@1)
	SBCI R31,HIGH(-@1)
	ST   Z,R@0
	.ENDM

	.MACRO __PUTWSRX
	MOVW R30,R28
	SUBI R30,LOW(-@2)
	SBCI R31,HIGH(-@2)
	ST   Z+,R@0
	ST   Z,R@1
	.ENDM

	.MACRO __PUTB1SNX
	MOVW R26,R28
	SUBI R26,LOW(-@0)
	SBCI R27,HIGH(-@0)
	LD   R0,X+
	LD   R27,X
	MOV  R26,R0
	SUBI R26,LOW(-@1)
	SBCI R27,HIGH(-@1)
	ST   X,R30
	.ENDM

	.MACRO __PUTW1SNX
	MOVW R26,R28
	SUBI R26,LOW(-@0)
	SBCI R27,HIGH(-@0)
	LD   R0,X+
	LD   R27,X
	MOV  R26,R0
	SUBI R26,LOW(-@1)
	SBCI R27,HIGH(-@1)
	ST   X+,R30
	ST   X,R31
	.ENDM

	.MACRO __PUTD1SNX
	MOVW R26,R28
	SUBI R26,LOW(-@0)
	SBCI R27,HIGH(-@0)
	LD   R0,X+
	LD   R27,X
	MOV  R26,R0
	SUBI R26,LOW(-@1)
	SBCI R27,HIGH(-@1)
	ST   X+,R30
	ST   X+,R31
	ST   X+,R22
	ST   X,R23
	.ENDM

	.MACRO __MULBRR
	MULS R@0,R@1
	MOVW R30,R0
	.ENDM

	.MACRO __MULBRRU
	MUL  R@0,R@1
	MOVW R30,R0
	.ENDM

	.MACRO __MULBRR0
	MULS R@0,R@1
	.ENDM

	.MACRO __MULBRRU0
	MUL  R@0,R@1
	.ENDM

	.MACRO __MULBNWRU
	LDI  R26,@2
	MUL  R26,R@0
	MOVW R30,R0
	MUL  R26,R@1
	ADD  R31,R0
	.ENDM

;NAME DEFINITIONS FOR GLOBAL VARIABLES ALLOCATED TO REGISTERS
	.DEF __lcd_x=R5
	.DEF __lcd_y=R4
	.DEF __lcd_maxx=R7

	.CSEG
	.ORG 0x00

;START OF CODE MARKER
__START_OF_CODE:

;INTERRUPT VECTORS
	JMP  __RESET
	JMP  0x00
	JMP  _ext_int1_isr
	JMP  0x00
	JMP  0x00
	JMP  0x00
	JMP  0x00
	JMP  0x00
	JMP  0x00
	JMP  0x00
	JMP  0x00
	JMP  0x00
	JMP  0x00
	JMP  0x00
	JMP  0x00
	JMP  0x00
	JMP  0x00
	JMP  0x00
	JMP  0x00
	JMP  0x00
	JMP  0x00

_tbl10_G103:
	.DB  0x10,0x27,0xE8,0x3,0x64,0x0,0xA,0x0
	.DB  0x1,0x0
_tbl16_G103:
	.DB  0x0,0x10,0x0,0x1,0x10,0x0,0x1,0x0

_0x0:
	.DB  0x43,0x6F,0x72,0x72,0x65,0x63,0x74,0x21
	.DB  0x0,0x57,0x61,0x72,0x6E,0x69,0x6E,0x67
	.DB  0x2E,0x2E,0x2E,0x0,0x45,0x72,0x72,0x6F
	.DB  0x72,0x2E,0x54,0x72,0x79,0x20,0x61,0x67
	.DB  0x61,0x69,0x6E,0x21,0x0,0x4D,0x6F,0x74
	.DB  0x6F,0x72,0x20,0x69,0x73,0x20,0x52,0x75
	.DB  0x6E,0x6E,0x69,0x6E,0x67,0x0
_0x40003:
	.DB  0x31,0x32,0x33,0x34,0x35,0x36,0x37,0x38
	.DB  0x39,0x2A,0x30,0x23
_0x40004:
	.DB  0x31,0x31,0x31,0x31,0x31,0x31
_0x40000:
	.DB  0x45,0x4E,0x54,0x45,0x52,0x20,0x50,0x41
	.DB  0x53,0x53,0x57,0x4F,0x52,0x44,0x3A,0x0
	.DB  0x43,0x68,0x61,0x6E,0x67,0x65,0x20,0x70
	.DB  0x61,0x73,0x73,0x21,0x0,0x4F,0x6C,0x64
	.DB  0x20,0x70,0x61,0x73,0x73,0x3F,0x0,0x4E
	.DB  0x65,0x77,0x20,0x70,0x61,0x73,0x73,0x3F
	.DB  0x0,0x43,0x6F,0x6E,0x66,0x69,0x72,0x6D
	.DB  0x20,0x50,0x61,0x73,0x73,0x3F,0x0,0x50
	.DB  0x61,0x73,0x73,0x20,0x63,0x68,0x61,0x6E
	.DB  0x67,0x65,0x64,0x21,0x0
_0x2020003:
	.DB  0x80,0xC0

__GLOBAL_INI_TBL:
	.DW  0x09
	.DW  _0xD
	.DW  _0x0*2

	.DW  0x0B
	.DW  _0xD+9
	.DW  _0x0*2+9

	.DW  0x11
	.DW  _0xD+20
	.DW  _0x0*2+20

	.DW  0x11
	.DW  _0xD+37
	.DW  _0x0*2+37

	.DW  0x0C
	.DW  _keypad
	.DW  _0x40003*2

	.DW  0x06
	.DW  _pass_md
	.DW  _0x40004*2

	.DW  0x10
	.DW  _0x40019
	.DW  _0x40000*2

	.DW  0x0D
	.DW  _0x40024
	.DW  _0x40000*2+16

	.DW  0x0A
	.DW  _0x40024+13
	.DW  _0x40000*2+29

	.DW  0x0A
	.DW  _0x40024+23
	.DW  _0x40000*2+39

	.DW  0x0E
	.DW  _0x40024+33
	.DW  _0x40000*2+49

	.DW  0x0E
	.DW  _0x40024+47
	.DW  _0x40000*2+63

	.DW  0x02
	.DW  __base_y_G101
	.DW  _0x2020003*2

_0xFFFFFFFF:
	.DW  0

#define __GLOBAL_INI_TBL_PRESENT 1

__RESET:
	CLI
	CLR  R30
	OUT  EECR,R30

;INTERRUPT VECTORS ARE PLACED
;AT THE START OF FLASH
	LDI  R31,1
	OUT  GICR,R31
	OUT  GICR,R30
	OUT  MCUCR,R30

;CLEAR R2-R14
	LDI  R24,(14-2)+1
	LDI  R26,2
	CLR  R27
__CLEAR_REG:
	ST   X+,R30
	DEC  R24
	BRNE __CLEAR_REG

;CLEAR SRAM
	LDI  R24,LOW(__CLEAR_SRAM_SIZE)
	LDI  R25,HIGH(__CLEAR_SRAM_SIZE)
	LDI  R26,__SRAM_START
__CLEAR_SRAM:
	ST   X+,R30
	SBIW R24,1
	BRNE __CLEAR_SRAM

;GLOBAL VARIABLES INITIALIZATION
	LDI  R30,LOW(__GLOBAL_INI_TBL*2)
	LDI  R31,HIGH(__GLOBAL_INI_TBL*2)
__GLOBAL_INI_NEXT:
	LPM  R24,Z+
	LPM  R25,Z+
	SBIW R24,0
	BREQ __GLOBAL_INI_END
	LPM  R26,Z+
	LPM  R27,Z+
	LPM  R0,Z+
	LPM  R1,Z+
	MOVW R22,R30
	MOVW R30,R0
__GLOBAL_INI_LOOP:
	LPM  R0,Z+
	ST   X+,R0
	SBIW R24,1
	BRNE __GLOBAL_INI_LOOP
	MOVW R30,R22
	RJMP __GLOBAL_INI_NEXT
__GLOBAL_INI_END:

;HARDWARE STACK POINTER INITIALIZATION
	LDI  R30,LOW(__SRAM_END-__HEAP_SIZE)
	OUT  SPL,R30
	LDI  R30,HIGH(__SRAM_END-__HEAP_SIZE)
	OUT  SPH,R30

;DATA STACK POINTER INITIALIZATION
	LDI  R28,LOW(__SRAM_START+__DSTACK_SIZE)
	LDI  R29,HIGH(__SRAM_START+__DSTACK_SIZE)

	JMP  _main

	.ESEG
	.ORG 0x00

	.DSEG
	.ORG 0x160

	.CSEG
;/*******************************************************
;This program was created by the CodeWizardAVR V3.32
;Automatic Program Generator
;© Copyright 1998-2017 Pavel Haiduc, HP InfoTech s.r.l.
;http://www.hpinfotech.com
;
;Project : MOTOR_PASS
;Version : 1
;Date    : 14/11/2021
;Author  : nghia
;Company :
;Comments:
;
;
;Chip type               : ATmega16
;Program type            : Application
;AVR Core Clock frequency: 8.000000 MHz
;Memory model            : Small
;External RAM size       : 0
;Data Stack size         : 256
;*******************************************************/
;#include <mega16.h>
	#ifndef __SLEEP_DEFINED__
	#define __SLEEP_DEFINED__
	.EQU __se_bit=0x40
	.EQU __sm_mask=0xB0
	.EQU __sm_powerdown=0x20
	.EQU __sm_powersave=0x30
	.EQU __sm_standby=0xA0
	.EQU __sm_ext_standby=0xB0
	.EQU __sm_adc_noise_red=0x10
	.SET power_ctrl_reg=mcucr
	#endif
;#include <delay.h>
;#include <stdint.h>
;#include <string.h>
;
;#include "Keypad.h"
;#include "EEP.h"
;
;// Alphanumeric LCD functions
;#include <alcd.h>
;
;/* Define Status of Program */
;#define     S_PASSWORD_CHEKING      0
;#define     S_MOTOR_RUN_MODE        1
;#define     S_CHANGE_PASSWORD       2
;
;/* Define Pin/Port */
;#define     Passing_BTN             PINC.6
;#define     Buzzer_BTN              PINC.7
;#define     MOTOR_BTN               PINC.4
;#define     Passing_LED             PORTC.5
;#define     Buzzer                  PORTA.3
;#define     MOTOR                   PORTA.0
;
;
;// Declare your global variables here
;extern uint8_t pass[6];
;extern uint8_t pass1[6];
;extern uint8_t pass2[6];
;extern uint8_t pass_md[6];
;extern uint8_t mk[6];
;volatile uint8_t status = S_PASSWORD_CHEKING;
;
;// External Interrupt 1 service routine
;interrupt [EXT_INT1] void ext_int1_isr(void)
; 0000 0039 {

	.CSEG
_ext_int1_isr:
; .FSTART _ext_int1_isr
	ST   -Y,R26
	ST   -Y,R30
	IN   R30,SREG
	ST   -Y,R30
; 0000 003A     // Jump to Change Password
; 0000 003B     if (status != S_MOTOR_RUN_MODE)
	LDS  R26,_status
	CPI  R26,LOW(0x1)
	BREQ _0x3
; 0000 003C     {
; 0000 003D         status = S_CHANGE_PASSWORD;
	LDI  R30,LOW(2)
	STS  _status,R30
; 0000 003E     }
; 0000 003F }
_0x3:
	LD   R30,Y+
	OUT  SREG,R30
	LD   R30,Y+
	LD   R26,Y+
	RETI
; .FEND
;
;void main(void)
; 0000 0042 {
_main:
; .FSTART _main
; 0000 0043 // Declare your local variables here
; 0000 0044 uint8_t count = 0;
; 0000 0045 uint8_t j = 0;
; 0000 0046 
; 0000 0047 // Input/Output Ports initialization
; 0000 0048 // Port A initialization
; 0000 0049 // Function: Bit7=In Bit6=In Bit5=In Bit4=In Bit3=Out Bit2=In Bit1=In Bit0=Out
; 0000 004A DDRA=(0<<DDA7) | (0<<DDA6) | (0<<DDA5) | (0<<DDA4) | (1<<DDA3) | (0<<DDA2) | (0<<DDA1) | (1<<DDA0);
;	count -> R17
;	j -> R16
	LDI  R17,0
	LDI  R16,0
	LDI  R30,LOW(9)
	OUT  0x1A,R30
; 0000 004B // State: Bit7=T Bit6=T Bit5=T Bit4=T Bit3=0 Bit2=T Bit1=T Bit0=0
; 0000 004C PORTA=(0<<PORTA7) | (0<<PORTA6) | (0<<PORTA5) | (0<<PORTA4) | (0<<PORTA3) | (0<<PORTA2) | (0<<PORTA1) | (0<<PORTA0);
	LDI  R30,LOW(0)
	OUT  0x1B,R30
; 0000 004D 
; 0000 004E // Port B initialization
; 0000 004F // Function: Bit7=Out Bit6=Out Bit5=Out Bit4=Out Bit3=In Bit2=In Bit1=In Bit0=In
; 0000 0050 DDRB=(1<<DDB7) | (1<<DDB6) | (1<<DDB5) | (1<<DDB4) | (0<<DDB3) | (0<<DDB2) | (0<<DDB1) | (0<<DDB0);
	LDI  R30,LOW(240)
	OUT  0x17,R30
; 0000 0051 // State: Bit7=0 Bit6=0 Bit5=0 Bit4=0 Bit3=P Bit2=P Bit1=P Bit0=P
; 0000 0052 PORTB=(0<<PORTB7) | (0<<PORTB6) | (0<<PORTB5) | (0<<PORTB4) | (1<<PORTB3) | (1<<PORTB2) | (1<<PORTB1) | (1<<PORTB0);
	LDI  R30,LOW(15)
	OUT  0x18,R30
; 0000 0053 
; 0000 0054 // Port C initialization
; 0000 0055 // Function: Bit7=In Bit6=In Bit5=Out Bit4=In Bit3=In Bit2=In Bit1=In Bit0=In
; 0000 0056 DDRC=(0<<DDC7) | (0<<DDC6) | (1<<DDC5) | (0<<DDC4) | (0<<DDC3) | (0<<DDC2) | (0<<DDC1) | (0<<DDC0);
	LDI  R30,LOW(32)
	OUT  0x14,R30
; 0000 0057 // State: Bit7=P Bit6=P Bit5=0 Bit4=P Bit3=T Bit2=T Bit1=T Bit0=T
; 0000 0058 PORTC=(1<<PORTC7) | (1<<PORTC6) | (0<<PORTC5) | (1<<PORTC4) | (0<<PORTC3) | (0<<PORTC2) | (0<<PORTC1) | (0<<PORTC0);
	LDI  R30,LOW(208)
	OUT  0x15,R30
; 0000 0059 
; 0000 005A // Port D initialization
; 0000 005B // Function: Bit7=Out Bit6=Out Bit5=Out Bit4=Out Bit3=In Bit2=Out Bit1=Out Bit0=Out
; 0000 005C DDRD=(1<<DDD7) | (1<<DDD6) | (1<<DDD5) | (1<<DDD4) | (0<<DDD3) | (1<<DDD2) | (1<<DDD1) | (1<<DDD0);
	LDI  R30,LOW(247)
	OUT  0x11,R30
; 0000 005D // State: Bit7=0 Bit6=0 Bit5=0 Bit4=0 Bit3=P Bit2=0 Bit1=0 Bit0=0
; 0000 005E PORTD=(0<<PORTD7) | (0<<PORTD6) | (0<<PORTD5) | (0<<PORTD4) | (1<<PORTD3) | (0<<PORTD2) | (0<<PORTD1) | (0<<PORTD0);
	LDI  R30,LOW(8)
	OUT  0x12,R30
; 0000 005F 
; 0000 0060 // Timer/Counter 0 initialization
; 0000 0061 // Clock source: System Clock
; 0000 0062 // Clock value: Timer 0 Stopped
; 0000 0063 // Mode: Normal top=0xFF
; 0000 0064 // OC0 output: Disconnected
; 0000 0065 TCCR0=(0<<WGM00) | (0<<COM01) | (0<<COM00) | (0<<WGM01) | (0<<CS02) | (0<<CS01) | (0<<CS00);
	LDI  R30,LOW(0)
	OUT  0x33,R30
; 0000 0066 TCNT0=0x00;
	OUT  0x32,R30
; 0000 0067 OCR0=0x00;
	OUT  0x3C,R30
; 0000 0068 
; 0000 0069 // Timer/Counter 1 initialization
; 0000 006A // Clock source: System Clock
; 0000 006B // Clock value: Timer1 Stopped
; 0000 006C // Mode: Normal top=0xFFFF
; 0000 006D // OC1A output: Disconnected
; 0000 006E // OC1B output: Disconnected
; 0000 006F // Noise Canceler: Off
; 0000 0070 // Input Capture on Falling Edge
; 0000 0071 // Timer1 Overflow Interrupt: Off
; 0000 0072 // Input Capture Interrupt: Off
; 0000 0073 // Compare A Match Interrupt: Off
; 0000 0074 // Compare B Match Interrupt: Off
; 0000 0075 TCCR1A=(0<<COM1A1) | (0<<COM1A0) | (0<<COM1B1) | (0<<COM1B0) | (0<<WGM11) | (0<<WGM10);
	OUT  0x2F,R30
; 0000 0076 TCCR1B=(0<<ICNC1) | (0<<ICES1) | (0<<WGM13) | (0<<WGM12) | (0<<CS12) | (0<<CS11) | (0<<CS10);
	OUT  0x2E,R30
; 0000 0077 TCNT1H=0x00;
	OUT  0x2D,R30
; 0000 0078 TCNT1L=0x00;
	OUT  0x2C,R30
; 0000 0079 ICR1H=0x00;
	OUT  0x27,R30
; 0000 007A ICR1L=0x00;
	OUT  0x26,R30
; 0000 007B OCR1AH=0x00;
	OUT  0x2B,R30
; 0000 007C OCR1AL=0x00;
	OUT  0x2A,R30
; 0000 007D OCR1BH=0x00;
	OUT  0x29,R30
; 0000 007E OCR1BL=0x00;
	OUT  0x28,R30
; 0000 007F 
; 0000 0080 // Timer/Counter 2 initialization
; 0000 0081 // Clock source: System Clock
; 0000 0082 // Clock value: Timer2 Stopped
; 0000 0083 // Mode: Normal top=0xFF
; 0000 0084 // OC2 output: Disconnected
; 0000 0085 ASSR=0<<AS2;
	OUT  0x22,R30
; 0000 0086 TCCR2=(0<<PWM2) | (0<<COM21) | (0<<COM20) | (0<<CTC2) | (0<<CS22) | (0<<CS21) | (0<<CS20);
	OUT  0x25,R30
; 0000 0087 TCNT2=0x00;
	OUT  0x24,R30
; 0000 0088 OCR2=0x00;
	OUT  0x23,R30
; 0000 0089 
; 0000 008A // Timer(s)/Counter(s) Interrupt(s) initialization
; 0000 008B TIMSK=(0<<OCIE2) | (0<<TOIE2) | (0<<TICIE1) | (0<<OCIE1A) | (0<<OCIE1B) | (0<<TOIE1) | (0<<OCIE0) | (0<<TOIE0);
	OUT  0x39,R30
; 0000 008C 
; 0000 008D // External Interrupt(s) initialization
; 0000 008E // INT0: Off
; 0000 008F // INT1: On
; 0000 0090 // INT1 Mode: Falling Edge
; 0000 0091 // INT2: Off
; 0000 0092 GICR|=(1<<INT1) | (0<<INT0) | (0<<INT2);
	IN   R30,0x3B
	ORI  R30,0x80
	OUT  0x3B,R30
; 0000 0093 MCUCR=(1<<ISC11) | (0<<ISC10) | (0<<ISC01) | (0<<ISC00);
	LDI  R30,LOW(8)
	OUT  0x35,R30
; 0000 0094 MCUCSR=(0<<ISC2);
	LDI  R30,LOW(0)
	OUT  0x34,R30
; 0000 0095 GIFR=(1<<INTF1) | (0<<INTF0) | (0<<INTF2);
	LDI  R30,LOW(128)
	OUT  0x3A,R30
; 0000 0096 
; 0000 0097 // USART initialization
; 0000 0098 // USART disabled
; 0000 0099 UCSRB=(0<<RXCIE) | (0<<TXCIE) | (0<<UDRIE) | (0<<RXEN) | (0<<TXEN) | (0<<UCSZ2) | (0<<RXB8) | (0<<TXB8);
	LDI  R30,LOW(0)
	OUT  0xA,R30
; 0000 009A 
; 0000 009B // Analog Comparator initialization
; 0000 009C // Analog Comparator: Off
; 0000 009D // The Analog Comparator's positive input is
; 0000 009E // connected to the AIN0 pin
; 0000 009F // The Analog Comparator's negative input is
; 0000 00A0 // connected to the AIN1 pin
; 0000 00A1 ACSR=(1<<ACD) | (0<<ACBG) | (0<<ACO) | (0<<ACI) | (0<<ACIE) | (0<<ACIC) | (0<<ACIS1) | (0<<ACIS0);
	LDI  R30,LOW(128)
	OUT  0x8,R30
; 0000 00A2 SFIOR=(0<<ACME);
	LDI  R30,LOW(0)
	OUT  0x30,R30
; 0000 00A3 
; 0000 00A4 // ADC initialization
; 0000 00A5 // ADC disabled
; 0000 00A6 ADCSRA=(0<<ADEN) | (0<<ADSC) | (0<<ADATE) | (0<<ADIF) | (0<<ADIE) | (0<<ADPS2) | (0<<ADPS1) | (0<<ADPS0);
	OUT  0x6,R30
; 0000 00A7 
; 0000 00A8 // SPI initialization
; 0000 00A9 // SPI disabled
; 0000 00AA SPCR=(0<<SPIE) | (0<<SPE) | (0<<DORD) | (0<<MSTR) | (0<<CPOL) | (0<<CPHA) | (0<<SPR1) | (0<<SPR0);
	OUT  0xD,R30
; 0000 00AB 
; 0000 00AC // TWI initialization
; 0000 00AD // TWI disabled
; 0000 00AE TWCR=(0<<TWEA) | (0<<TWSTA) | (0<<TWSTO) | (0<<TWEN) | (0<<TWIE);
	OUT  0x36,R30
; 0000 00AF 
; 0000 00B0 // Alphanumeric LCD initialization
; 0000 00B1 // Connections are specified in the
; 0000 00B2 // Project|Configure|C Compiler|Libraries|Alphanumeric LCD menu:
; 0000 00B3 // RS - PORTD Bit 0
; 0000 00B4 // RD - PORTD Bit 1
; 0000 00B5 // EN - PORTD Bit 2
; 0000 00B6 // D4 - PORTD Bit 4
; 0000 00B7 // D5 - PORTD Bit 5
; 0000 00B8 // D6 - PORTD Bit 6
; 0000 00B9 // D7 - PORTD Bit 7
; 0000 00BA // Characters/line: 16
; 0000 00BB lcd_init(16);
	LDI  R26,LOW(16)
	RCALL _lcd_init
; 0000 00BC 
; 0000 00BD // Globally enable interrupts
; 0000 00BE #asm("sei")
	SEI
; 0000 00BF 
; 0000 00C0 /* Setting up Default Pass at first */
; 0000 00C1 Read_Pass_fromEEP(pass);
	LDI  R26,LOW(_pass)
	LDI  R27,HIGH(_pass)
	RCALL _Read_Pass_fromEEP
; 0000 00C2 if (pass[0] > 9)
	LDS  R26,_pass
	CPI  R26,LOW(0xA)
	BRLO _0x4
; 0000 00C3 {
; 0000 00C4     Write_Pass_toEEP(pass_md);
	LDI  R26,LOW(_pass_md)
	LDI  R27,HIGH(_pass_md)
	RCALL _Write_Pass_toEEP
; 0000 00C5 }
; 0000 00C6 
; 0000 00C7 Read_Pass_fromEEP(pass_md);
_0x4:
	LDI  R26,LOW(_pass_md)
	LDI  R27,HIGH(_pass_md)
	RCALL _Read_Pass_fromEEP
; 0000 00C8 Assign_Pass(pass, pass_md);
	RCALL SUBOPT_0x0
	LDI  R26,LOW(_pass_md)
	LDI  R27,HIGH(_pass_md)
	RCALL _Assign_Pass
; 0000 00C9 
; 0000 00CA /* Super Loop */
; 0000 00CB     while (1)
_0x5:
; 0000 00CC     {
; 0000 00CD         switch(status)
	LDS  R30,_status
	LDI  R31,0
; 0000 00CE         {
; 0000 00CF             case S_PASSWORD_CHEKING:
	SBIW R30,0
	BRNE _0xB
; 0000 00D0             {
; 0000 00D1                 Read_Pass_fromEEP(pass);
	LDI  R26,LOW(_pass)
	LDI  R27,HIGH(_pass)
	RCALL _Read_Pass_fromEEP
; 0000 00D2                 Enter_Pass();
	RCALL _Enter_Pass
; 0000 00D3 
; 0000 00D4                 if( check(pass,mk) )
	RCALL SUBOPT_0x0
	LDI  R26,LOW(_mk)
	LDI  R27,HIGH(_mk)
	RCALL _check
	CPI  R30,0
	BREQ _0xC
; 0000 00D5                 {
; 0000 00D6                     lcd_clear();
	RCALL SUBOPT_0x1
; 0000 00D7                     delay_ms(2);
; 0000 00D8 
; 0000 00D9                     lcd_gotoxy(0,1);
; 0000 00DA                     lcd_puts("Correct!") ;
	__POINTW2MN _0xD,0
	RCALL _lcd_puts
; 0000 00DB 
; 0000 00DC                     status = S_MOTOR_RUN_MODE;
	LDI  R30,LOW(1)
	STS  _status,R30
; 0000 00DD                     j = 0;
	LDI  R16,LOW(0)
; 0000 00DE                 }
; 0000 00DF                 else
	RJMP _0xE
_0xC:
; 0000 00E0                 {
; 0000 00E1                     j++;
	SUBI R16,-1
; 0000 00E2                     if(j>=3)    /* Fail pass > 3 times -> Warning */
	CPI  R16,3
	BRLO _0xF
; 0000 00E3                     {
; 0000 00E4                         lcd_clear();
	RCALL SUBOPT_0x1
; 0000 00E5                         delay_ms(2);
; 0000 00E6 
; 0000 00E7                         lcd_gotoxy(0,1);
; 0000 00E8                         lcd_puts("Warning...");
	__POINTW2MN _0xD,9
	RCALL _lcd_puts
; 0000 00E9 
; 0000 00EA                         /* Buzzer ON in 10s to Warning */
; 0000 00EB                         j=0;
	LDI  R16,LOW(0)
; 0000 00EC                         Buzzer = 1;
	SBI  0x1B,3
; 0000 00ED                         delay_ms(10000);
	LDI  R26,LOW(10000)
	LDI  R27,HIGH(10000)
	RCALL _delay_ms
; 0000 00EE                         Buzzer = 0;
	CBI  0x1B,3
; 0000 00EF                     }
; 0000 00F0                     else    /* Fail pass < 3 times */
	RJMP _0x14
_0xF:
; 0000 00F1                     {
; 0000 00F2                         lcd_gotoxy(0,1);
	RCALL SUBOPT_0x2
; 0000 00F3                         lcd_puts("Error.Try again!");
	__POINTW2MN _0xD,20
	RCALL _lcd_puts
; 0000 00F4                         for (count = 0; count < 2; count++)
	LDI  R17,LOW(0)
_0x16:
	CPI  R17,2
	BRSH _0x17
; 0000 00F5                         {
; 0000 00F6                             Buzzer = 1;
	SBI  0x1B,3
; 0000 00F7                             delay_ms(200);
	LDI  R26,LOW(200)
	LDI  R27,0
	RCALL _delay_ms
; 0000 00F8                             Buzzer = 0;
	CBI  0x1B,3
; 0000 00F9                             delay_ms(200);
	LDI  R26,LOW(200)
	LDI  R27,0
	RCALL _delay_ms
; 0000 00FA                         }
	SUBI R17,-1
	RJMP _0x16
_0x17:
; 0000 00FB                         lcd_clear();
	RCALL _lcd_clear
; 0000 00FC                     }
_0x14:
; 0000 00FD                 }
_0xE:
; 0000 00FE                 break;
	RJMP _0xA
; 0000 00FF             }
; 0000 0100             case S_MOTOR_RUN_MODE:
_0xB:
	CPI  R30,LOW(0x1)
	LDI  R26,HIGH(0x1)
	CPC  R31,R26
	BRNE _0x1C
; 0000 0101             {
; 0000 0102                 if ( MOTOR_BTN == 0 )
	SBIC 0x13,4
	RJMP _0x1D
; 0000 0103                 {
; 0000 0104                     delay_ms(20);
	LDI  R26,LOW(20)
	LDI  R27,0
	RCALL _delay_ms
; 0000 0105                     if ( MOTOR_BTN == 0 )
	SBIC 0x13,4
	RJMP _0x1E
; 0000 0106                     {
; 0000 0107                         MOTOR = 1;      /* Run MOTOR */
	SBI  0x1B,0
; 0000 0108                         lcd_clear();
	RCALL _lcd_clear
; 0000 0109                         delay_ms(2);
	LDI  R26,LOW(2)
	LDI  R27,0
	RCALL _delay_ms
; 0000 010A                         lcd_puts("Motor is Running");
	__POINTW2MN _0xD,37
	RCALL _lcd_puts
; 0000 010B                     }
; 0000 010C                 }
_0x1E:
; 0000 010D                 if ( Passing_BTN == 0 )
_0x1D:
	SBIC 0x13,6
	RJMP _0x21
; 0000 010E                 {
; 0000 010F                     delay_ms(20);
	LDI  R26,LOW(20)
	LDI  R27,0
	RCALL _delay_ms
; 0000 0110                     if ( Passing_BTN == 0 )
	SBIC 0x13,6
	RJMP _0x22
; 0000 0111                     {
; 0000 0112                         /* Blink LED Passing */
; 0000 0113                         for (count = 0; count < 5; count++)
	LDI  R17,LOW(0)
_0x24:
	CPI  R17,5
	BRSH _0x25
; 0000 0114                         {
; 0000 0115                             Passing_LED = 1;
	SBI  0x15,5
; 0000 0116                             delay_ms(200);
	LDI  R26,LOW(200)
	LDI  R27,0
	RCALL _delay_ms
; 0000 0117                             Passing_LED = 0;
	CBI  0x15,5
; 0000 0118                             delay_ms(200);
	LDI  R26,LOW(200)
	LDI  R27,0
	RCALL _delay_ms
; 0000 0119                         }
	SUBI R17,-1
	RJMP _0x24
_0x25:
; 0000 011A                     }
; 0000 011B                 }
_0x22:
; 0000 011C 
; 0000 011D                 if ( Buzzer_BTN == 0 )
_0x21:
	SBIC 0x13,7
	RJMP _0x2A
; 0000 011E                 {
; 0000 011F                     delay_ms(20);
	LDI  R26,LOW(20)
	LDI  R27,0
	RCALL _delay_ms
; 0000 0120                     if ( Buzzer_BTN == 0 )
	SBIC 0x13,7
	RJMP _0x2B
; 0000 0121                     {
; 0000 0122                         /* BUZZER ON in 0,5s */
; 0000 0123                         Buzzer = 1;
	SBI  0x1B,3
; 0000 0124                         delay_ms(500);
	LDI  R26,LOW(500)
	LDI  R27,HIGH(500)
	RCALL _delay_ms
; 0000 0125                         Buzzer = 0;
	CBI  0x1B,3
; 0000 0126                     }
; 0000 0127                 }
_0x2B:
; 0000 0128                 break;
_0x2A:
	RJMP _0xA
; 0000 0129             }
; 0000 012A             case S_CHANGE_PASSWORD:
_0x1C:
	CPI  R30,LOW(0x2)
	LDI  R26,HIGH(0x2)
	CPC  R31,R26
	BRNE _0xA
; 0000 012B             {
; 0000 012C                 Change_Password();
	RCALL _Change_Password
; 0000 012D                 j = 0;
	LDI  R16,LOW(0)
; 0000 012E                 status = S_PASSWORD_CHEKING;
	LDI  R30,LOW(0)
	STS  _status,R30
; 0000 012F                 break;
; 0000 0130             }
; 0000 0131         }
_0xA:
; 0000 0132     }
	RJMP _0x5
; 0000 0133 }
_0x31:
	RJMP _0x31
; .FEND

	.DSEG
_0xD:
	.BYTE 0x36
;
;#include "EEP.h"
;#include <eeprom.h>
;#include <string.h>
;
;void Write_Pass_toEEP(uint8_t send[6])
; 0001 0006 {

	.CSEG
_Write_Pass_toEEP:
; .FSTART _Write_Pass_toEEP
; 0001 0007     eeprom_write_block(send, 0, strlen(send));
	RCALL SUBOPT_0x3
;	send -> R16,R17
	RCALL _eeprom_write_block
; 0001 0008 }
	RJMP _0x20A0004
; .FEND
;void Read_Pass_fromEEP(uint8_t rec[6])
; 0001 000A {
_Read_Pass_fromEEP:
; .FSTART _Read_Pass_fromEEP
; 0001 000B 	eeprom_read_block(rec, 0, strlen(rec));
	RCALL SUBOPT_0x3
;	rec -> R16,R17
	RCALL _eeprom_read_block
; 0001 000C }
	RJMP _0x20A0004
; .FEND
;
;#include "Keypad.h"
;
;#include <mega16.h>
	#ifndef __SLEEP_DEFINED__
	#define __SLEEP_DEFINED__
	.EQU __se_bit=0x40
	.EQU __sm_mask=0xB0
	.EQU __sm_powerdown=0x20
	.EQU __sm_powersave=0x30
	.EQU __sm_standby=0xA0
	.EQU __sm_ext_standby=0xB0
	.EQU __sm_adc_noise_red=0x10
	.SET power_ctrl_reg=mcucr
	#endif
;#include <delay.h>
;#include <alcd.h>
;#include <eeprom.h>
;#include <string.h>
;
;#ifndef S_CHANGE_PASSWORD
;#define     S_CHANGE_PASSWORD       2
;#endif
;
;
;uint8_t keypad[4][3] = {'1','2','3','4','5','6','7','8','9','*','0','#'};

	.DSEG
;uint8_t pass_md[6]={'1','1','1','1','1','1'};
;uint8_t pass[6];
;uint8_t pass1[6];
;uint8_t pass2[6];
;uint8_t mk[6];
;uint8_t oldpass[6];
;extern volatile uint8_t status;
;
;void Assign_Pass(uint8_t nguon[6], uint8_t dich[6])
; 0002 0018 {

	.CSEG
_Assign_Pass:
; .FSTART _Assign_Pass
; 0002 0019 	int i;
; 0002 001A 	for(i = 0; i < 6;i++)
	RCALL SUBOPT_0x4
;	nguon -> R20,R21
;	dich -> R18,R19
;	i -> R16,R17
	__GETWRN 16,17,0
_0x40006:
	__CPWRN 16,17,6
	BRGE _0x40007
; 0002 001B     {
; 0002 001C 		nguon[i] = dich[i];
	MOVW R26,R16
	ADD  R26,R20
	ADC  R27,R21
	MOVW R30,R16
	ADD  R30,R18
	ADC  R31,R19
	LD   R30,Z
	ST   X,R30
; 0002 001D 	}
	__ADDWRN 16,17,1
	RJMP _0x40006
_0x40007:
; 0002 001E }
	RJMP _0x20A0005
; .FEND
;
;uint8_t keypass(void)
; 0002 0021 {
_keypass:
; .FSTART _keypass
; 0002 0022     unsigned char c, r;
; 0002 0023     if(PIN_KEYPAD != 0x0F)
	ST   -Y,R17
	ST   -Y,R16
;	c -> R17
;	r -> R16
	IN   R30,0x16
	CPI  R30,LOW(0xF)
	BREQ _0x40008
; 0002 0024     {
; 0002 0025         for(c=0; c<3; c++)
	LDI  R17,LOW(0)
_0x4000A:
	CPI  R17,3
	BRSH _0x4000B
; 0002 0026         {
; 0002 0027             PORT_KEYPAD = ~(0x01<<(4+c));
	MOV  R30,R17
	SUBI R30,-LOW(4)
	LDI  R26,LOW(1)
	RCALL __LSLB12
	COM  R30
	OUT  0x18,R30
; 0002 0028             delay_ms(1);
	LDI  R27,0
	RCALL _delay_ms
; 0002 0029             for(r=0; r<4; r++)
	LDI  R16,LOW(0)
_0x4000D:
	CPI  R16,4
	BRSH _0x4000E
; 0002 002A             {
; 0002 002B                 if((PIN_KEYPAD & (0x01 << r)) == 0)
	RCALL SUBOPT_0x5
	BRNE _0x4000F
; 0002 002C                 {
; 0002 002D                     while( (PIN_KEYPAD & (0x01<<r)) == 0 );
_0x40010:
	RCALL SUBOPT_0x5
	BREQ _0x40010
; 0002 002E                     return keypad[r][c];
	LDI  R26,LOW(3)
	MUL  R16,R26
	MOVW R30,R0
	SUBI R30,LOW(-_keypad)
	SBCI R31,HIGH(-_keypad)
	MOVW R26,R30
	RCALL SUBOPT_0x6
	RJMP _0x20A0004
; 0002 002F                 }
; 0002 0030             }
_0x4000F:
	SUBI R16,-1
	RJMP _0x4000D
_0x4000E:
; 0002 0031         }
	SUBI R17,-1
	RJMP _0x4000A
_0x4000B:
; 0002 0032     }
; 0002 0033     return 0;
_0x40008:
	LDI  R30,LOW(0)
	RJMP _0x20A0004
; 0002 0034 }
; .FEND
;
;uint8_t check(uint8_t a[], uint8_t b[])
; 0002 0037 {
_check:
; .FSTART _check
; 0002 0038 	unsigned char i;
; 0002 0039 	for(i=0; i<6; i++){
	RCALL SUBOPT_0x4
;	a -> R20,R21
;	b -> R18,R19
;	i -> R17
	LDI  R17,LOW(0)
_0x40014:
	CPI  R17,6
	BRSH _0x40015
; 0002 003A 		if(a[i] != b[i])
	MOVW R26,R20
	CLR  R30
	ADD  R26,R17
	ADC  R27,R30
	LD   R0,X
	MOVW R26,R18
	RCALL SUBOPT_0x6
	CP   R30,R0
	BREQ _0x40016
; 0002 003B         {
; 0002 003C             return 0;
	LDI  R30,LOW(0)
	RJMP _0x20A0005
; 0002 003D         }
; 0002 003E 	}
_0x40016:
	SUBI R17,-1
	RJMP _0x40014
_0x40015:
; 0002 003F 	return 1;
	LDI  R30,LOW(1)
_0x20A0005:
	RCALL __LOADLOCR6
	ADIW R28,8
	RET
; 0002 0040 }
; .FEND
;
;void Enter_Pass(void)
; 0002 0043 {
_Enter_Pass:
; .FSTART _Enter_Pass
; 0002 0044     uint8_t i = 0, key = 0;
; 0002 0045     // P2_7 = 0; LED
; 0002 0046     PORTA.2 = 0;
	ST   -Y,R17
	ST   -Y,R16
;	i -> R17
;	key -> R16
	LDI  R17,0
	LDI  R16,0
	CBI  0x1B,2
; 0002 0047 
; 0002 0048     lcd_gotoxy(0,0);
	RCALL SUBOPT_0x7
; 0002 0049     lcd_puts("ENTER PASSWORD:");
	__POINTW2MN _0x40019,0
	RCALL _lcd_puts
; 0002 004A     lcd_gotoxy(0,1);
	RCALL SUBOPT_0x2
; 0002 004B 
; 0002 004C     i=0;
	LDI  R17,LOW(0)
; 0002 004D     while( i < 6 )
_0x4001A:
	CPI  R17,6
	BRSH _0x4001C
; 0002 004E     {
; 0002 004F         key = keypass();
	RCALL _keypass
	MOV  R16,R30
; 0002 0050         if(key == '1' || key == '2' || key == '3' || key == '4' || key == '5' || key == '6' || key == '7' || key == '8'  ...
	CPI  R16,49
	BREQ _0x4001E
	CPI  R16,50
	BREQ _0x4001E
	CPI  R16,51
	BREQ _0x4001E
	CPI  R16,52
	BREQ _0x4001E
	CPI  R16,53
	BREQ _0x4001E
	CPI  R16,54
	BREQ _0x4001E
	CPI  R16,55
	BREQ _0x4001E
	CPI  R16,56
	BREQ _0x4001E
	CPI  R16,57
	BREQ _0x4001E
	CPI  R16,48
	BRNE _0x4001D
_0x4001E:
; 0002 0051         {
; 0002 0052             lcd_gotoxy(i, 1);
	ST   -Y,R17
	LDI  R26,LOW(1)
	RCALL _lcd_gotoxy
; 0002 0053             lcd_putchar(key);
	MOV  R26,R16
	RCALL _lcd_putchar
; 0002 0054             mk[i] = key;
	MOV  R30,R17
	LDI  R31,0
	SUBI R30,LOW(-_mk)
	SBCI R31,HIGH(-_mk)
	ST   Z,R16
; 0002 0055             key = 0;
	LDI  R16,LOW(0)
; 0002 0056             i++;
	SUBI R17,-1
; 0002 0057         }
; 0002 0058         if(key == '*' && i > 0)
_0x4001D:
	CPI  R16,42
	BRNE _0x40021
	CPI  R17,1
	BRSH _0x40022
_0x40021:
	RJMP _0x40020
_0x40022:
; 0002 0059         {
; 0002 005A             lcd_gotoxy(i-1, 1);
	MOV  R30,R17
	RCALL SUBOPT_0x8
; 0002 005B             lcd_putchar(' ');
; 0002 005C             i--;
	SUBI R17,1
; 0002 005D         }
; 0002 005E         if (status == S_CHANGE_PASSWORD)
_0x40020:
	LDS  R26,_status
	CPI  R26,LOW(0x2)
	BRNE _0x4001A
; 0002 005F         {
; 0002 0060             break;
; 0002 0061         }
; 0002 0062     }
_0x4001C:
; 0002 0063 }
_0x20A0004:
	LD   R16,Y+
	LD   R17,Y+
	RET
; .FEND

	.DSEG
_0x40019:
	.BYTE 0x10
;
;void Change_Password(void)
; 0002 0066 {

	.CSEG
_Change_Password:
; .FSTART _Change_Password
; 0002 0067     uint8_t key = 0, j = 0, k = 0, h = 0;
; 0002 0068     lcd_clear();
	RCALL __SAVELOCR4
;	key -> R17
;	j -> R16
;	k -> R19
;	h -> R18
	LDI  R17,0
	LDI  R16,0
	LDI  R19,0
	LDI  R18,0
	RCALL _lcd_clear
; 0002 0069     lcd_gotoxy(0,0);
	RCALL SUBOPT_0x7
; 0002 006A     lcd_puts("Change pass!");
	__POINTW2MN _0x40024,0
	RCALL _lcd_puts
; 0002 006B     delay_ms(500);
	LDI  R26,LOW(500)
	LDI  R27,HIGH(500)
	RCALL _delay_ms
; 0002 006C     do
_0x40026:
; 0002 006D     {
; 0002 006E         lcd_clear();
	RCALL _lcd_clear
; 0002 006F         lcd_gotoxy(0,0);
	RCALL SUBOPT_0x7
; 0002 0070         lcd_puts("Old pass?");
	__POINTW2MN _0x40024,13
	RCALL _lcd_puts
; 0002 0071         lcd_gotoxy(0,1);
	RCALL SUBOPT_0x2
; 0002 0072 
; 0002 0073         j = 0;
	LDI  R16,LOW(0)
; 0002 0074         while(j < 6)
_0x40028:
	CPI  R16,6
	BRSH _0x4002A
; 0002 0075         {
; 0002 0076             key = keypass();
	RCALL _keypass
	MOV  R17,R30
; 0002 0077             if(key == '1' || key == '2' || key == '3' || key == '4' || key == '5' || key == '6' || key == '7' || key ==  ...
	CPI  R17,49
	BREQ _0x4002C
	CPI  R17,50
	BREQ _0x4002C
	CPI  R17,51
	BREQ _0x4002C
	CPI  R17,52
	BREQ _0x4002C
	CPI  R17,53
	BREQ _0x4002C
	CPI  R17,54
	BREQ _0x4002C
	CPI  R17,55
	BREQ _0x4002C
	CPI  R17,56
	BREQ _0x4002C
	CPI  R17,57
	BREQ _0x4002C
	CPI  R17,48
	BRNE _0x4002B
_0x4002C:
; 0002 0078             {
; 0002 0079                 lcd_gotoxy(j, 1);
	ST   -Y,R16
	RCALL SUBOPT_0x9
; 0002 007A                 lcd_putchar(key);
; 0002 007B                 oldpass[j] = key;
	MOV  R30,R16
	LDI  R31,0
	SUBI R30,LOW(-_oldpass)
	SBCI R31,HIGH(-_oldpass)
	ST   Z,R17
; 0002 007C                 key = 0;
	LDI  R17,LOW(0)
; 0002 007D                 j++;
	SUBI R16,-1
; 0002 007E             }
; 0002 007F             if(key == '*' && j > 0){
_0x4002B:
	CPI  R17,42
	BRNE _0x4002F
	CPI  R16,1
	BRSH _0x40030
_0x4002F:
	RJMP _0x4002E
_0x40030:
; 0002 0080                 lcd_gotoxy(j-1, 1);
	MOV  R30,R16
	RCALL SUBOPT_0x8
; 0002 0081                 lcd_putchar(' ');
; 0002 0082                 j--;
	SUBI R16,1
; 0002 0083             }
; 0002 0084         }
_0x4002E:
	RJMP _0x40028
_0x4002A:
; 0002 0085         // Read_PASS_From_EEP(pass);
; 0002 0086         eeprom_read_block(pass, 0, strlen(pass));
	RCALL SUBOPT_0x0
	RCALL SUBOPT_0xA
	LDI  R26,LOW(_pass)
	LDI  R27,HIGH(_pass)
	RCALL _strlen
	MOVW R26,R30
	RCALL _eeprom_read_block
; 0002 0087     }while( !check(oldpass, pass) );
	LDI  R30,LOW(_oldpass)
	LDI  R31,HIGH(_oldpass)
	ST   -Y,R31
	ST   -Y,R30
	LDI  R26,LOW(_pass)
	LDI  R27,HIGH(_pass)
	RCALL _check
	CPI  R30,0
	BRNE _0x40027
	RJMP _0x40026
_0x40027:
; 0002 0088 
; 0002 0089     do{
_0x40032:
; 0002 008A         lcd_clear();
	RCALL _lcd_clear
; 0002 008B         lcd_gotoxy(0,0);
	RCALL SUBOPT_0x7
; 0002 008C         lcd_puts("New pass?");
	__POINTW2MN _0x40024,23
	RCALL _lcd_puts
; 0002 008D         lcd_gotoxy(0, 1);
	RCALL SUBOPT_0x2
; 0002 008E         k = 0;
	LDI  R19,LOW(0)
; 0002 008F         while(k < 6)
_0x40034:
	CPI  R19,6
	BRSH _0x40036
; 0002 0090         {
; 0002 0091             key = keypass();
	RCALL _keypass
	MOV  R17,R30
; 0002 0092             if(key == '1' || key == '2' || key == '3' || key == '4' || key == '5' || key == '6' || key == '7' || key ==  ...
	CPI  R17,49
	BREQ _0x40038
	CPI  R17,50
	BREQ _0x40038
	CPI  R17,51
	BREQ _0x40038
	CPI  R17,52
	BREQ _0x40038
	CPI  R17,53
	BREQ _0x40038
	CPI  R17,54
	BREQ _0x40038
	CPI  R17,55
	BREQ _0x40038
	CPI  R17,56
	BREQ _0x40038
	CPI  R17,57
	BREQ _0x40038
	CPI  R17,48
	BRNE _0x40037
_0x40038:
; 0002 0093                 lcd_gotoxy(k, 1);
	ST   -Y,R19
	RCALL SUBOPT_0x9
; 0002 0094                 lcd_putchar(key);
; 0002 0095                 pass1[k] = key;
	MOV  R30,R19
	LDI  R31,0
	SUBI R30,LOW(-_pass1)
	SBCI R31,HIGH(-_pass1)
	ST   Z,R17
; 0002 0096                 key = 0;
	LDI  R17,LOW(0)
; 0002 0097                 k++;
	SUBI R19,-1
; 0002 0098             }
; 0002 0099             if(key == '*' && k > 0){
_0x40037:
	CPI  R17,42
	BRNE _0x4003B
	CPI  R19,1
	BRSH _0x4003C
_0x4003B:
	RJMP _0x4003A
_0x4003C:
; 0002 009A                 lcd_gotoxy(k-1, 1);
	MOV  R30,R19
	RCALL SUBOPT_0x8
; 0002 009B                 lcd_putchar(' ');
; 0002 009C                 k--;
	SUBI R19,1
; 0002 009D             }
; 0002 009E         }
_0x4003A:
	RJMP _0x40034
_0x40036:
; 0002 009F 
; 0002 00A0         lcd_clear();
	RCALL _lcd_clear
; 0002 00A1         lcd_gotoxy(0,0);
	RCALL SUBOPT_0x7
; 0002 00A2         lcd_puts("Confirm Pass?");
	__POINTW2MN _0x40024,33
	RCALL _lcd_puts
; 0002 00A3         lcd_gotoxy(0, 1);
	RCALL SUBOPT_0x2
; 0002 00A4         h = 0;
	LDI  R18,LOW(0)
; 0002 00A5         while (h < 6)
_0x4003D:
	CPI  R18,6
	BRSH _0x4003F
; 0002 00A6         {
; 0002 00A7             key = keypass();
	RCALL _keypass
	MOV  R17,R30
; 0002 00A8             if(key == '1' || key == '2' || key == '3' || key == '4' || key == '5' || key == '6' || key == '7' || key ==  ...
	CPI  R17,49
	BREQ _0x40041
	CPI  R17,50
	BREQ _0x40041
	CPI  R17,51
	BREQ _0x40041
	CPI  R17,52
	BREQ _0x40041
	CPI  R17,53
	BREQ _0x40041
	CPI  R17,54
	BREQ _0x40041
	CPI  R17,55
	BREQ _0x40041
	CPI  R17,56
	BREQ _0x40041
	CPI  R17,57
	BREQ _0x40041
	CPI  R17,48
	BRNE _0x40040
_0x40041:
; 0002 00A9             {
; 0002 00AA                 lcd_gotoxy(h, 1);
	ST   -Y,R18
	RCALL SUBOPT_0x9
; 0002 00AB                 lcd_putchar(key);
; 0002 00AC                 pass2[h] = key;
	MOV  R30,R18
	LDI  R31,0
	SUBI R30,LOW(-_pass2)
	SBCI R31,HIGH(-_pass2)
	ST   Z,R17
; 0002 00AD                 key=0;
	LDI  R17,LOW(0)
; 0002 00AE                 h++;
	SUBI R18,-1
; 0002 00AF             }
; 0002 00B0             if(key == '*' && h > 0){
_0x40040:
	CPI  R17,42
	BRNE _0x40044
	CPI  R18,1
	BRSH _0x40045
_0x40044:
	RJMP _0x40043
_0x40045:
; 0002 00B1                 lcd_gotoxy(h-1, 1);
	MOV  R30,R18
	RCALL SUBOPT_0x8
; 0002 00B2                 lcd_putchar(' ');
; 0002 00B3                 h--;
	SUBI R18,1
; 0002 00B4             }
; 0002 00B5         }
_0x40043:
	RJMP _0x4003D
_0x4003F:
; 0002 00B6     } while( !check(pass1, pass2) );
	RCALL SUBOPT_0xB
	LDI  R26,LOW(_pass2)
	LDI  R27,HIGH(_pass2)
	RCALL _check
	CPI  R30,0
	BRNE _0x40033
	RJMP _0x40032
_0x40033:
; 0002 00B7 
; 0002 00B8     // Write_PASS_To_EEP(pass1);
; 0002 00B9     eeprom_write_block(pass1, 0, strlen(pass1));
	RCALL SUBOPT_0xB
	RCALL SUBOPT_0xA
	LDI  R26,LOW(_pass1)
	LDI  R27,HIGH(_pass1)
	RCALL _strlen
	MOVW R26,R30
	RCALL _eeprom_write_block
; 0002 00BA 
; 0002 00BB     lcd_clear();
	RCALL _lcd_clear
; 0002 00BC     lcd_gotoxy(0,0);
	RCALL SUBOPT_0x7
; 0002 00BD     lcd_puts("Pass changed!");
	__POINTW2MN _0x40024,47
	RCALL _lcd_puts
; 0002 00BE }
	JMP  _0x20A0003
; .FEND

	.DSEG
_0x40024:
	.BYTE 0x3D
;
;

	.CSEG
_strlen:
; .FSTART _strlen
	ST   -Y,R27
	ST   -Y,R26
    ld   r26,y+
    ld   r27,y+
    clr  r30
    clr  r31
strlen0:
    ld   r22,x+
    tst  r22
    breq strlen1
    adiw r30,1
    rjmp strlen0
strlen1:
    ret
; .FEND
	#ifndef __SLEEP_DEFINED__
	#define __SLEEP_DEFINED__
	.EQU __se_bit=0x40
	.EQU __sm_mask=0xB0
	.EQU __sm_powerdown=0x20
	.EQU __sm_powersave=0x30
	.EQU __sm_standby=0xA0
	.EQU __sm_ext_standby=0xB0
	.EQU __sm_adc_noise_red=0x10
	.SET power_ctrl_reg=mcucr
	#endif

	.DSEG

	.CSEG
__lcd_write_nibble_G101:
; .FSTART __lcd_write_nibble_G101
	ST   -Y,R17
	MOV  R17,R26
	IN   R30,0x12
	ANDI R30,LOW(0xF)
	MOV  R26,R30
	MOV  R30,R17
	ANDI R30,LOW(0xF0)
	OR   R30,R26
	OUT  0x12,R30
	__DELAY_USB 13
	SBI  0x12,2
	__DELAY_USB 13
	CBI  0x12,2
	__DELAY_USB 13
	RJMP _0x20A0002
; .FEND
__lcd_write_data:
; .FSTART __lcd_write_data
	ST   -Y,R26
	LD   R26,Y
	RCALL __lcd_write_nibble_G101
    ld    r30,y
    swap  r30
    st    y,r30
	LD   R26,Y
	RCALL __lcd_write_nibble_G101
	__DELAY_USB 133
	ADIW R28,1
	RET
; .FEND
_lcd_gotoxy:
; .FSTART _lcd_gotoxy
	ST   -Y,R17
	ST   -Y,R16
	MOV  R17,R26
	LDD  R16,Y+2
	MOV  R30,R17
	LDI  R31,0
	SUBI R30,LOW(-__base_y_G101)
	SBCI R31,HIGH(-__base_y_G101)
	LD   R30,Z
	ADD  R30,R16
	MOV  R26,R30
	RCALL __lcd_write_data
	MOV  R5,R16
	MOV  R4,R17
	LDD  R17,Y+1
	LDD  R16,Y+0
	ADIW R28,3
	RET
; .FEND
_lcd_clear:
; .FSTART _lcd_clear
	LDI  R26,LOW(2)
	RCALL SUBOPT_0xC
	LDI  R26,LOW(12)
	RCALL __lcd_write_data
	LDI  R26,LOW(1)
	RCALL SUBOPT_0xC
	LDI  R30,LOW(0)
	MOV  R4,R30
	MOV  R5,R30
	RET
; .FEND
_lcd_putchar:
; .FSTART _lcd_putchar
	ST   -Y,R17
	MOV  R17,R26
	CPI  R17,10
	BREQ _0x2020005
	CP   R5,R7
	BRLO _0x2020004
_0x2020005:
	LDI  R30,LOW(0)
	ST   -Y,R30
	INC  R4
	MOV  R26,R4
	RCALL _lcd_gotoxy
	CPI  R17,10
	BREQ _0x20A0002
_0x2020004:
	INC  R5
	SBI  0x12,0
	MOV  R26,R17
	RCALL __lcd_write_data
	CBI  0x12,0
	RJMP _0x20A0002
; .FEND
_lcd_puts:
; .FSTART _lcd_puts
	RCALL __SAVELOCR4
	MOVW R18,R26
_0x2020008:
	RCALL SUBOPT_0xD
	MOV  R17,R30
	CPI  R30,0
	BREQ _0x202000A
	MOV  R26,R17
	RCALL _lcd_putchar
	RJMP _0x2020008
_0x202000A:
_0x20A0003:
	RCALL __LOADLOCR4
	ADIW R28,4
	RET
; .FEND
_lcd_init:
; .FSTART _lcd_init
	ST   -Y,R17
	MOV  R17,R26
	IN   R30,0x11
	ORI  R30,LOW(0xF0)
	OUT  0x11,R30
	SBI  0x11,2
	SBI  0x11,0
	SBI  0x11,1
	CBI  0x12,2
	CBI  0x12,0
	CBI  0x12,1
	MOV  R7,R17
	MOV  R30,R17
	SUBI R30,-LOW(128)
	__PUTB1MN __base_y_G101,2
	MOV  R30,R17
	SUBI R30,-LOW(192)
	__PUTB1MN __base_y_G101,3
	LDI  R26,LOW(20)
	LDI  R27,0
	RCALL _delay_ms
	RCALL SUBOPT_0xE
	RCALL SUBOPT_0xE
	RCALL SUBOPT_0xE
	LDI  R26,LOW(32)
	RCALL __lcd_write_nibble_G101
	__DELAY_USW 200
	LDI  R26,LOW(40)
	RCALL __lcd_write_data
	LDI  R26,LOW(4)
	RCALL __lcd_write_data
	LDI  R26,LOW(133)
	RCALL __lcd_write_data
	LDI  R26,LOW(6)
	RCALL __lcd_write_data
	RCALL _lcd_clear
_0x20A0002:
	LD   R17,Y+
	RET
; .FEND

	.CSEG
_eeprom_read_block:
; .FSTART _eeprom_read_block
	RCALL SUBOPT_0xF
	__GETWRS 16,17,10
	__GETWRS 18,19,8
_0x2040003:
	RCALL SUBOPT_0x10
	BREQ _0x2040005
	PUSH R17
	PUSH R16
	__ADDWRN 16,17,1
	MOVW R26,R18
	__ADDWRN 18,19,1
	RCALL __EEPROMRDB
	POP  R26
	POP  R27
	ST   X,R30
	RJMP _0x2040003
_0x2040005:
	RJMP _0x20A0001
; .FEND
_eeprom_write_block:
; .FSTART _eeprom_write_block
	RCALL SUBOPT_0xF
	__GETWRS 16,17,8
	__GETWRS 18,19,10
_0x2040006:
	RCALL SUBOPT_0x10
	BREQ _0x2040008
	PUSH R17
	PUSH R16
	__ADDWRN 16,17,1
	RCALL SUBOPT_0xD
	POP  R26
	POP  R27
	RCALL __EEPROMWRB
	RJMP _0x2040006
_0x2040008:
_0x20A0001:
	RCALL __LOADLOCR6
	ADIW R28,12
	RET
; .FEND
	#ifndef __SLEEP_DEFINED__
	#define __SLEEP_DEFINED__
	.EQU __se_bit=0x40
	.EQU __sm_mask=0xB0
	.EQU __sm_powerdown=0x20
	.EQU __sm_powersave=0x30
	.EQU __sm_standby=0xA0
	.EQU __sm_ext_standby=0xB0
	.EQU __sm_adc_noise_red=0x10
	.SET power_ctrl_reg=mcucr
	#endif

	.CSEG

	.CSEG

	.DSEG
_pass:
	.BYTE 0x6
_pass1:
	.BYTE 0x6
_pass2:
	.BYTE 0x6
_pass_md:
	.BYTE 0x6
_mk:
	.BYTE 0x6
_status:
	.BYTE 0x1
_keypad:
	.BYTE 0xC
_oldpass:
	.BYTE 0x6
__base_y_G101:
	.BYTE 0x4

	.CSEG
;OPTIMIZER ADDED SUBROUTINE, CALLED 3 TIMES, CODE SIZE REDUCTION:4 WORDS
SUBOPT_0x0:
	LDI  R30,LOW(_pass)
	LDI  R31,HIGH(_pass)
	ST   -Y,R31
	ST   -Y,R30
	RET

;OPTIMIZER ADDED SUBROUTINE, CALLED 2 TIMES, CODE SIZE REDUCTION:5 WORDS
SUBOPT_0x1:
	RCALL _lcd_clear
	LDI  R26,LOW(2)
	LDI  R27,0
	RCALL _delay_ms
	LDI  R30,LOW(0)
	ST   -Y,R30
	LDI  R26,LOW(1)
	RJMP _lcd_gotoxy

;OPTIMIZER ADDED SUBROUTINE, CALLED 5 TIMES, CODE SIZE REDUCTION:10 WORDS
SUBOPT_0x2:
	LDI  R30,LOW(0)
	ST   -Y,R30
	LDI  R26,LOW(1)
	RJMP _lcd_gotoxy

;OPTIMIZER ADDED SUBROUTINE, CALLED 2 TIMES, CODE SIZE REDUCTION:9 WORDS
SUBOPT_0x3:
	ST   -Y,R17
	ST   -Y,R16
	MOVW R16,R26
	ST   -Y,R17
	ST   -Y,R16
	LDI  R30,LOW(0)
	LDI  R31,HIGH(0)
	ST   -Y,R31
	ST   -Y,R30
	RCALL _strlen
	MOVW R26,R30
	RET

;OPTIMIZER ADDED SUBROUTINE, CALLED 2 TIMES, CODE SIZE REDUCTION:1 WORDS
SUBOPT_0x4:
	RCALL __SAVELOCR6
	MOVW R18,R26
	__GETWRS 20,21,6
	RET

;OPTIMIZER ADDED SUBROUTINE, CALLED 2 TIMES, CODE SIZE REDUCTION:7 WORDS
SUBOPT_0x5:
	IN   R22,22
	MOV  R30,R16
	LDI  R26,LOW(1)
	LDI  R27,HIGH(1)
	RCALL __LSLW12
	MOV  R26,R22
	LDI  R27,0
	AND  R30,R26
	AND  R31,R27
	SBIW R30,0
	RET

;OPTIMIZER ADDED SUBROUTINE, CALLED 2 TIMES, CODE SIZE REDUCTION:1 WORDS
SUBOPT_0x6:
	CLR  R30
	ADD  R26,R17
	ADC  R27,R30
	LD   R30,X
	RET

;OPTIMIZER ADDED SUBROUTINE, CALLED 6 TIMES, CODE SIZE REDUCTION:13 WORDS
SUBOPT_0x7:
	LDI  R30,LOW(0)
	ST   -Y,R30
	LDI  R26,LOW(0)
	RJMP _lcd_gotoxy

;OPTIMIZER ADDED SUBROUTINE, CALLED 4 TIMES, CODE SIZE REDUCTION:13 WORDS
SUBOPT_0x8:
	SUBI R30,LOW(1)
	ST   -Y,R30
	LDI  R26,LOW(1)
	RCALL _lcd_gotoxy
	LDI  R26,LOW(32)
	RJMP _lcd_putchar

;OPTIMIZER ADDED SUBROUTINE, CALLED 3 TIMES, CODE SIZE REDUCTION:4 WORDS
SUBOPT_0x9:
	LDI  R26,LOW(1)
	RCALL _lcd_gotoxy
	MOV  R26,R17
	RJMP _lcd_putchar

;OPTIMIZER ADDED SUBROUTINE, CALLED 2 TIMES, CODE SIZE REDUCTION:1 WORDS
SUBOPT_0xA:
	LDI  R30,LOW(0)
	LDI  R31,HIGH(0)
	ST   -Y,R31
	ST   -Y,R30
	RET

;OPTIMIZER ADDED SUBROUTINE, CALLED 2 TIMES, CODE SIZE REDUCTION:1 WORDS
SUBOPT_0xB:
	LDI  R30,LOW(_pass1)
	LDI  R31,HIGH(_pass1)
	ST   -Y,R31
	ST   -Y,R30
	RET

;OPTIMIZER ADDED SUBROUTINE, CALLED 2 TIMES, CODE SIZE REDUCTION:1 WORDS
SUBOPT_0xC:
	RCALL __lcd_write_data
	LDI  R26,LOW(3)
	LDI  R27,0
	RJMP _delay_ms

;OPTIMIZER ADDED SUBROUTINE, CALLED 2 TIMES, CODE SIZE REDUCTION:1 WORDS
SUBOPT_0xD:
	MOVW R26,R18
	__ADDWRN 18,19,1
	LD   R30,X
	RET

;OPTIMIZER ADDED SUBROUTINE, CALLED 3 TIMES, CODE SIZE REDUCTION:8 WORDS
SUBOPT_0xE:
	LDI  R26,LOW(48)
	RCALL __lcd_write_nibble_G101
	__DELAY_USW 200
	RET

;OPTIMIZER ADDED SUBROUTINE, CALLED 2 TIMES, CODE SIZE REDUCTION:2 WORDS
SUBOPT_0xF:
	ST   -Y,R27
	ST   -Y,R26
	RCALL __SAVELOCR6
	__GETWRS 20,21,8
	RET

;OPTIMIZER ADDED SUBROUTINE, CALLED 2 TIMES, CODE SIZE REDUCTION:3 WORDS
SUBOPT_0x10:
	LDD  R30,Y+6
	LDD  R31,Y+6+1
	SBIW R30,1
	STD  Y+6,R30
	STD  Y+6+1,R31
	ADIW R30,1
	RET

;RUNTIME LIBRARY

	.CSEG
__SAVELOCR6:
	ST   -Y,R21
__SAVELOCR5:
	ST   -Y,R20
__SAVELOCR4:
	ST   -Y,R19
__SAVELOCR3:
	ST   -Y,R18
__SAVELOCR2:
	ST   -Y,R17
	ST   -Y,R16
	RET

__LOADLOCR6:
	LDD  R21,Y+5
__LOADLOCR5:
	LDD  R20,Y+4
__LOADLOCR4:
	LDD  R19,Y+3
__LOADLOCR3:
	LDD  R18,Y+2
__LOADLOCR2:
	LDD  R17,Y+1
	LD   R16,Y
	RET

__LSLB12:
	TST  R30
	MOV  R0,R30
	MOV  R30,R26
	BREQ __LSLB12R
__LSLB12L:
	LSL  R30
	DEC  R0
	BRNE __LSLB12L
__LSLB12R:
	RET

__LSLW12:
	TST  R30
	MOV  R0,R30
	LDI  R30,8
	MOV  R1,R30
	MOVW R30,R26
	BREQ __LSLW12R
__LSLW12S8:
	CP   R0,R1
	BRLO __LSLW12L
	MOV  R31,R30
	LDI  R30,0
	SUB  R0,R1
	BREQ __LSLW12R
__LSLW12L:
	LSL  R30
	ROL  R31
	DEC  R0
	BRNE __LSLW12L
__LSLW12R:
	RET

__EEPROMRDB:
	SBIC EECR,EEWE
	RJMP __EEPROMRDB
	PUSH R31
	IN   R31,SREG
	CLI
	OUT  EEARL,R26
	OUT  EEARH,R27
	SBI  EECR,EERE
	IN   R30,EEDR
	OUT  SREG,R31
	POP  R31
	RET

__EEPROMWRB:
	SBIS EECR,EEWE
	RJMP __EEPROMWRB1
	WDR
	RJMP __EEPROMWRB
__EEPROMWRB1:
	IN   R25,SREG
	CLI
	OUT  EEARL,R26
	OUT  EEARH,R27
	SBI  EECR,EERE
	IN   R24,EEDR
	CP   R30,R24
	BREQ __EEPROMWRB0
	OUT  EEDR,R30
	SBI  EECR,EEMWE
	SBI  EECR,EEWE
__EEPROMWRB0:
	OUT  SREG,R25
	RET

_delay_ms:
	adiw r26,0
	breq __delay_ms1
__delay_ms0:
	wdr
	__DELAY_USW 0x7D0
	sbiw r26,1
	brne __delay_ms0
__delay_ms1:
	ret

;END OF CODE MARKER
__END_OF_CODE:
