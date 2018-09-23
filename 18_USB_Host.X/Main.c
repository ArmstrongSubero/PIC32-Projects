 /*
 * File: Main.c
 * Author: Armstrong Subero
 * Processor: PIC32MX270F256D w/Ext OSC @ 4MHz, PLL to 48 MHz, 3.3v
 * Program: 18_USB_Host
 * Compiler: XC32 (v1.44, MPLAX X v5.05)
 * Program Version: 1.0
 *                             
 * Program Description: This Program Allows PIC32MX270F256D to use the USB OTG
 *                      module in USB host mode to read a USB drive. The program
 *                      was tested with various Drives from size 2 GB to 32 GB
 *                      from different manufacturers. 
 * 
 *                      NOTE: This file is dependent on the legacy PLIB 
 *                      libraries.  
 * 
 * Hardware Description: A USB Flash Drive is connected to the microcontroller
 *                       as follows:
 *                       
 *                       VBUS -> Vcc (5v)
 *                    VUSB3V3 -> 3.3v                    
 *                         D+ -> D+
 *                         D- -> D-
 *                     VBUSON -> 3.3v    
 *                      USBID -> GND   
 * 
 * Change History:
 *
 * Author             Rev     Date          Description
 * Armstrong Subero   1.0     23/09/2018    Initial Release.
 *                      
 * Created September 23st, 2018, 01:26 PM
 */

////////////////////////////////////////////////////////////////////////////////
// Includes and Defines
////////////////////////////////////////////////////////////////////////////////
#include "usb.h"
#include "usb_host_msd.h"
#include "usb_host_msd_scsi.h"
#include "FSIO.h"
#include "PIC32MX270_USB.h"
#include "usb_event_handler.h"

FSFILE *myFile;                // FSFILE pointer for file we are working with 

int main(void)
{ 
    // Enable the cache for the best performance
    CheKseg0CacheOn();
    
    // Enable interrupts
    INTEnableSystemMultiVectoredInt();
    
    // Initially the device is not attached
    deviceAttached = FALSE;

    //Initialize the stack
    USBInitialize(0);

    while(1)
    {
        //USB stack process function
        USBTasks();

        //if flash drive is plugged in
        if(USBHostMSDSCSIMediaDetect())
        {
            // device is now attached
            deviceAttached = TRUE;   
    
            // after device is attached try to initialize the file system
            if(FSInit())
            {
                // Opening a file in mode "w" will create the file if it doesn't
                // exist.  If the file does exist it will delete the old file
                // and create a new one.
                myFile = FSfopen("text.txt","w");
                
                // Write some data to the new file.
                FSfwrite("Some Text",1,11,myFile);
                
                // Make sure to close the file so that the data is written
                FSfclose(myFile);
                PORTBbits.RB0 = 0;

                // Just sit here until the device is removed.
                while(deviceAttached == TRUE)
                {
                    USBTasks();
                }
            }
        }
    }
    return 0;
}


