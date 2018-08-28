/*
 * File: Main.c
 * Author: Armstrong Subero
 * Processor: PIC32MX270F256D w/Ext OSC @ 4MHz, PLL to 48 MHz, 3.3v
 * Program: 21_RTCC
 * Compiler: XC32 (v1.44, MPLAX X v4.00)
 * Program Version: 1.0
 *                             
 * Program Description: This Program Allows PIC32MX270F256D to use the on board
 *                      RTCC module. The UART drivers are taken from MCC provided 
 *                      by Microchip and printf is remmapped to UART1
 * 
 * Hardware Description: An CP2104 USB-UART converter is connected to PINC5 and
 *                       a 32.768 kHz crystal oscillator is connected with 22 pF
 *                       caps to pins RB4 and RA4. 
 * Change History:
 *
 * Author             Rev     Date          Description
 * Armstrong Subero   1.0     02/04/2018    Initial Release.
 * 
 *                      
 * Created August 28th, 2018, 2:00 PM
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

    RPC5Rbits.RPC5R = 0x0001;  //RC5->UART1 TX
    
    OSCCONSET=_OSCCON_SOSCEN_MASK;    // enable SOSC
    RTCCONSET=_RTCCON_RTCWREN_MASK;   // enable RTCC writes

    // lock PPS
    CFGCONbits.IOLOCK = 1; 
    systemReg_Lock();
    
    UART1_Initialize(); 
}

void rtcc_init()
{
    unsigned long time=0x04153300; // set time to 04 hr, 15 min, 33 sec
    unsigned long date=0x18082705; // set date to Friday 27 August 2018
    RTCCONCLR=0x8000;              // turn off the RTCC
    while(RTCCON&0x40);            // wait for clock to be turned off
    RTCTIME=time;                  // safe to update the time
    RTCDATE=date;                  // update the date
    RTCCONSET=0x8000;              // turn on the RTCC
    while(!(RTCCON&0x40));         // wait for clock to start running
}

/*******************************************************************************
* Function Name: void main (void)
*
* Specification: main function
*
*******************************************************************************/
void main(void) {
    
    initMain();         // initializes main function
    rtcc_init();        // initializes the RTCC
    
    uint8_t sec_o;      // seconds ones 
    uint8_t sec_t;      // seconds tens
   

    while(1)
    {
      // configure printf to use UART1
      __XC_UART = 1;
  
      // Read Seconds
      sec_o = RTCTIMEbits.SEC01;
      sec_t = RTCTIMEbits.SEC10;
      
      // Send seconds via UART
      printf("%d%d\n", sec_t, sec_o);
      delay_ms(1000);
   }
}
