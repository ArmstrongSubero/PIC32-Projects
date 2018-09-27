/*
 * File: PIC32MX270_STD.h
 * Author: Armstrong Subero
 * Processor: PIC32MX270F256D @ 48MHz, 3.3v
 * Program: One Wire Protocol
 * Compiler: XC32 (v1.44, MPLAX X v5.05)
 * Program Version 1.0
 * Program Description: This header file contains MX270F256D setup
 * 
 * Change History:
 *
 * Author             Rev     Date          Description
 * Armstrong Subero   1.0     26/09/2018    Initial Release.
 * 
 * Updated on September 26, 2018, 10:06 PM
 */


/*******************************************************************************
* Includes and defines
*******************************************************************************/
#include <xc.h>

// Define OneWire Pin
#define OW_Pin PORTCbits.RC0
#define OW_Dir TRISCbits.TRISC0 
#define OW_Analog ANSELCbits.ANSC0

// Registers
#define SKIP_ROM 0xCC
#define START_CONVERSION 0x44 
#define WRITE_SCRATCHPAD 0x4E
#define RESOLUTION_12BIT 0x7F
#define READ_SCRATCHPAD 0xBE

// function prototypes
void OW_Init(void);
unsigned char OW_Reset(void);
unsigned char OW_ReadBit();
void OW_WriteBit(int b);
unsigned char OW_ReadByte(void);
void OW_WriteByte(char val);
