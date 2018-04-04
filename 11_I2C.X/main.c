/*
 * File: Main.c
 * Author: Armstrong Subero
 * Processor: PIC32MX270F256D w/Ext OSC @ 4MHz, PLL to 48 MHz, 3.3v
 * Program: 11_I2C
 * Compiler: XC32 (v1.44, MPLAX X v4.00)
 * Program Version: 1.0
 *                             
 * Program Description: This Program Allows PIC32MX270F256D to use the I2C
 *                      module to read and write a 24LC16B EEPROM
 * 
 * Hardware Description: An 24LC16B EEPROM is connected to I2C1
 * 
 * Change History:
 *
 * Author             Rev     Date          Description
 * Armstrong Subero   1.0     03/04/2018    Initial Release.
 * 
 *                      
 * Created April 3rd, 2018, 8:02 PM
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
#include "i2c.h"
#include <string.h>

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
    TRISBbits.TRISB14 = 0;      // set PINB1 as output
    
    // unlock PPS
    systemReg_Unlock();
    CFGCONbits.IOLOCK = 0;

    RPC5Rbits.RPC5R = 0x0001;   //RC5->UART1 TX

    // lock PPS
    CFGCONbits.IOLOCK = 1; 
    systemReg_Lock();
    
    i2c_master_setup();        // initialize master I2C
    UART1_Initialize();        // initialize UART
}


/*******************************************************************************
* Function Name: void main (void)
*
* Specification: main function
*
*******************************************************************************/
void main(void) {
    
    initMain();                         // initializes main function
    __XC_UART = 1;                      // configure printf to use UART1
      
    unsigned int incoming_data;         // variable to store read value
   
    while(1)
    {
      printf("Write begin\n");           // start write
      i2c_master_start();                // issue I2C start signal
      i2c_master_send(0xA2);             // send byte via I2C  (device address + W)
      i2c_master_send(2);                // send byte (address of EEPROM location)
      i2c_master_send(0x01);             // send data (data to be written)
      i2c_master_stop();                 // issue I2C stop signal
      delay_ms(100);                     // wait 100 ms
      printf("Write end\n");             // end write
      
      
      printf("Read begin\n");            // start read
      i2c_master_start();                // issue I2C start signal
      i2c_master_send(0xA2);             // send byte via I2C  (device address + W)
      i2c_master_send(2);                // send byte (data address)
      i2c_master_restart();              // issue I2C signal repeated start
      i2c_master_send(0xA3);             // send byte (device address + R)
      incoming_data = i2c_master_recv(); // Read the data
      i2c_master_ack(1);                 // send NACK
      i2c_master_stop();                 // issue I2C stop signal 
      printf("Read end\n");              // end read
 
    
      printf("%d\n", incoming_data);     // print read value
      delay_ms(1000);                    // delay 1 second
    }
}
