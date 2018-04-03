/*
 * File: Main.c
 * Author: Armstrong Subero
 * Processor: PIC32MX270F256D w/Ext OSC @ 4MHz, PLL to 48 MHz, 3.3v
 * Program: 05_Counter
 * Compiler: XC32 (v1.44, MPLAX X v4.00)
 * Program Version: 1.0
 *                             
 * Program Description: This Program Allows PIC32MX270F256D to use Timer5 as
 *                      a counter which turns on an LED when the count reaches
 *                      a certain value
 * 
 * Hardware Description: An LED is connected via a 1k resistor to PIN RB14 
 * 
 * Change History:
 *
 * Author             Rev     Date          Description
 * Armstrong Subero   1.0     02/04/2018    Initial Release.
 * 
 *                      
 * Created April 2nd, 2018, 10:46 PM
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
    
    // unlock PPS
    systemReg_Unlock();  
    CFGCONbits.IOLOCK = 0;

    T5CKRbits.T5CKR = 0x0004;   //RB9->TMR5 CLK
    
    // LOCK PPS
    CFGCONbits.IOLOCK = 1; 
    systemReg_Lock();
}


/*******************************************************************************
* Function Name: void main (void)
*
* Specification: main function
*
*******************************************************************************/
void main(void) {
    
    initMain();         // initializes main function
    
     __builtin_disable_interrupts();  // disable interrupts    
    
    TMR5 = 0;               // initialize count to 0
    PR5 = 0xFFFF;           // allow count to reach max 
    T5CONbits.TCKPS0 = 0;   // set prescaler to 1
    T5CONbits.TCKPS1 = 0;
    T5CONbits.TCKPS2 = 0;
    T5CONbits.TGATE =  0;    // not gated input (the default)
    T5CONbits.TSIDL =  0;    // stop in idle mode off
    T5CONbits.TCS =    1;    // Count External Pulses
    T5CONbits.ON =     1;    // turn on Timer1
    
    // variable to read counter value
    uint16_t count;
    
    while(1)
    {
        count = TMR5;         // get timer5 value
        
        if (count == 5)       // if button pushed 5 times
        {
            LED = 1;          // turn LED on
            delay_ms(1000);
            TMR5 = 0;         // set timer back to 0 
        }
        
        else
        {
            LED = 0;             
        }
        
    }
}
