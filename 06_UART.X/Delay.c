/*
 * File: Delay_32.c
 * Author: Armstrong Subero
 * Processor: PIC32MX270F256D w/Ext OSC @ 4MHz, PLL to 48 MHz, 3.3v
 * Program: Library file for Delay
 * Compiler:  XC32 (v1.44, MPLAX X v4.00)
 * Program Version: 1.1
 *              
 * Program Description: This Library allows you to use the MIPS coprocessor 0
 *                      to add delay functions to a PIC32MX270F256D this version
 *                      of the library removed functions provided by PLIB
 * 
 * Modified From: Microchip Forums
 *  
 * 
 * Change History:
 *
 * Author             Rev     Date          Description
 * Armstrong Subero   1.0     08/02/2015    Initial Release.
 * Armstrong Subero   1.1     26/03/2018    Changed to accommodate 270F256D from
 *                                          230F064D 
 *                                          Removed dependency on Legacy Lib
 *                      
 * Updated on March 26th, 2018, 12:23 PM
 */

/*******************************************************************************
 Includes and defines
*******************************************************************************/
#include "Delay.h"


/*******************************************************************************
* Function: void delay_ms (unsigned long delay)
*
* Returns: Nothing
*
* Description:   Millisecond Delay function using the Count register
*                in coprocessor 0 in the MIPS core.
*
*******************************************************************************/
void delay_ms(unsigned long delay)
{
    register unsigned int startCntms = _CP0_GET_COUNT();
    register unsigned int waitCntms = delay * ms_SCALE;

    while(_CP0_GET_COUNT() - startCntms < waitCntms );
}


/*******************************************************************************
* Function: void delay_us (unsigned long delay)
*
* Returns: Nothing
*
* Description: Microsecond Delay function using the Count register
*              in coprocessor 0 in the MIPS core.
*
*******************************************************************************/
void delay_us(unsigned long delay)
{
    register unsigned int startCnt = _CP0_GET_COUNT();
    register unsigned int waitCnt = delay * us_SCALE;

    while(_CP0_GET_COUNT() - startCnt < waitCnt );
}

