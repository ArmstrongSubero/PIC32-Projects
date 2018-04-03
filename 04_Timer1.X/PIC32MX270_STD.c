/*
 * File: Delay_32.c
 * Author: Armstrong Subero
 * Processor: PIC32MX270F256D w/Ext OSC @ 4MHz, PLL to 48 MHz, 3.3v
 * Program: Library file for Standard setup
 * Compiler:  XC32 (v1.44, MPLAX X v4.00)
 * Program Version: 1.1
 *              
 * Program Description: This Library allows you to setup the PIC32MX270F256D
 * 
 * Modified From: Microchip Forums
 *  
 * 
 * Change History:
 *
 * Author             Rev     Date          Description
 * Armstrong Subero   1.0     08/02/2015    Initial Release.
 * Armstrong Subero   1.1     02/04/2018    Changed to accommodate 270F256D from
 *                                          230F064D 
 *                                          Removed dependency on Legacy Lib
 *                      
 * Updated on April 2nd, 2018, 9:13 PM
 */


/*******************************************************************************
 Includes and defines
*******************************************************************************/
#include "PIC32MX270_STD.h"

// DEVCFG3
#pragma config PMDL1WAY = ON      // Peripheral Module Disable Configuration->Allow only one reconfiguration
#pragma config IOL1WAY = ON       // Peripheral Pin Select Configuration->Allow only one reconfiguration
#pragma config FUSBIDIO = ON      // USB USID Selection->Controlled by the USB Module
#pragma config FVBUSONIO = ON     // USB VBUS ON Selection->Controlled by USB Module

// DEVCFG2
#pragma config FPLLIDIV = DIV_1   // PLL Input Divider->1x Divider
#pragma config FPLLMUL = MUL_24   // PLL Multiplier->24x Multiplier
#pragma config UPLLIDIV = DIV_12  // USB PLL Input Divider->12x Divider
#pragma config UPLLEN = OFF       // USB PLL Enable->Disabled and Bypassed
#pragma config FPLLODIV = DIV_2   // System PLL Output Clock Divider->PLL Divide by 2

// DEVCFG1
#pragma config FNOSC = PRIPLL       // Oscillator Selection Bits->Primary Osc w/PLL (XT+,HS+,EC+PLL)
#pragma config FSOSCEN = ON         // Secondary Oscillator Enable->Enabled
#pragma config IESO = ON            // Internal/External Switch Over->Enabled
#pragma config POSCMOD = XT         // Primary Oscillator Configuration->XT osc mode
#pragma config OSCIOFNC = OFF       // CLKO Output Signal Active on the OSCO Pin->Disabled
#pragma config FPBDIV = DIV_1       // Peripheral Clock Divisor->Pb_Clk is Sys_Clk
#pragma config FCKSM = CSDCMD       // Clock Switching and Monitor Selection->Clock Switch Disable, FSCM Disabled
#pragma config WDTPS = PS1048576    // Watchdog Timer Postscaler->1:1048576
#pragma config WINDIS = OFF         // Watchdog Timer Window Enable->Watchdog Timer is in Non-Window Mode
#pragma config FWDTEN = OFF         // Watchdog Timer Enable->WDT Disabled (SWDTEN Bit Controls)
#pragma config FWDTWINSZ = WINSZ_25 // Watchdog Timer Window Size->Window Size is 25%

// DEVCFG0
#pragma config DEBUG = OFF        // Background Debugger Enable->Debugger is Disabled
#pragma config JTAGEN = ON        // JTAG Enable->JTAG Port Enabled
#pragma config ICESEL = ICS_PGx3  // ICE/ICD Comm Channel Select->Communicate on PGEC3/PGED3
#pragma config PWP = OFF          // Program Flash Write Protect->Disable
#pragma config BWP = OFF          // Boot Flash Write Protect bit->Protection Disabled
#pragma config CP = OFF           // Code Protect->Protection Disabled


/*******************************************************************************
* Function: void systemReg_Unlock(void)
*
* Returns: Nothing
*
* Description: System register unlock sequence
*
*******************************************************************************/
void systemReg_Unlock(void)
{
   SYSKEY = 0x12345678;
   SYSKEY = 0xAA996655;
   SYSKEY = 0x556699AA; 
}

/*******************************************************************************
* Function: void systemReg_Lock(void)
*
* Returns: Nothing
*
* Description: System register lock sequence
*
*******************************************************************************/
void systemReg_Lock(void)
{
     SYSKEY = 0x00000000;  
}


/*******************************************************************************
* Function: void uc_init(void)
*
* Returns: Nothing
*
* Description: Setup oscillator
*
*******************************************************************************/
void uc_init(void)
{
    // system reg unlock
    systemReg_Unlock();
    
    // configure oscillator
    OSCCON = 0x80F3300;
     
    // system reg lock
    systemReg_Lock();
    
    // tune oscillator centre frequency
    OSCTUN = 0x0;
    
    // configure reference
    REFOCON = 0x100;
    
    // configure reference oscillator trim register
    REFOTRIM = 0x0;   
    
}
