/*
 * File: Main.c
 * Author: Armstrong Subero
 * Processor: PIC32MX270F256D w/Ext OSC @ 4MHz, PLL to 48 MHz, 3.3v
 * Program: 12_Comparator
 * Compiler: XC32 (v1.44, MPLAX X v4.00)
 * Program Version: 1.0
 *                             
 * Program Description: This Program Allows PIC32MX270F256D to use the 
 *                      comparator module. The non-inverting input of the 
 *                      comparator is connected to a potentiometer and the
 *                      inverting input is connected to the output of a voltage
 *                      divider.
 * 
 * Hardware Description: A 10k potentiometer is connected to PINB3 and a 1k 
 *                       voltage divider is connected to PINB2. An LED is 
 *                       connected via a 1k resistor to PIN RC9 which is
 *                       comparator output.
 * 
 * Change History:
 *
 * Author             Rev     Date          Description
 * Armstrong Subero   1.0     03/04/2018    Initial Release.
 * 
 *                      
 * Created April 3nd, 2018, 9:07 PM
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

#define LED LATBbits.LATB14


/*******************************************************************************
* Function Name: void initMain (void)
*
* Specification: initializes main
*
*******************************************************************************/
void initMain(void)
{  
    uc_init();                // initialize microcontroller
    TRISBbits.TRISB14 = 0;    // set PINB14 as output
    
    // unlock PPS
    systemReg_Unlock();
    CFGCONbits.IOLOCK = 0;

    RPC5Rbits.RPC5R = 0x0001;  //RC5->UART1 TX
    RPC9Rbits.RPC9R = 0x0007;  //RC9->C1OUT;

    // lock PPS
    CFGCONbits.IOLOCK = 1; 
    systemReg_Lock();
    
    TRISCbits.TRISC9 = 0;     // set comparator output pin as output
   
    CMSTATbits.SIDL  = 0;     // comparators will continue to operate in IDLE
    CM1CONbits.COE   = 1;     // comparator output is driven to out pin
    CM1CONbits.CREF  = 0;     // comparator positive input connected to C1INA
    CM1CONbits.CCH0  = 0;     // comparator negative input connect to   C1INB
    CM1CONbits.CCH1  = 0;
    CM1CONbits.ON    = 1;     // turn the comparator on
    
    UART1_Initialize();       // initialize UART   
}


/*******************************************************************************
* Function Name: void main (void)
*
* Specification: main function
*
*******************************************************************************/
void main(void) {
    
    initMain();         // initializes main function
    
    while(1)
    {
      // configure printf to use UART1
      __XC_UART = 1;
      
      if (CM1CONbits.COUT)    // if output bit is high
      {
        printf("High\n");     // send High via UART
        delay_ms(1000);       // delay 1 second
      }
      
      else
      {
        printf("Low\n");      // send Low via UART
        delay_ms(1000);       // delay 1 second
      }
      
    }
}
