/*
 * File: DS1820.c
 * Author: Armstrong Subero
 * Processor: PIC32MX270F256D w/Ext OSC @ 4MHz, PLL to 48 MHz, 3.3v
 * Program: Library file for DS1820 
 * Compiler:  XC32 (v1.44, MPLAX X v5.05)
 * Program Version: 1.1
 *              
 * Program Description: This Library allows you to setup the PIC32MX270F256D with
 *                      a DS1820 temperature sensor
 * 
 * Modified From: Microchip Forums
 *  
 * 
 * Change History:
 *
 * Author             Rev     Date          Description
 * Armstrong Subero   1.0     26/09/2018    Initial Release.
 *                      
 * Updated on April 2nd, 2018, 10:20 PM
 */

/*******************************************************************************
 * Includes and defines
 ******************************************************************************/
#include "onewire.h"


/*******************************************************************************
* Function: void OW_Init(void)
*
* Returns: Nothing
*
* Description: Initializes pin with the one wire protocol
*
*******************************************************************************/
void OW_Init(void)
{
    OW_Analog = 0;
}

/*******************************************************************************
* Function: unsigned char OW_Reset(void)
*
* Returns: Nothing
*
* Description: Issues one wire reset signal for the DS1820
*
*******************************************************************************/
unsigned char OW_Reset(void)
{
    TRISCbits.TRISC0 = 0;   // set as output  
    OW_Pin = 0;             //pull line low
    delay_us(480);          // leave it low for 480us

    TRISCbits.TRISC0 = 1;   // set as input
    
    delay_us(60);           // wait for presence
    
    if (OW_Pin == 0)        // 0 is detected
    {
        delay_us(480);
        return 0;
    }
    
    else                    // 1 is not detected  
    {
        delay_us(480);
        return 1;
    }
} 

/*******************************************************************************
* Function: unsigned char OW_ReadBit() 
*
* Returns: Nothing
*
* Description: reads one bit of data via the OneWire bus
*
*******************************************************************************/
unsigned char OW_ReadBit() 
{
  unsigned char result;

  OW_Dir = 0;       // set as output
  OW_Pin = 0;       // set high
  delay_us(1);      // 1 us delay
  
  OW_Dir = 1;       // set as input
  delay_us(5);      // 5 us delay
  
  result = OW_Pin;  // read pin
  delay_us(55);     // 55 us delay
  
  return result;    // return result
}


/*******************************************************************************
* Function: void OW_WriteBit(int b)
*
* Returns: Nothing
*
* Description: writes one bit of data via the OneWire bus
*
*******************************************************************************/
void OW_WriteBit(int b) 
{
    b = b & 0x01;    // AND 0x01
    
    if (b) 
    {
        OW_Dir = 0;   // set as output
        OW_Pin = 0;   // set high
        delay_us(5);  // 5 us delay
        
        OW_Dir = 1;   // set as input
        delay_us(60); // 60 us delay
    } 
    else 
    {
        OW_Dir = 0;   // set as output
        OW_Pin = 0;   // set high
        delay_us(70); // 70 us delay
        
        OW_Dir = 1;   // set as input
        delay_us(2);  // 2 us delay
  }
}

/*******************************************************************************
* Function: unsigned char OW_ReadByte() 
*
* Returns: Nothing
*
* Description: reads one byte of data via the OneWire bus
*
*******************************************************************************/
unsigned char OW_ReadByte(void)
{
    unsigned char i;
    unsigned char value = 0;
    
    for (i=0;i<8;i++)
    {
        // read byte in and shift left
        if(OW_ReadBit()) 
        {
            value|=0x01<<i;
        }
    } 
    
    delay_ms(6);  // delay 6 ms
    
    return(value);
}

/*******************************************************************************
* Function: void OW_WriteBbyte (char val)
*
* Returns: Nothing
*
* Description: writes one byte of data via the OneWire bus
*
*******************************************************************************/
void OW_WriteByte(char val)
{
    unsigned char i;
    unsigned char temp;
    
    // write byte and shift val right inc spaces, then write bit
    for (i=0; i<8; i++) 
    {
        temp = val>>i;
        temp &= 0x01;
        OW_WriteBit(temp); 
    }
    delay_ms(5);
}


