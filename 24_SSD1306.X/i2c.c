/*
 * File: i2c.c
 * Author: Armstrong Subero
 * Processor: PIC32MX270F256D w/Ext OSC @ 4MHz, PLL to 48 MHz, 3.3v
 * Program: Library file for I2C functions
 * Compiler:  XC32 (v1.44, MPLAX X v4.00)
 * Program Version: 1.1
 *              
 * Program Description: This Library allows you to use the I2C1 module on the
 *                      PIC32MX270F256D microcontroller
 *  
 * Change History:
 *
 * Author             Rev     Date          Description
 * Armstrong Subero   1.0     03/04/2018    Initial Release.
 *                      
 * Updated on April 3rd, 2018, 8:06 PM
 */

/*******************************************************************************
 Includes and defines
*******************************************************************************/
#include "i2c.h"


/*******************************************************************************
* Function Name: void i2c_master_setup(void) 
*
* Specification: Initializes the I2C bus 
*
*******************************************************************************/
void i2c_master_setup(void) 
{
    I2C1BRG = 57;       // 400 kHz
    I2C1CONbits.ON = 1; // turn on the I2C1 module
    
    
}


/*******************************************************************************
* Function Name: void i2c_master_setup(void) 
*
* Specification: Starts a transmission on the I2C bus
*
*******************************************************************************/
void i2c_master_start(void)
{
    I2C1CONbits.SEN = 1;         // send the start bit
    while(I2C1CONbits.SEN) { ; } // wait for the start bit to be sent
}


/*******************************************************************************
* Function Name: void i2c_master_restart(void) 
*
* Specification: master restart function
*
*******************************************************************************/
void i2c_master_restart(void) 
{
    I2C1CONbits.RSEN = 1;         // send a restart
    while(I2C1CONbits.RSEN) { ; } // wait for the restart to clear
}

/*******************************************************************************
* Function Name: void i2c_master_send(unsigned char byte) 
*
* Specification: Sends a byte of data to the I2C slave
*
*******************************************************************************/
void i2c_master_send(unsigned char byte) 
{ 
    I2C1TRN = byte;                  // if an address, bit 0 = 0 for write, 1 for read
    while(I2C1STATbits.TRSTAT) { ; } // wait for the transmission to finish
    if(I2C1STATbits.ACKSTAT) 
    { 
        
    }
}

/*******************************************************************************
* Function Name: unsigned char i2c_master_recv(void)
*
* Specification: Receive a byte of data from slave
*
*******************************************************************************/
unsigned char i2c_master_recv(void) 
{ 
    I2C1CONbits.RCEN = 1;          // start receiving data
    while(!I2C1STATbits.RBF) { ; } // wait to receive the data
    return I2C1RCV;                // read and return the data
}


/*******************************************************************************
* Function Name: void i2c_master_ack(int val)
*
* Specification: Sends ACK = 0 or NACK = 1 in val
*
*******************************************************************************/
void i2c_master_ack(int val) 
{ 
    I2C1CONbits.ACKDT = val;       // store ACK/NACK in ACKDT
    I2C1CONbits.ACKEN = 1;         // send ACKDT
    while(I2C1CONbits.ACKEN) { ; } // wait for ACK/NACK to be sent
}

/*******************************************************************************
* Function Name: void i2c_master_stop(void) 
*
* Specification: Stop transmission on the I2C bus
*
*******************************************************************************/
void i2c_master_stop(void) 
{ 
    // send a STOP:
    I2C1CONbits.PEN = 1;            //master relinquishes bus
    while(I2C1CONbits.PEN) { ; }    // wait for STOP to complete
}

