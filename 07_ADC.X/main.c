/*
 * File: Main.c
 * Author: Armstrong Subero
 * Processor: PIC32MX270F256D w/Ext OSC @ 4MHz, PLL to 48 MHz, 3.3v
 * Program: 07_ADC
 * Compiler: XC32 (v1.44, MPLAX X v4.00)
 * Program Version: 1.0
 *                             
 * Program Description: This Program Allows PIC32MX270F256D to use the ADC module
 * 
 * Hardware Description: An potentiometer is connected to AN3
 * 
 * Change History:
 *
 * Author             Rev     Date          Description
 * Armstrong Subero   1.0     02/04/2018    Initial Release.
 * 
 *                      
 * Created April 3rd, 2018, 1:31 AM
 */

/*******************************************************************************
 Includes and defines
*******************************************************************************/
#include <xc.h>
#include <stdio.h>
#include <stdlib.h>
#include "PIC32MX270_STD.h"
#include "Delay.h"
#include "uart1.h"
#include "adc.h"

#define LED LATBbits.LATB14


/*******************************************************************************
* Function Name: void initMain (void)
*
* Specification: initializes main
*
*******************************************************************************/
void initMain(void)
{  
    uc_init();              // initialize microcontroller
    TRISBbits.TRISB14 = 0;  // set PINB14 as output
    ANSELBbits.ANSB1 = 1;   // make channel 3 analog input
    
    // unlock PPS
    systemReg_Unlock();
    CFGCONbits.IOLOCK = 0;

    RPC5Rbits.RPC5R = 0x0001;   //RC5->UART1:U1TX;

    // lock PPS
    CFGCONbits.IOLOCK = 1; 
    systemReg_Lock();
    
    UART1_Initialize(); 
    ADC_Init();
}


/*******************************************************************************
* Function Name: void main (void)
*
* Specification: main function
*
*******************************************************************************/
void main(void) {
    
    initMain();         // initializes main function
    
    int conversion;
    
    while(1)
    {
      // configure printf to use UART1
      __XC_UART = 1;
      
      conversion = readADC(3);  // perform ADC conversion on channel 3
      
      printf("%d\n", conversion);
      delay_ms(1000);   // delay 1 second
    }
}
