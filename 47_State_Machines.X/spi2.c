/*
 * File: spi2.c
 * Author: Armstrong Subero
 * Processor: PIC32MX270F256D w/Ext OSC @ 4MHz, PLL to 48 MHz, 3.3v
 * Program: Library file for Delay
 * Compiler:  XC32 (v1.44, MPLAX X v4.00)
 * Program Version: 1.1
 *              
 * Program Description: This Library allows you to use the SPI2 module on the
 *                      PIC32MX270F256D
 * 
 * Modified From: Microchip Forums
 *  
 * 
 * Change History:
 *
 * Author             Rev     Date          Description
 * Armstrong Subero   1.0     09/04/2015    Initial Release.

 *                      
 * Updated on April 9th, 2018, 5:59 PM
 */


/*******************************************************************************
 Includes and defines
*******************************************************************************/
#include "spi2.h"


/*******************************************************************************
* Function Name: SPI1_init(void)
*
* Specification: Initializes the SPI1 module
*
*******************************************************************************/
void SPI2_init(void)
{
    SPI2BUF;                  // clear SPI bus by reading from it
    SPI2BRG = 11;             // baud rate = (24000000/(2*4)) - 1 (SPI at 1 MHz)
    SPI2STATbits.SPIROV = 0;  // clear the overflow bit
    SPI2CONbits.FRMEN   = 0;  // frame support diabled
    SPI2CONbits.MCLKSEL = 0;  // PPBCLK used by baud rate generator
    SPI2CONbits.MODE32  = 0;  // use 8 bit mode
    SPI2CONbits.MODE16  = 0;
    SPI2CONbits.MSTEN   = 1;  // user SPI in master mode
    SPI2CONbits.CKP     = 1;  // clock idle state is high
    SPI2CONbits.ON      = 1;  // turn on SPI1          
}


/*******************************************************************************
* Function Name: uint8_t SPI1_Exchange8bit(unsigned char b)
*
* Specification: Exchanges a byte of data with SPI1
*
*******************************************************************************/
uint8_t SPI2_Exchange8bit(unsigned char b)
{
	SPI2BUF = b;                        // write to buffer for TX
    while( !SPI2STATbits.SPIRBF);       // wait transfer complete
    return SPI2BUF;                     // read the received value 
}
