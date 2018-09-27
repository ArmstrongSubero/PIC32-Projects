/*

By MD.
To compile successfully, must changed into large memory model (code/data)

Project > Build Options > Project > MPLab C30
Click the option box that says "General"
Click on "Memory Model"
On the right side select the memory models that you want. 
*/

#include "data_types.h"

#ifndef SAM_H
#define SAM_H

#define SAM_DEFAULT_PITCH 64
#define SAM_DEFAULT_SPEED 100
#define SAM_DEFAULT_MOUTH 128
#define SAM_DEFAULT_THROAT 128

void SetInput(char *_input);
void SetSpeed(unsigned char _speed);
void SetPitch(unsigned char _pitch);
void SetMouth(unsigned char _mouth);
void SetThroat(unsigned char _throat);
void EnableSingmode(_UINT32_ sing);

_INT16_ speakText(const char* str);
unsigned char SingString(unsigned char pitch, const char* str);
#endif
