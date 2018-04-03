/*
 * File:   adc.h
 * Author: Armstrong Subero
 * Processor: PIC32MX270F256D @ 48MHz, 3.3v
 * Program: Header file for MX270F256D delay routines
 * Compiler: XC32 (v1.44, MPLAX X v4.00)
 * Program Version 1.1
 * Program Description: This header file contains MX270F256D adc function 
 *                      prototypes
 * 
 * Change History:
 *
 * Author             Rev     Date          Description
 * Armstrong Subero   1.0     03/04/2015    Initial Release.
 * 
 * Updated on April 3rd, 2018, 1:27 AM
 */

#include "PIC32MX270_STD.h"

void ADC_Init(void);
int readADC(int ch);