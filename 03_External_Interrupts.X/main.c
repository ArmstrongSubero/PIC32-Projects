/*
 * File: Main.c
 * Author: Armstrong Subero
 * Processor: PIC32MX270F256D w/Ext OSC @ 4MHz, PLL to 48 MHz, 3.3v
 * Program: 03_External_Interrupts
 * Compiler: XC32 (v1.44, MPLAX X v4.00)
 * Program Version: 1.0
 *                             
 * Program Description: This Program Allows PIC32MX270F256D to used external
 *                      interrupts
 * 
 * Hardware Description: An LED is connected via a 1k resistor to PIN RB14 and
 *                       a switch is connected to PINB7
 * 
 * Change History:
 *
 * Author             Rev     Date          Description
 * Armstrong Subero   1.0     02/04/2018    Initial Release.
 * 
 *                      
 * Created April 2nd, 2018, 9:52 PM
 */

/*******************************************************************************
 Includes and defines
*******************************************************************************/
#include <xc.h>
#include "PIC32MX270_STD.h"
#include "Delay.h"

#define LED LATBbits.LATB14
#define SWITCH PORTBbits.RB1


/*******************************************************************************
* Function Name: void __ISR(_EXTERNAL_0_VECTOR, IPL1SOFT) Ext0ISR(void)
*
* Specification: interrupt routine for external interrupt on PINB7 (INT0)
*
*******************************************************************************/
void __ISR(_EXTERNAL_0_VECTOR, IPL1SOFT) Ext0ISR(void)
{
    int i; 
    
    for (i = 0; i <= 10; i++)
    {
      LED = 0;
      delay_ms(1000);
      LED = 1;
      delay_ms(1000);
    }
    
    LED = 0;              // set LED low again
    IFS0bits.INT0IF = 0;  // clear interrupt flag     
}


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
    TRISBbits.TRISB1  = 1;  // set PINB1 as input
    ANSELBbits.ANSB1  = 0;  // turn off analog input on PINB1
}


/*******************************************************************************
* Function Name: void main (void)
*
* Specification: main function
*
*******************************************************************************/
void main(void) {
    
    initMain();         // initializes main function
    
    __builtin_disable_interrupts();   // disable interrupts
     
    INTCONbits.INT0EP = 0;   // interrupt triggers on negative edge    
    IPC0bits.INT0IP = 1;     // EXT0 priority 1
    IPC0bits.INT0IS = 0;     // EXT0 sub-priority 0
    IFS0bits.INT0IF = 0;     // clear the interrupt flag
    
    IEC0bits.INT0IE = 1;     // enable interrupt on INT0
   
    INTCONbits.MVEC = 1;     //  Enable the multi vector interrupts

    __builtin_enable_interrupts();   // enable interrupts
    
    while(1)
    {
       // do nothing
    }
}
