/*
 * File: Main.c
 * Author: Armstrong Subero
 * Processor: PIC32MX270F256D w/Ext OSC @ 4MHz, PLL to 48 MHz, 3.3v
 * Program: 02_Switch
 * Compiler: XC32 (v1.44, MPLAX X v4.00)
 * Program Version: 1.0
 *                             
 * Program Description: This Program Allows PIC32MX270F256D to turn on an LED
 *                      when a pushbutton is pressed
 * 
 * Hardware Description: An LED is connected via a 1k resistor to PIN RB14 and
 *                       a switch is connected to PIN
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
}


/*******************************************************************************
* Function Name: void main (void)
*
* Specification: main function
*
*******************************************************************************/
void main(void) {
    
    initMain();         // initializes main function
    
    while(1)
    {
        if(SWITCH == 0)
        {
            LED = HIGH;
        }
        
        else
        {
            LED = LOW;
        }
    }
}
