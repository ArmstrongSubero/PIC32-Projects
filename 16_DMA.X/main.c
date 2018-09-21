/*
 * File: Main.c
 * Author: Armstrong Subero
 * Processor: PIC32MX270F256D w/Ext OSC @ 4MHz, PLL to 48 MHz, 3.3v
 * Program: 16_DMA
 * Compiler: XC32 (v1.44, MPLAX X v4.00)
 * Program Version: 1.0
 *                             
 * Program Description: This Program Allows PIC32MX270F256D to use the DMA 
 *                      controller to transfer data to PORTC of the 
 *                      microcontroller.
 * 
 * Hardware Description: Three LED's are connected to the lower bits of PORTC
 *                       on the microcontroller via 1k resistors. 
 * 
 * Change History:
 *
 * Author             Rev     Date          Description
 * Armstrong Subero   1.0     21/09/2018    Initial Release.
 * 
 *                      
 * Created September 21st, 2018, 12:20 PM
 */

/*******************************************************************************
 Includes and defines
*******************************************************************************/
#include <xc.h>
#include <stdio.h>
#include <stdlib.h>
#include "PIC32MX270_STD.h"
#include "Delay.h"

uint32_t srcAddr;
uint32_t dstAddr;

const uint8_t outData[] = {0b00000101, 0b00000010, 0b00000110, 0b00000011};

/*******************************************************************************
* Function Name: void __ISR(_TIMER_5_VECTOR, IPL1SOFT) Timer5ISR (void)
*
* Specification: interrupt routine for Timer5
*
*******************************************************************************/
void __ISR(_TIMER_5_VECTOR, IPL1SOFT) Timer5ISR (void)
{
    // On interrupt clear the interrupt flag
    IFS0bits.T5IF = 0;
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
}


/*******************************************************************************
* Function Name: void main (void)
*
* Specification: main function
*
*******************************************************************************/
void main(void) {
    
    initMain();         // initializes main function
    TRISC = 0;          // set destination TRIS to 0
    
    ////////////////////////////////
    // Source and Destination
    ////////////////////////////////
    srcAddr = (uint32_t) &outData & 0x1FFFFFFF;   // source address 
    dstAddr = (uint32_t) &LATC    & 0x1FFFFFFF;   // destination address 
    
    ///////////////////////////////
    //Initialize timer 5 
    ///////////////////////////////
    PR5 = 47999;          // (ms) = CLK / PR1 + 1 with pre-scale of 256 = 1000 ms
    T5CONbits.TCKPS0 = 1; // set prescaler to 256
    T5CONbits.TCKPS1 = 1;
    T5CONbits.TCKPS2 = 1;
    T5CONbits.TGATE =  0;  // not gated input (the default)
    T5CONbits.TSIDL =  0;  // stop in idle mode off
    T5CONbits.TCS =    0;  // PCBLK input (the default)
    T5CONbits.ON =     0;  // ensure timer 5 is off
    
    /////////////////////////////////
    // Initialize timer 5 interrupts
    /////////////////////////////////
    __builtin_disable_interrupts(); // disable interrupts    
    IPC5bits.T5IP = 1;              // timer5 interrupt priority
    IPC5bits.T5IS = 0;              // timer5 sub-priority
    IFS0bits.T5IF = 0;              // clear interrupt flag
    IEC0bits.T5IE = 1;              // enable timer5 interrupt
    INTCONbits.MVEC = 1;            // enable the multi vector interrupts
    __builtin_enable_interrupts();  // enable interrupts
    
    
    ////////////////////////////
    // Initialize DMA module
    ///////////////////////////
    DMACONbits.ON = 1;                 // DMA module on
    DCH0INT = 0;                       // no DMA interrupts being used
    DCH0SSA = srcAddr;                 // channel source start addr
    DCH0DSA = dstAddr;                 // destination source start addr
    DCH0SSIZ = 4;                      // size of source      (4 bytes)
    DCH0DSIZ = 1;                      // size of destination (1 byte)
    DCH0CSIZ = 1;                      // size of cell        (1 byte)
    DCH0ECONbits.SIRQEN = 1;           // cell transfer on CHSIRQ matching int
    DCH0ECONbits.CHSIRQ = 0b00011000;  // DMA transfer on interrupt 24 (Timer5)
    

    ////////////////////////////////
    // Enable DMA
    ///////////////////////////////
    DCH0CON = 0b10010011; // priority 3, auto enable, no chain, ignore events,on
       
    // turn on timer5
    T5CONbits.ON = 1;
    
    while(1)
    {
      // do nothing completely CPU free
    }
}

