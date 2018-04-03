/*
 * File: Main.c
 * Author: Armstrong Subero
 * Processor: PIC32MX270F256D w/Ext OSC @ 4MHz, PLL to 48 MHz, 3.3v
 * Program: 08_Output_Compare
 * Compiler: XC32 (v1.44, MPLAX X v4.00)
 * Program Version: 1.0
 *                             
 * Program Description: This Program Allows PIC32MX270F256D to generate a 10 kHz
 *                      square wave using the output capture module on channel 1
 *                      that varies from 0 to 100% duty cycle.
 *                      
 * Hardware Description: An oscilloscope probe is connected to PIN B4
 * 
 * Change History:
 *
 * Author             Rev     Date          Description
 * Armstrong Subero   1.0     02/04/2018    Initial Release.
 * 
 *                      
 * Created April 2nd, 2018, 9:24 PM
 */

/*******************************************************************************
 Includes and defines
*******************************************************************************/
#include <xc.h>
#include "PIC32MX270_STD.h"
#include "Delay.h"

#define LED LATBbits.LATB14

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

    RPB4Rbits.RPB4R = 0x0005;   //RB4->OC1

    // lock PPS
    CFGCONbits.IOLOCK = 1;
    systemReg_Lock();
    
    /////////////////////
    // Configure Timer2
    /////////////////////
    T2CONbits.TCKPS0 = 0;       // Timer2 Prescale 1:1
    T2CONbits.TCKPS1 = 0;
    T2CONbits.TCKPS2 = 0;
    
    // Period = (PR + 1 ) * Prescale * 41.667 (PBCLK = 24 MHz)
    // Period = 2400 * 1 * 41.667 = ~ 10 kHz 
    PR2 = 2399;
    TMR2 = 0;                  // TMR2 count = 0
    
    ////////////////////
    // Configure PWM
    ///////////////////
    OC1CONbits.OCM0 = 0;       // PWM mode, fault pin disabled
    OC1CONbits.OCM1 = 1;
    OC1CONbits.OCM2 = 1; 
    OC1CONbits.OCTSEL = 0;     // Timer2 is clock source
    OC1CONbits.OC32 = 0;       // 16-bit timer source
    OC1CONbits.SIDL =  0;      // continue operation in IDLE mode
    
    // duty cycle = OCRS/PR+1 = 50%
    OC1RS = 1200;              // secondary value  
    OC1R = 1200;               // primary value  
    
    T2CONbits.ON = 1;          // turn Timer2 on
    OC1CONbits.ON = 1;         // turn OC1 on
}


/*******************************************************************************
* Function Name: void main (void)
*
* Specification: main function
*
*******************************************************************************/
void main(void) {
    
    initMain();         // initializes main function
    
    uint16_t i;
    uint16_t value = 0;
    
    while(1)
    {
        // vary duty cycle from  0 to 100%
        for (i = 0; i <= 2400; i++)
        {
            value = i;
            OC1RS = value;
            delay_us(500);
        } 
    }
}
