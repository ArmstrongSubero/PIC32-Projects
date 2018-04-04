/*
 * File: Main.c
 * Author: Armstrong Subero
 * Processor: PIC32MX270F256D w/Ext OSC @ 4MHz, PLL to 48 MHz, 3.3v
 * Program: 13_Idle_Sleep
 * Compiler: XC32 (v1.44, MPLAX X v4.00)
 * Program Version: 1.0
 *                             
 * Program Description: This Program Allows PIC32MX270F256D to demonstrate the
 *                      IDLE and SLEEP modes of the microcontroller.
 * 
 * Hardware Description: An CP2104 USB-UART converter is connected to PINC5
 * 
 * Change History:
 *
 * Author             Rev     Date          Description
 * Armstrong Subero   1.0     03/04/2018    Initial Release.
 * 
 *                      
 * Created April 3nd, 2018, 9:40 PM
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
    uc_init();              // initialize microcontroller
    TRISBbits.TRISB14 = 0;  // set PINB1 as output
    
    // unlock PPS
    systemReg_Unlock();
    CFGCONbits.IOLOCK = 0;

    RPC5Rbits.RPC5R = 0x0001;   //RC5->UART1 TX

    // lock PPS
    CFGCONbits.IOLOCK = 1; 
    systemReg_Lock();
    
    UART1_Initialize(); 
}


/*******************************************************************************
* Function Name: void main (void)
*
* Specification: main function
*
*******************************************************************************/
void main(void) {
    
    initMain();         // initializes main function
    
    #define SLEEP_DEMO
    
    while(1)
    {
      // configure printf to use UART1
      __XC_UART = 1;
      
      printf("Start");
      delay_ms(1000);
      
#ifdef IDLE_DEMO
      printf("Going to IDLE\n");
      delay_ms(5000);       // delay 5 seconds
      
      SYSKEY = 0x0;         // Write invalid key to force lock
      SYSKEY = 0xAA996655;  // Write Key1 to SYSKEY
      SYSKEY = 0x556699AA;  // Write Key2 to SYSKEY
      OSCCONCLR = 0x10;     // Set the power-saving mode to an idle mode
      SYSKEY = 0x0;         // Write invalid key to force lock
      
      asm volatile ( "wait" ); // Put device in selected power-saving mode
      
      printf("After Idle dose not run!\n");
      
#elif defined SLEEP_DEMO
      
      OSCCONSET = 0x10;           // set Power-Saving mode to Sleep
      
      printf ("Going to SLEEP\n");
      delay_ms(5000);
      asm volatile("wait");       // put device in sleep mode
      
      printf("After sleep dose not run");
      
#endif
      
    }
}
