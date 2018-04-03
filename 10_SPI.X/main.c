/*
 * File: Main.c
 * Author: Armstrong Subero
 * Processor: PIC32MX270F256D w/Ext OSC @ 4MHz, PLL to 48 MHz, 3.3v
 * Program: 10_SPI
 * Compiler: XC32 (v1.44, MPLAX X v4.00)
 * Program Version: 1.0
 *                             
 * Program Description: This Program Allows PIC32MX270F256D to use SPI1 module
 *                      which is used to control a MCP4131 digital potentiometer
 * 
 * Hardware Description: An MCP4131 digipot is connected to SPI1
 * 
 * Change History:
 *
 * Author             Rev     Date          Description
 * Armstrong Subero   1.0     03/04/2018    Initial Release.
 * 
 *                      
 * Created April 3rd, 2018, 6:05 PM
 */

/*******************************************************************************
 Includes and defines
*******************************************************************************/
#include <xc.h>
#include <stdio.h>
#include <stdlib.h>
#include "PIC32MX270_STD.h"
#include "Delay.h"
#include "spi1.h"

#define LED LATBbits.LATB14


/*******************************************************************************
* Function Name: digiPot_write(uint8_t i)
*
* Specification: writes a  value to the digipot
*******************************************************************************/
void digiPot_write(uint8_t i)
{
    // Set SS Low
    LATBbits.LATB1 = 0;
    delay_ms(1);
    
    // Slave address
    SPI1_Exchange8bit(0x00);
    
    // Data
    SPI1_Exchange8bit(i);
    
    // Set SS High
    LATBbits.LATB1 = 1;
    delay_ms(1);
}



/*******************************************************************************
* Function Name: void initMain (void)
*
* Specification: initializes main
*
*******************************************************************************/
void initMain(void)
{  
    uc_init();                    // initialize microcontroller
    TRISBbits.TRISB1 = 0;         // set PINB1 as output
    
    // unlock PPS
    systemReg_Unlock();
    CFGCONbits.IOLOCK = 0;

    RPC5Rbits.RPC5R = 0x0001;     //RC5->UART1 TX
    RPB11Rbits.RPB11R = 0x0003;   //RB11->SDO1;

    // lock PPS
    CFGCONbits.IOLOCK = 1; 
    systemReg_Lock();
    
    SPI1_init();                  // initialize SPI
}


/*******************************************************************************
* Function Name: void main (void)
*
* Specification: main function
*
*******************************************************************************/
void main(void) {
    
    initMain();         // initializes main function
    int i;              // variable for digipot value
    
    while(1)
    { 
         for (i = 0; i <= 127; i++){ 
             digiPot_write(i);       // write value to digipot
             delay_ms(100);          // delay 100 ms
         } 
    }
}




