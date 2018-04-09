/*
 * File: Main.c
 * Author: Armstrong Subero
 * Processor: PIC32MX270F256D w/Ext OSC @ 4MHz, PLL to 48 MHz, 3.3v
 * Program: 28_ST7735
 * Compiler: XC32 (v1.44, MPLAX X v4.00)
 * Program Version: 1.0
 *                             
 * Program Description: This Program Allows PIC32MX270F256D to communicate with
 *                      the ST7735 LCD using the SPI2 module.
 * 
 * Hardware Description: A ST7735 LCD is connected as follows:
 *                       RST    -> RC3
 *                       CS     -> RC4
 *                       RS     -> RC5
 *                       DIN    -> RA9
 *                       CLK    -> RB15
 *                       VCC    -> VCC
 *                       BL     -> VCC via 10k
 *                       GND    -> GND
 *  
 * Change History:
 *
 * Author             Rev     Date          Description
 * Armstrong Subero   1.0     09/04/2018    Initial Release.
 * 
 *                      
 * Created April 9th, 2018, 5:09 PM
 */

/*******************************************************************************
 Includes and defines
*******************************************************************************/
#include <xc.h>
#include <stdio.h>
#include <stdlib.h>
#include "PIC32MX270_STD.h"
#include "Delay.h"
#include "ST7735.h"
#include "spi2.h"

/*******************************************************************************
* Function Name: void initMain (void)
*
* Specification: initializes main
*
*******************************************************************************/
void initMain(void)
{  
    uc_init();                  // initialize microcontroller
    
    // unlock PPS
    systemReg_Unlock();
    CFGCONbits.IOLOCK = 0;

    RPA9Rbits.RPA9R = 0x0004;   // RA9->SDO2;
   
    // lock PPS
    CFGCONbits.IOLOCK = 1; 
    systemReg_Lock();
    
    TRISCbits.TRISC3 = 0;      // reset
    TRISCbits.TRISC4 = 0;      // chip select	
    TRISCbits.TRISC5 = 0;      // data or command 
    PORTCbits.RC3 = 0;
    PORTCbits.RC4 = 0;
    PORTCbits.RC5 = 0;
   
    PMCONbits.ON = 0;         // Turn of PMP as per errata
 
    SPI2_init();              // Initialize SPI2
}


/*******************************************************************************
* Function Name: void main (void)
*
* Specification: main function
*
*******************************************************************************/
void main(void) {
    
    initMain();         // initializes main function
    ST7735_initR();     // initialize LCD
   
    while(1)
    {
       ST7735_test();   // start LCD test
    }
}




