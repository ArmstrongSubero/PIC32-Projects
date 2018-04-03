/*
 * File: Main.c
 * Author: Armstrong Subero
 * Processor: PIC32MX270F256D w/Ext OSC @ 4MHz, PLL to 48 MHz, 3.3v
 * Program: 04_Timer1
 * Compiler: XC32 (v1.44, MPLAX X v4.00)
 * Program Version: 1.0
 *                             
 * Program Description: This Program Allows PIC32MX270F256D to use Timer1 to
 *                      generate an interrupt which flashes an LED
 * 
 * Hardware Description: An LED is connected via a 1k resistor to PIN RB14 
 * 
 * Change History:
 *
 * Author             Rev     Date          Description
 * Armstrong Subero   1.0     02/04/2018    Initial Release.
 * 
 *                      
 * Created April 2nd, 2018, 10:06 PM
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
* Function Name: void __ISR(_TIMER_1_VECTOR, IPL1SOFT) Timer1ISR (void)
*
* Specification: interrupt routine for external interrupt on PINB7 (INT0)
*
*******************************************************************************/
void __ISR(_TIMER_1_VECTOR, IPL1SOFT) Timer1ISR (void)
{
    // Toggle LED
    
    LATBbits.LATB14 = !LATBbits.LATB14;
    
    IFS0bits.T1IF = 0;
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
    
     __builtin_disable_interrupts();  // disable interrupts    
    
    // Calculate time T (ms) = CLK / PR1 + 1 with pre-scale of 256
    PR1 = 47999;            // set period register
    TMR1 = 0;               // initialize count to 0
    T1CONbits.TCKPS0 = 1;   // set prescaler to 256
    T1CONbits.TCKPS1 = 1;
    T1CONbits.TGATE = 0;    // not gated input (the default)
    T1CONbits.TSIDL = 0;    // stop in idle mode off
    T1CONbits.TSYNC = 0;    // external clock synchonization bit disabled
    T1CONbits.TCS = 0;      // PCBLK input (the default)
    T1CONbits.ON = 1;       // turn on Timer1
    
    IPC1bits.T1IP = 1;               // timer1 interrupt priority
    IPC1bits.T1IS = 0;               // timer1 sub-priority
    IFS0bits.T1IF = 0;               // clear interrupt flag
    IEC0bits.T1IE = 1;               // enable timer1 interrupt
    INTCONbits.MVEC = 1;             //  Enable the multi vector interrupts
    __builtin_enable_interrupts();   // enable interrupts
    
    while(1)
    {
       // do nothing
    }
}
