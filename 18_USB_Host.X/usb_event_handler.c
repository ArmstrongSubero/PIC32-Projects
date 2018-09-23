
#include "usb_event_handler.h"


/****************************************************************************
  Function:
    BOOL USB_ApplicationEventHandler( BYTE address, USB_EVENT event,
                void *data, DWORD size )

  Summary:
    This is the application event handler.  It is called when the stack has
    an event that needs to be handled by the application layer rather than
    by the client driver.

  Description:
    This is the application event handler.  It is called when the stack has
    an event that needs to be handled by the application layer rather than
    by the client driver.  If the application is able to handle the event, it
    returns TRUE.  Otherwise, it returns FALSE.

  Precondition:
    None

  Parameters:
    BYTE address    - Address of device where event occurred
    USB_EVENT event - Identifies the event that occured
    void *data      - Pointer to event-specific data
    DWORD size      - Size of the event-specific data

  Return Values:
    TRUE    - The event was handled
    FALSE   - The event was not handled

  Remarks:
    The application may also implement an event handling routine if it
    requires knowledge of events.  To do so, it must implement a routine that
    matches this function signature and define the USB_HOST_APP_EVENT_HANDLER
    macro as the name of that function.
  ***************************************************************************/

BOOL USB_ApplicationEventHandler( BYTE address, USB_EVENT event, void *data, DWORD size )
{
    switch( event )
    {
        case EVENT_VBUS_REQUEST_POWER:
            // The data pointer points to a byte that represents the amount of power
            // requested in mA, divided by two.  If the device wants too much power,
            // we reject it.
            // Error handler message
            return TRUE;

        case EVENT_VBUS_RELEASE_POWER:
            // Turn off Vbus power.
            //This means that the device was removed
            deviceAttached = FALSE;
            return TRUE;
            break;

        case EVENT_HUB_ATTACH:
            // Error handler message
            return TRUE;
            break;

        case EVENT_UNSUPPORTED_DEVICE:
            // Error Handler Message
            return TRUE;
            break;

        case EVENT_CANNOT_ENUMERATE:
            // Error Handler Message 
            return TRUE;
            break;

        case EVENT_CLIENT_INIT_ERROR:
            // Error Handler Message
            return TRUE;
            break;

        case EVENT_OUT_OF_MEMORY:
            // Error Handler Message
            return TRUE;
            break;

        case EVENT_UNSPECIFIED_ERROR:   // This should never be generated.
            // Error handler Message
            return TRUE;
            break;

        default:
            break;
    }

    return FALSE;
}
