/*
 * File: spi1.c
 * Author: Armstrong Subero
 * Processor: PIC32MX270F256D w/Ext OSC @ 4MHz, PLL to 48 MHz, 3.3v
 * Program: Library file for Delay
 * Compiler:  XC32 (v1.44, MPLAX X v4.00)
 * Program Version: 1.1
 *              
 * Program Description: This Library allows you to use the SPI1 module on the
 *                      PIC32MX270F256D
 * 
 * Modified From: Microchip Forums
 *  
 * 
 * Change History:
 *
 * Author             Rev     Date          Description
 * Armstrong Subero   1.0     08/02/2015    Initial Release.

 *                      
 * Updated on April 3rd, 2018, 5:59 PM
 */


/*******************************************************************************
 Includes and defines
*******************************************************************************/
#include "spi1.h"


/*******************************************************************************
* Function Name: SPI1_init(void)
*
* Specification: Initializes the SPI1 module
*
*******************************************************************************/
void SPI1_init(void)
{
    SPI1BUF;                  // clear SPI bus by reading from it
    SPI1BRG = 11;             // baud rate = (24000000/(2*4)) - 1 (SPI at 1 MHz)
    SPI1STATbits.SPIROV = 0;  // clear the overflow bit
    SPI1CONbits.FRMEN   = 0;  // frame support diabled
    SPI1CONbits.MCLKSEL = 0;  // PPBCLK used by baud rate generator
    SPI1CONbits.MODE32  = 0;  // use 8 bit mode
    SPI1CONbits.MODE16  = 0;
    SPI1CONbits.MSTEN   = 1;  // user SPI in master mode
    SPI1CONbits.CKP     = 1;  // clock idle state is high
    SPI1CONbits.ON      = 1;  // turn on SPI1          
}


/*******************************************************************************
* Function Name: uint8_t SPI1_Exchange8bit(unsigned char b)
*
* Specification: Exchanges a byte of data with SPI1
*
*******************************************************************************/
uint8_t SPI1_Exchange8bit(unsigned char b)
{
	SPI1BUF = b;                        // write to buffer for TX
    while( !SPI1STATbits.SPIRBF);       // wait transfer complete
    return SPI1BUF;                     // read the received value 
}
