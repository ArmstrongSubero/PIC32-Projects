/*
 * File: Main.c
 * Author: Armstrong Subero
 * Processor: PIC32MX270F256D w/Ext OSC @ 4MHz, PLL to 48 MHz, 3.3v
 * Program: 47_State_Machines
 * Compiler: XC32 (v1.44, MPLAX X v4.00)
 * Program Version: 1.0
 *                             
 * Program Description: This Program Allows PIC32MX270F256D to jump between 
 *                      four state machines. The user will be notified which 
 *                      state the machine is in.
 * 
 * Hardware Description: A ST7735 LCD is connected as follows:
 *                       RST    -> RC3
 *                       CS     -> RC4
 *                       RS     -> RC5
 *                       DIN    -> RA9
 *                       CLK    -> RB15
 *                       VCC    -> VCC
 *                       BL     -> VCC via 10k
 *                       GND    -> GND
 *  
 * Change History:
 *
 * Author             Rev     Date          Description
 * Armstrong Subero   1.0     09/04/2018    Initial Release.
 * 
 *                      
 * Created April 9th, 2018, 5:09 PM
 */

/*******************************************************************************
 Includes and defines
*******************************************************************************/
#include <xc.h>
#include <stdio.h>
#include <stdlib.h>
#include "PIC32MX270_STD.h"
#include "Delay.h"
#include "ST7735.h"
#include "spi2.h"


// Number of states for State Machine
#define NUM_STATES 4

/*******************************************************************************
* Function Prototypes
*******************************************************************************/
void initMain(void);

void SM_STATE_ONE(void);      // A state
void SM_STATE_TWO(void);      // B State
void SM_STATE_THREE(void);    // C state
void SM_STATE_FOUR(void);     // D state
void RUN_STATEMACHINE (void); // Run state machine

 // enum of each state
 typedef enum
 {
     STATE_ONE,
     STATE_TWO,
     STATE_THREE,
     STATE_FOUR
 }StateType;

 // define state machine table structure
 typedef struct
 {
     StateType State;       // Define the command
     void(*func)(void);     // Defines the function to run
 }StateMachineType;
 
// Table that defines valid states of the SM and function to be executed for 
StateMachineType StateMachine[] =
 {
     {STATE_ONE, SM_STATE_ONE},
     {STATE_TWO, SM_STATE_TWO},
     {STATE_THREE, SM_STATE_THREE},
     {STATE_FOUR, SM_STATE_FOUR}
 };

// Store current state of state machine
StateType SM_STATE = STATE_ONE;


/*******************************************************************************
 * Function:        void SM_STATE_ONE(void)
 *
 * PreCondition:    Table structure for states should have been initialized
 *                  as well as enum for each state
 *
 * Overview:        State A 
 ******************************************************************************/
void SM_STATE_ONE(void)
{
    ST7735_fillScreen(colWhite);
    ST7735_drawString(1, 1, "State One", colMagenta, 2);
    delay_ms(1000);
   
    
    SM_STATE = STATE_TWO;
}


/*******************************************************************************
 * Function:        void SM_STATE_TWO(void)
 *
 * PreCondition:    Table structure for states should have been initialized
 *                  as well as enum for each state
 *
 * Overview:        State B 
 ******************************************************************************/
void SM_STATE_TWO(void)
{
    ST7735_fillScreen(colWhite);
    ST7735_drawString(1, 1, "State Two", colCyan, 2);
    delay_ms(1000);
    
    SM_STATE = STATE_THREE;
}

/*******************************************************************************
 * Function:        void SM_STATE_THREE(void)
 *
 * PreCondition:    Table structure for states should have been initialized
 *                  as well as enum for each state
 *
 * Overview:        State C 
 ******************************************************************************/
void SM_STATE_THREE(void)
{
    ST7735_fillScreen(colWhite);
    ST7735_drawString(1, 1, "State Three", colDarkKhaki, 2);
    delay_ms(1000);
    
    SM_STATE = STATE_FOUR;
}


/*******************************************************************************
 * Function:        void SM_STATE_FOUR(void)
 *
 * PreCondition:    Table structure for states should have been initialized
 *                  as well as enum for each state
 *
 * Overview:        State D 
 ******************************************************************************/
void SM_STATE_FOUR(void)
{
    ST7735_fillScreen(colWhite);
    ST7735_drawString(1, 1, "State Four", colOrchid, 2);
    delay_ms(1000);
    
    SM_STATE = STATE_ONE; 
}


/*******************************************************************************
* Function Name: void initMain (void)
*
* Specification: initializes main
*
*******************************************************************************/
void initMain(void)
{  
    uc_init();                  // initialize microcontroller
    
    // unlock PPS
    systemReg_Unlock();
    CFGCONbits.IOLOCK = 0;

    RPA9Rbits.RPA9R = 0x0004;   // RA9->SDO2;
   
    // lock PPS
    CFGCONbits.IOLOCK = 1; 
    systemReg_Lock();
    
    TRISCbits.TRISC3 = 0;      // reset
    TRISCbits.TRISC4 = 0;      // chip select	
    TRISCbits.TRISC5 = 0;      // data or command 
    PORTCbits.RC3 = 0;
    PORTCbits.RC4 = 0;
    PORTCbits.RC5 = 0;
   
    PMCONbits.ON = 0;         // Turn of PMP as per errata
 
    SPI2_init();              // Initialize SPI2
}


/*******************************************************************************
* Function Name: void main (void)
*
* Specification: main function
*
*******************************************************************************/
void main(void) {
 
START:
    initMain();         // initializes main function
    ST7735_initR();     // initialize LCD
   
    while(1)
    {
       // Start the state machine
       RUN_STATEMACHINE();
    }
}

/*******************************************************************************
 * Function:        RUN_STATEMACHINE(void)
 *
 * PreCondition:    Table structure for states should have been initialized
 *                  as well as enum for each state
 *
 * Overview:        Allows state machine to run
 ******************************************************************************/
void RUN_STATEMACHINE (void)
{
    // Make Sure States is valid
    if (SM_STATE < NUM_STATES)
    {
        // Call function for state
        (*StateMachine[SM_STATE].func)();
    }
    else
    {
        // Code should never reach here
        while(1)
        {
            // Some exception handling;
            ST7735_fillScreen(colWhite);
            ST7735_drawString(1, 1, "Error", colOrchid, 2);
        }
    }
}






