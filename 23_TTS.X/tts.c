/*
 * File: tts.c
 * Author: Armstrong Subero
 * Processor: PIC32MX270F256D w/Ext OSC @ 4MHz, PLL to 48 MHz, 3.3v
 * Program: Library file for TTS setup
 * Compiler:  XC32 (v1.44, MPLAX X v5.05)
 * Program Version: 1.1
 *              
 * Program Description: This Library allows you to setup TTS for PIC32MX270F256D
 * 
 * Change History:
 *
 * Author             Rev     Date          Description
 * Armstrong Subero   1.0     27/11/2018    Initial Release.
 *                      
 * Updated on September 27th, 2018, 1:12 PM
 */


/*******************************************************************************
 * Includes and defines
 ******************************************************************************/
#include "tts.h"

/*******************************************************************************
* Function: void initTTS(void)
*
* Returns: Nothing
*
* Description: Initializes Timer2 and OC1 for TTS
*
*******************************************************************************/
void initTTS(void)
{
    PR2 = 100;                 // 101
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