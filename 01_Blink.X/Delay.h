/*
 * File:   Delay_32.h
 * Author: Armstrong Subero
 * Processor: PIC32MX270F256D @ 48MHz, 3.3v
 * Program: Header file for MX270F256D delay routines
 * Compiler: XC32 (v1.44, MPLAX X v4.00)
 * Program Version 1.1
 * Program Description: This header file contains MX270F256D delay functions
 * Modified From: Microchip Forum discussion
 * 
 * Change History:
 *
 * Author             Rev     Date          Description
 * Armstrong Subero   1.0     08/02/2015    Initial Release.
 * Armstrong Subero   1.1     26/03/2018    Changed to accommodate 270F256D from
 *                                          230F064D 
 *                                          Removed dependency on Legacy Lib
 * 
 * Updated on March 26, 2018, 12:17 PM
 */


/*******************************************************************************
 Includes and defines
*******************************************************************************/
#include "PIC32MX270_STD.h"

#define us_SCALE   (GetSystemClock()/2000000)
#define ms_SCALE   (GetSystemClock()/2000)


/*******************************************************************************
 Function Prototype
*******************************************************************************/
void delay_ms(unsigned long delay);
void delay_us(unsigned long delay);


