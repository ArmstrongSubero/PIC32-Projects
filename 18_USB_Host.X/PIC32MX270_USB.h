/*
 * File: PIC32MX270_STD.h
 * Author: Armstrong Subero
 * Processor: PIC32MX270F256D @ 48MHz, 3.3v
 * Program: Header file for MX270F256D setup
 * Compiler: XC32 (v1.44, MPLAX X v4.00)
 * Program Version 1.1
 * Program Description: This header file contains MX270F256D setup
 * 
 * Change History:
 *
 * Author             Rev     Date          Description
 * Armstrong Subero   1.0     08/02/2015    Initial Release.
 * Armstrong Subero   1.1     02/04/2018    Changed to accommodate 270F256D from
 *                                          230F064D 
 *                                          Removed dependency on Legacy Lib
 * 
 * Updated on April 2, 2018, 9:09 PM
 */


/*******************************************************************************
 Includes and defines
*******************************************************************************/
#include <p32xxxx.h>
#include <xc.h>
#include <sys/attribs.h>
#include <stdint.h>
#include <stdbool.h>
#include <stdio.h>
#include <stdlib.h>


#define HIGH   1
#define LOW    0
#define INPUT  0
#define OUTPUT 1

#define PI  3.14159


/*******************************************************************************
 Function Prototype
*******************************************************************************/
void uc_init(void);
void systemReg_Unlock(void);
void systemReg_Lock(void);




