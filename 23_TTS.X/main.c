/*
 * File: Main.c
 * Author: Armstrong Subero
 * Processor: PIC32MX270F256D w/Ext OSC @ 4MHz, PLL to 48 MHz, 3.3v
 * Program: 23_TTS
 * Compiler: XC32 (v1.44, MPLAX X v5.05)
 * Program Version: 1.0
 *                             
 * Program Description: This Program Allows PIC32MX270F256D to use the PWM 
 *                      module to perform TTS.
 * 
 * Hardware Description: A PAM8610 is connected to RB4 and a CP4104 USB-UART 
 *                       bridge is connected to RC5.
 * 
 * Change History:
 *
 * Author             Rev     Date          Description
 * Armstrong Subero   1.0     27/11/2018    Initial Release.
 * 
 * Modified From: Inspired by the www.toughdev.com project.
 *                      
 * Created September 27th, 2018, 1:15 PM
 */


/*******************************************************************************
 * Includes and Defines
 ******************************************************************************/
#include "PIC32MX270_STD.h"
#include "delay.h"
#include "uart1.h"
#include <string.h>
#include <stdlib.h>
#include <stdio.h>
#include "sam.h"
#include "reciter.h"
#include "tts.h"

/*******************************************************************************
* Function Name: void initMain(void)
*
* Specification: initializes main
*
*******************************************************************************/
void initMain(void)
{
    // unlock PPS
    systemReg_Unlock();
    CFGCONbits.IOLOCK = 0;

    RPB4Rbits.RPB4R = 0x0005;   //RB4->OC1
    RPC5Rbits.RPC5R = 0x0001;   //RC5->UART1 TX

    // lock PPS
    CFGCONbits.IOLOCK = 1;
    systemReg_Lock();   
}


int main()
{	
    uc_init();
    initMain();
    
    // initialize UART
    UART1_Initialize(); 
    delay_ms(300);
    
    // initialize the TTS module
    initTTS();
	
	while(1)
	{
	  // configure printf to use UART1
      __XC_UART = 1; 
      
      // begin speaking
      printf("Begin");
      
      // speak text
      speakText("Hello");
      delay_ms(500);
      speakText("I am SAM");
      delay_ms(500);
      speakText("Would you like to play a gayme?");
      delay_ms(500);
      
      // end speaking
      printf("End");
    }
}
