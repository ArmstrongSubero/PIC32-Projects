/*
 * File: Main.c
 * Author: Armstrong Subero
 * Processor: PIC32MX270F256D w/Ext OSC @ 4MHz, PLL to 48 MHz, 3.3v
 * Program: 09_Input_Capture
 * Compiler: XC32 (v1.44, MPLAX X v4.00)
 * Program Version: 1.0
 *                             
 * Program Description: This Program Allows PIC32MX270F256D to use the input 
 *                      capture module to determine the frequency of a square
 *                      wave. The program used the OC module to generate a 
 *                      1 kHz square wave at 50% duty cycle that is measured 
 *                      by the input capture module.
 * 
 * Hardware Description: An jumper wire is connected from PIN RB2 to PIN RB4 
 * 
 * Change History:
 *
 * Author             Rev     Date          Description
 * Armstrong Subero   1.0     03/04/2018    Initial Release.
 * 
 *                      
 * Created April 3rd, 2018, 3:47 PM
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
    TRISBbits.TRISB14 = 0;  // set PINB14 as output
    TRISBbits.TRISB2 = 1;
    ANSELBbits.ANSB2 = 0;
    
    // unlock PPS
    systemReg_Unlock();
    CFGCONbits.IOLOCK = 0;

    RPC5Rbits.RPC5R = 0x0001;   //RC5->UART1 TX
    RPB4Rbits.RPB4R = 0x0005;   //RB4->OC1
    IC1Rbits.IC1R = 0x0004;     //RB2->IC1

    // lock PPS
    CFGCONbits.IOLOCK = 1; 
    systemReg_Lock();
    
    
    __builtin_disable_interrupts();   // disable interrupts
    
    /////////////////////
    // Configure Timer2
    // for OC
    /////////////////////
    T2CONbits.TCKPS0 = 1;      // prescale 1:2, ticks at 12 MHz, 83.3333 ns
    T2CONbits.TCKPS1 = 0;
    T2CONbits.TCKPS2 = 0;
    PR2 = 11999;               // rollover every 12,000 ticks or 1 ms (1kHz)
    TMR2 = 0;                  // zero timer2
    
    
    /////////////////////
    // Configure Timer3
    // for IC
    /////////////////////
    T2CONbits.TCKPS0 = 1;      // prescale 1:2, ticks at 12 MHz, 83.3333 ns
    T2CONbits.TCKPS1 = 0;
    T2CONbits.TCKPS2 = 0;
    PR3 = 0xFFFF;                     
    TMR3 = 0;                  // clear timer 3
    
    
    ////////////////////
    // Configure OC
    ///////////////////
    OC1CONbits.OCM0 = 0;       // PWM mode, fault pin disabled
    OC1CONbits.OCM1 = 1;
    OC1CONbits.OCM2 = 1; 
    OC1CONbits.OCTSEL = 0;     // Timer2 is clock source
    OC1CONbits.OC32 = 0;       // 16-bit timer source
    OC1CONbits.SIDL =  0;      // continue operation in IDLE mode
    
    ////////////////////
    // Configure IC
    ///////////////////
    IC1CONbits.ICTMR = 0;      // use timer 3
    IC1CONbits.ICM0  = 1;      // capture every edge
    IC1CONbits.ICM1  = 0;
    IC1CONbits.ICM2  = 0;
    IC1CONbits.FEDGE = 1;      // capture rising edge
    IC1CONbits.ICI0  = 0;      // interrupt every edge
    IC1CONbits.ICI1  = 0;     
    IEC0bits.IC1IE   = 1;      // enable IC1 interrupt
    
    T2CONbits.ON =  1;          // turn Timer2 on
    T3CONbits.ON =  1;          // turn Timer3 on
    OC1CONbits.ON = 1;          // turn OC1 on
    IC1CONbits.ON = 1;          // turn IC1 on
    
    __builtin_enable_interrupts();   // enable interrupts
           
    
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
    
    unsigned long val1;
    unsigned long val2;
    unsigned long period;
    float freq;
    
    OC1RS = 6000;       // set duty cycle to 50%
    
    float freq_timer = 12000000.0;  // timer frequency is PBCLK/2
    
    while(1)
    {
      // configure printf to use UART1
      __XC_UART = 1;
      
      
     while(!IFS0bits.IC1IF);      // wait for interrupt
     
     if(!(!IC1CONbits.ICBNE))     // if capture buffer is not empty
     {
        IFS0bits.IC1IF = 0;       // clear interrupt flag
        val1 = IC1BUF;            // read value from IC1BUF
     }
     
     
     while(!IFS0bits.IC1IF);
     if(!(!IC1CONbits.ICBNE))
     {
        IFS0bits.IC1IF = 0;
        val2 = IC1BUF;
     }
     
      
     // begin frequency calculation 
     if (val1 < val2)
     {
         period = val2 - val1;             // determine signal period 
         freq = (freq_timer / period);     // calculate frequency
         
     }
              
      printf("Frequency: %.2f\n", freq);  // print frequency
    }
}
