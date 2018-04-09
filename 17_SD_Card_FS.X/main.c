/*
 * File: Main.c
 * Author: Armstrong Subero
 * Processor: PIC32MX270F256D w/Ext OSC @ 4MHz, PLL to 48 MHz, 3.3v
 * Program: 17_SD_Card_FS
 * Compiler: XC32 (v1.44, MPLAX X v4.00)
 * Program Version: 1.0
 *                             
 * Program Description: This Program Allows PIC32MX270F256D to use an SD card 
 *                      with a file system. This is dependent on the legacy PLIB 
 *                      libraries.
 * 
 * Hardware Description: An MH SD card breakout module is connected as follows:
 *                        GND  -> GND
 *                        3.3V -> 3.3v
 *                        CS   -> RC6 
 *                        MOSI -> RB2
 *                        SCK  -> RB14
 *                        MISO -> RB1
 *                        GND  -> GND
 * 
 * A Sparkfun SD/MMC breakout was also tested and was connected as follows:
*                     
*                    D2         --> NC
*                    D3(SS)     --> (pullup to VCC) RC6
*                    CMD(MOSI)  --> (pullup to VCC) RB2
*                    CD         --> NC
*                    CLK(SCK)   --> RB14
*                    VCC        --> 3.3V (Decoupled, cap, tantalum)(10uF)
*                    GND        --> GND  (Decoupled, cap, tantalum)
*                    D0(MISO)   --> (pullup to VCC)RB1
*                    D1         --> NC
*                    WP         --> NC
* 
 * Change History:
 *
 * Author             Rev     Date          Description
 * Armstrong Subero   1.0     09/04/2018    Initial Release.
 * 
 *                      
 * Created April 9th, 2018, 12:43 AM
 * 
 * 
 */

#define _SUPPRESS_PLIB_WARNING     //Remove warnings
#include <stdio.h>
#include <GenericTypeDefs.h>
#include "PIC32MX270_STD.h"
#include "Delay.h"
#include "plib.h"
#include "MDD_includes/FSIO.h"
#include "MDD_includes/FSIO.h"


/*******************************************************************************
* Function Name: void initMain (void)
*
* Specification: initializes main
*
*******************************************************************************/
void initMain(void){ 
    
    // unlock PPS
    systemReg_Unlock();
    CFGCONbits.IOLOCK = 0;
    
    RPB2Rbits.RPB2R = 0x0003;               //RB2->SDO1;
    SDI1Rbits.SDI1R = 0x0002;               //RB1->SDI1;
    
    // lock PPS
    CFGCONbits.IOLOCK = 1; 
    systemReg_Lock();
    
    ANSELA = 0; ANSELB = 0;                 // Disable analog inputs
    CM1CON = 0; CM2CON = 0; CM3CON = 0;     // Disable analog comparators
}

/*******************************************************************************
* Function Name: void main (void)
*
* Specification: Program entry point
*
*******************************************************************************/
void main(void) {
    // SD Card Variables
    char myData[15] = "ThisIsSomeText";
    int bytesWritten;
    char newFile[] = "MyTest.txt";

    FSFILE *fPointer, *pNewFile;
    SearchRec rec;
    UINT8 attributes = ATTR_MASK;
     
    initMain();    
   
    // Initialize the library
    while (!FSInit());
    
    //Open file
    pNewFile = FSfopen (newFile, "w");
    
    //Write data
    bytesWritten = FSfwrite ((void *) myData, sizeof(myData), 1, pNewFile);
    FSfclose (pNewFile);
    
    /*
     //Show current text files
     if (FindFirst("*.TXT", attributes, &rec) == 0) { // file found
        printf("%s\t%u KB\n\r", rec.filename, rec.filesize/1000);   
        delay_ms(3000);
        int x = 0;
        while (FindNext(&rec) == 0) { // more files found
            printf("%s\t%u KB\n\r", rec.filename, rec.filesize/1000);    
            delay_ms(3000);
        }
    }
    */
 }  


