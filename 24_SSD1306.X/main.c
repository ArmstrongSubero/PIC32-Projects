/*
 * File: Main.c
 * Author: Armstrong Subero
 * Processor: PIC32MX270F256D w/Ext OSC @ 4MHz, PLL to 48 MHz, 3.3v
 * Program: 24_SSD1306
 * Compiler: XC32 (v1.44, MPLAX X v4.00)
 * Program Version: 1.0
 *                             
 * Program Description: This Program Allows PIC32MX270F256D to use the SSD1306
 *                      OLED 
 * 
 * Hardware Description: An SSD1306 OLED is connected to the I2C1 bus.
 * 
 * Change History:
 *
 * Author             Rev     Date          Description
 * Armstrong Subero   1.0     17/09/2018    Initial Release.
 * 
 *                      
 * Created September 17th, 2018, 1:55 PM
 */

/*******************************************************************************
 Includes and defines
*******************************************************************************/
#include <xc.h>
#include <stdio.h>
#include <stdlib.h>
#include "PIC32MX270_STD.h"
#include "Delay.h"
#include "i2c.h"
#include "logoart.c"
#include "SSD1306.h"
  

/*******************************************************************************
* Function Name: void initMain (void)
*
* Specification: initializes main
*
*******************************************************************************/
void initMain(void)
{  
    uc_init();              // initialize microcontroller
    
    i2c_master_setup();        // initialize master I2C
    I2C1CONbits.A10M = 1;
    I2C1CONbits.STRICT = 1;
    delay_ms(1000);
}


/*******************************************************************************
* Function Name: void main (void)
*
* Specification: main function
*
*******************************************************************************/
void main(void) {
    
    initMain();            // initializes main function
    OLED_init();           // initialize the OLED
    delay_ms(1000);
   
    while(1)
    {
      // print string at x = 0, y = 0
      OLED_gotoxy(0,0);   
      OLED_Write_String("Hello World");
    }

}
