/*
 * File: Main.c
 * Author: Armstrong Subero
 * Processor: PIC32MX270F256D w/Ext OSC @ 4MHz, PLL to 48 MHz, 3.3v
 * Program: 22_One Wire
 * Compiler: XC32 (v1.44, MPLAX X v5.05)
 * Program Version: 1.0
 *                             
 * Program Description: This Program Allows PIC32MX270F256D to use the One Wire
 *                      protocol to read a DS1820 microcontroller. 
 * 
 * Hardware Description: A DS1820 Temperature sensor is connected to PIN RC0
 * 
 * Change History:
 *
 * Author             Rev     Date          Description
 * Armstrong Subero   1.0     26/09/2018    Initial Release.
 * 
 *                      
 * Created September 26th, 2018, 9:57 PM
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
#include "onewire.h"

// program variables
char getDat[10];
char TEMP_LSB;
char TEMP_MSB;
int  loop_var;
char far_temp;
char cel_temp;


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

    RPC5Rbits.RPC5R = 0x0001;   //RC5->UART1 TX

    // lock PPS
    CFGCONbits.IOLOCK = 1; 
    systemReg_Lock();
    
    UART1_Initialize(); 
}


/*******************************************************************************
* Function Name: void main (void)
*
* Specification: main function
*
*******************************************************************************/
void main(void) {
    
    initMain();   // initializes main function
    OW_Init();    // initialize OW

    int present;  //var to check for device presence
    
    
    while(1)
    {
        // configure printf to use UART1
        __XC_UART = 1; 
        
        present = OW_Reset();  // see if device is present
        
        if (present == 0)
        {
            printf("Device is Present");
        }
        
        else
        {
            printf("Device not present");
            return;
        }
        
        OW_Reset();                     // reset device
        OW_WriteByte(SKIP_ROM);         //Skip ROM
        OW_WriteByte(START_CONVERSION); // Start Conversion
        delay_ms(5);
        
        OW_Reset();                    // reset device
        OW_WriteByte(SKIP_ROM);        // Skip ROM
        OW_WriteByte(READ_SCRATCHPAD); // Read Scratch Pad
        
        // read scratchpad data
        for(loop_var=0;loop_var<9;loop_var++)
        {
            getDat[loop_var] = OW_ReadByte();
        }
        
        // print scratchpad data
        printf("\n Scratchpad DATA = %X%X%X%X%X\n",getDat[8],getDat[7],getDat[6],
                getDat[5],getDat[4],getDat[3],getDat[2],getDat[1],getDat[0]);
        
        
        // get temperature data
        TEMP_MSB = getDat[1]; // Sign byte + lsbit
        TEMP_LSB = getDat[0]; // Temp data plus lsb
        
        
        if (TEMP_MSB <= 0x80)
        {
            TEMP_LSB = (TEMP_LSB/2); // shift to get whole degree
        } 
        
        TEMP_MSB = TEMP_MSB & 0x80;   // mask all but the sign bit
        
        if (TEMP_MSB >= 0x80)
        {
            TEMP_LSB = (~TEMP_LSB)+1;  // two's complement
        } 
        
       if (TEMP_MSB >= 0x80) 
       {
           TEMP_LSB = (TEMP_LSB/2);    // shift to get whole degree
       }

       if (TEMP_MSB >= 0x80) 
       {
           TEMP_LSB = ((-1)*TEMP_LSB);  // add sign bit
       } 
       
       // print temp in Celsius
       printf( "\nTempC= %d degrees C\n", (int)TEMP_LSB ); 
       
       // convert to Fahrenheit
       cel_temp = TEMP_LSB;         
       far_temp = (((int)cel_temp)* 9)/5 + 32;
       
       // print temp in Farenheit
       printf( "\nTempF= %d degrees F\n", (int)far_temp ); // print temp. F
       
       delay_ms(1000);
 } 
   
}
