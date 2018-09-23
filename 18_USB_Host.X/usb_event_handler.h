

#include "PIC32MX270_USB.h"
#include "usb.h"
volatile BOOL deviceAttached;  // bool to check if device is attached
BOOL USB_ApplicationEventHandler( BYTE address, USB_EVENT event, void *data, DWORD size );