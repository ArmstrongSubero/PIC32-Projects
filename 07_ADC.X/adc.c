/*
 * File: adc.c
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
 * Updated on April 3rd, 2018, 1:29 AM
 */


#include "adc.h"

/*******************************************************************************
* Function Name: ADC_Init(void)
*
* Specification: Initializes the ADC module
*******************************************************************************/
void ADC_Init(void)
{
     // ASAM disabled; DONE disabled; CLRASAM disabled; FORM Integer 16 bit; SAMP disabled; SSRC Clearing sample bit ends sampling and starts conversion; SIDL disabled; ON enabled; 
   AD1CON1 = 0x8000;

    // CSCNA disabled; ALTS disabled; BUFM disabled; SMPI 1; OFFCAL disabled; VCFG AVDD/AVSS; 
   AD1CON2 = 0x0;

    // SAMC 0; ADRC PBCLK; ADCS 4; 
   AD1CON3 = 0x4;

    // CH0SA AN2; CH0SB AN0; CH0NB Vrefl; CH0NA Vrefl; 
   AD1CHS = 0x20000;

    // CSSL15 disabled; CSSL14 disabled; CSSL11 disabled; CSSL10 disabled; CSSL13 disabled; CSSL9 disabled; CSSL12 disabled; CSSL0 disabled; CSSL8 disabled; CSSL7 disabled; CSSL6 disabled; CSSL5 disabled; CSSL4 disabled; CSSL3 disabled; CSSL2 disabled; CSSL1 disabled; 
   AD1CSSL = 0x0;
}


/*******************************************************************************
* Function Name: int readADC (int ch)
*
* Specification:   Reads a particular ADC channel and returns the result
*******************************************************************************/
int readADC(int ch)
{
    // select analog input
    AD1CHSbits.CH0SA = ch;
    
    // start sampling
    AD1CON1bits.SAMP = 1;
    
    // delay to allow for sampling
    delay_us(5);
    
    // start the conversion
    AD1CON1bits.SAMP = 0;
    
    // wait for conversion to complete
    while(!AD1CON1bits.DONE);
    
    // return conversion result
    return ADC1BUF0;
}
