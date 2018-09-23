#include "PIC32MX270_USB.h"

// *****************************************************************************
// Configuration Bits
// *****************************************************************************

// DEVCFG3
#pragma config PMDL1WAY = ON            // Peripheral Module Disable Configuration (Allow only one reconfiguration)
#pragma config IOL1WAY  = ON             // Peripheral Pin Select Configuration (Allow only one reconfiguration)
#pragma config FUSBIDIO = ON            // USB USID Selection (Controlled by the USB Module)
#pragma config FVBUSONIO = OFF          // USB VBUS ON Selection (Controlled by Port Function)

// DEVCFG2
#pragma config FPLLIDIV = DIV_1         // PLL Input Divider (1x Divider)
#pragma config FPLLMUL = MUL_24        // PLL Multiplier (24x Multiplier)
#pragma config FPLLODIV = DIV_2         // System PLL Output Clock Divider (PLL Divide by 2, run at 48 Mhz)
#pragma config UPLLIDIV = DIV_1         // USB PLL Input Divider (4 MHz Input)
#pragma config UPLLEN = ON              // USB PLL Enable (Enabled)

// DEVCFG1
#pragma config FNOSC = PRIPLL           // Oscillator Selection Bits (Primary Osc w/PLL (XT+,HS+,EC+PLL))
#pragma config FSOSCEN = OFF            // Secondary Oscillator Enable (Disabled)
#pragma config IESO = OFF               // Internal/External Switch Over (Disabled)
#pragma config POSCMOD = XT             // Primary Oscillator Configuration (Primary osc XT)
#pragma config OSCIOFNC = OFF           // CLKO Output Signal Active on the OSCO Pin (Disabled)
#pragma config FPBDIV = DIV_2          // Peripheral Clock Divisor (Pb_Clk is Sys_Clk/8)
#pragma config FCKSM = CSDCMD           // Clock Switching and Monitor Selection (Clock Switch Disable, FSCM Disabled)
#pragma config WDTPS = PS1048576        // Watchdog Timer Postscaler (1:1048576)
#pragma config WINDIS = OFF             // Watchdog Timer Window Enable (Watchdog Timer is in Non-Window Mode)
#pragma config FWDTEN = OFF             // Watchdog Timer Enable (WDT Disabled (SWDTEN Bit Controls))

// DEVCFG0
#pragma config JTAGEN = OFF             // JTAG Enable (JTAG Disabled)
#pragma config ICESEL = ICS_PGx3        // ICE/ICD Comm Channel Select (Communicate on PGEC1/PGED1)
#pragma config PWP = OFF                // Program Flash Write Protect (Disable)
#pragma config BWP = OFF                // Boot Flash Write Protect bit (Protection Disabled)
#pragma config CP = OFF                 // Code Protect (Protection Disabled)


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
