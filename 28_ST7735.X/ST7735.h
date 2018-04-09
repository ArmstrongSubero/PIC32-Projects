/*
 * File:   ST7735.h
 * Author: Armstrong Subero
 * Processor: PIC32MX270F256D @ 48MHz, 3.3v
 * Program: Header file for MX270F256D delay routines
 * Compiler: XC32 (v1.44, MPLAX X v4.00)
 * Program Version 1.1
 * Program Description: This header file contains function prototypes to use
 *                      ST7735 module
 * 
 * Change History:
 *
 * Author             Rev     Date          Description
 * Armstrong Subero   1.0     09/04/2015    Initial Release.
 * 
 * Updated on April 9th, 2018, 5:22 PM
 */

#define swap(a, b) { int t = a; a = b; b = t; }

#define SCREEN_WIDTH 128
#define SCREEN_HEIGHT 160

#define ST7735_NOP 0x0
#define ST7735_SWRESET 0x01
#define ST7735_RDDID 0x04
#define ST7735_RDDST 0x09

#define ST7735_SLPIN  0x10
#define ST7735_SLPOUT  0x11
#define ST7735_PTLON  0x12
#define ST7735_NORON  0x13

#define ST7735_INVOFF 0x20
#define ST7735_INVON 0x21
#define ST7735_DISPOFF 0x28
#define ST7735_DISPON 0x29
#define ST7735_CASET 0x2A
#define ST7735_RASET 0x2B
#define ST7735_RAMWR 0x2C
#define ST7735_RAMRD 0x2E

#define ST7735_COLMOD 0x3A
#define ST7735_MADCTL 0x36


#define ST7735_FRMCTR1 0xB1
#define ST7735_FRMCTR2 0xB2
#define ST7735_FRMCTR3 0xB3
#define ST7735_INVCTR 0xB4
#define ST7735_DISSET5 0xB6

#define ST7735_PWCTR1 0xC0
#define ST7735_PWCTR2 0xC1
#define ST7735_PWCTR3 0xC2
#define ST7735_PWCTR4 0xC3
#define ST7735_PWCTR5 0xC4
#define ST7735_VMCTR1 0xC5

#define ST7735_RDID1 0xDA
#define ST7735_RDID2 0xDB
#define ST7735_RDID3 0xDC
#define ST7735_RDID4 0xDD

#define ST7735_PWCTR6 0xFC

#define ST7735_GMCTRP1 0xE0
#define ST7735_GMCTRN1 0xE1

// macro to convert to RGB888 (24-bit value) to RGB565(12-bit, 4096 color) used by Nokia 3510i LCD
#define RGB565(r,g,b) ((((r>>3)<<11) | ((g>>2)<<5) | (b>>3))) 

#define colAliceBlue RGB565(240,248,255)
#define colAntiqueWhite RGB565(250,235,215)
#define colAqua RGB565( 0,255,255)
#define colAquamarine RGB565(127,255,212)
#define colAzure RGB565(240,255,255)
#define colBeige RGB565(245,245,220)
#define colBisque RGB565(255,228,196)
#define colBlack RGB565( 0, 0, 0)
#define colBlanchedAlmond RGB565(255,255,205)
#define colBlue RGB565( 0, 0,255)
#define colBlueViolet RGB565(138, 43,226)
#define colBrown RGB565(165, 42, 42)
#define colBurlywood RGB565(222,184,135)
#define colCadetBlue RGB565( 95,158,160)
#define colChartreuse RGB565(127,255, 0)
#define colChocolate RGB565(210,105, 30)
#define colCoral RGB565(255,127, 80)
#define colCornflowerBlue RGB565(100,149,237)
#define colCornsilk RGB565(255,248,220)
#define colCrimson RGB565(220, 20, 60)
#define colCyan RGB565( 0,255,255)
#define colDarkBlue RGB565( 0, 0,139)
#define colDarkCyan RGB565( 0,139,139)
#define colDarkGoldenRod RGB565(184,134, 11)
#define colDarkGray RGB565(169,169,169)
#define colDarkGreen RGB565( 0,100, 0)
#define colDarkKhaki RGB565(189,183,107)
#define colDarkMagenta RGB565(139, 0,139)
#define colDarkOliveGreen RGB565( 85,107, 47)
#define colDarkOrange RGB565(255,140, 0)
#define colDarkOrchid RGB565(153, 50,204)
#define colDarkRed RGB565(139, 0, 0)
#define colDarkSalmon RGB565(233,150,122)
#define colDarkSeaGreen RGB565(143,188,143)
#define colDarkSlateBlue RGB565( 72, 61,139)
#define colDarkSlateGray RGB565( 47, 79, 79)
#define colDarkTurquoise RGB565( 0,206,209)
#define colDarkViolet RGB565(148, 0,211)
#define colDeepPink RGB565(255, 20,147)
#define colDeepSkyBlue RGB565( 0,191,255)
#define colDimGray RGB565(105,105,105)
#define colDodgerBlue RGB565( 30,144,255)
#define colFireBrick RGB565(178, 34, 34)
#define colFloralWhite RGB565(255,250,240)
#define colForestGreen RGB565( 34,139, 34)
#define colFuchsia RGB565(255, 0,255)
#define colGainsboro RGB565(220,220,220)
#define colGhostWhite RGB565(248,248,255)
#define colGold RGB565(255,215, 0)
#define colGoldenRod RGB565(218,165, 32)
#define colGray RGB565(127,127,127)
#define colGreen RGB565( 0,128, 0)
#define colGreenYellow RGB565(173,255, 47)
#define colHoneyDew RGB565(240,255,240)
#define colHotPink RGB565(255,105,180)
#define colIndianRed RGB565(205, 92, 92)
#define colIndigo RGB565( 75, 0,130)
#define colIvory RGB565(255,255,240)
#define colKhaki RGB565(240,230,140)
#define colLavender RGB565(230,230,250)
#define colLavenderBlush RGB565(255,240,245)
#define colLawngreen RGB565(124,252, 0)
#define colLemonChiffon RGB565(255,250,205)
#define colLightBlue RGB565(173,216,230)
#define colLightCoral RGB565(240,128,128)
#define colLightCyan RGB565(224,255,255)
#define colLightGoldenRodYellow RGB565(250,250,210)
#define colLightGreen RGB565(144,238,144)
#define colLightGrey RGB565(211,211,211)
#define colLightPink RGB565(255,182,193)
#define colLightSalmon RGB565(255,160,122)
#define colLightSeaGreen RGB565( 32,178,170)
#define colLightSkyBlue RGB565(135,206,250)
#define colLightSlateGray RGB565(119,136,153)
#define colLightSteelBlue RGB565(176,196,222)
#define colLightYellow RGB565(255,255,224)
#define colLime RGB565( 0,255, 0)
#define colLimeGreen RGB565( 50,205, 50)
#define colLinen RGB565(250,240,230)
#define colMagenta RGB565(255, 0,255)
#define colMaroon RGB565(128, 0, 0)
#define colMediumAquamarine RGB565(102,205,170)
#define colMediumBlue RGB565( 0, 0,205)
#define colMediumOrchid RGB565(186, 85,211)
#define colMediumPurple RGB565(147,112,219)
#define colMediumSeaGreen RGB565( 60,179,113)
#define colMediumSlateBlue RGB565(123,104,238)
#define colMediumSpringGreen RGB565( 0,250,154)
#define colMediumTurquoise RGB565( 72,209,204)
#define colMediumVioletRed RGB565(199, 21,133)
#define colMidnightBlue RGB565( 25, 25,112)
#define colMintCream RGB565(245,255,250)
#define colMistyRose RGB565(255,228,225)
#define colMoccasin RGB565(255,228,181)
#define colNavajoWhite RGB565(255,222,173)
#define colNavy RGB565( 0, 0,128)
#define colNavyblue RGB565(159,175,223)
#define colOldLace RGB565(253,245,230)
#define colOlive RGB565(128,128, 0)
#define colOliveDrab RGB565(107,142, 35)
#define colOrange RGB565(255,165, 0)
#define colOrangeRed RGB565(255, 69, 0)
#define colOrchid RGB565(218,112,214)
#define colPaleGoldenRod RGB565(238,232,170)
#define colPaleGreen RGB565(152,251,152)
#define colPaleTurquoise RGB565(175,238,238)
#define colPaleVioletRed RGB565(219,112,147)
#define colPapayaWhip RGB565(255,239,213)
#define colPeachPuff RGB565(255,218,185)
#define colPeru RGB565(205,133, 63)
#define colPink RGB565(255,192,203)
#define colPlum RGB565(221,160,221)
#define colPowderBlue RGB565(176,224,230)
#define colPurple RGB565(128, 0,128)
#define colRed RGB565(255, 0, 0)
#define colRosyBrown RGB565(188,143,143)
#define colRoyalBlue RGB565( 65,105,225)
#define colSaddleBrown RGB565(139, 69, 19)
#define colSalmon RGB565(250,128,114)
#define colSandyBrown RGB565(244,164, 96)
#define colSeaGreen RGB565( 46,139, 87)
#define colSeaShell RGB565(255,245,238)
#define colSienna RGB565(160, 82, 45)
#define colSilver RGB565(192,192,192)
#define colSkyBlue RGB565(135,206,235)
#define colSlateBlue RGB565(106, 90,205)
#define colSlateGray RGB565(112,128,144)
#define colSnow RGB565(255,250,250)
#define colSpringGreen RGB565( 0,255,127)
#define colSteelBlue RGB565( 70,130,180)
#define colTan RGB565(210,180,140)
#define colTeal RGB565( 0,128,128)
#define colThistle RGB565(216,191,216)
#define colTomato RGB565(255, 99, 71)
#define colTurquoise RGB565( 64,224,208)
#define colViolet RGB565(238,130,238)
#define colWheat RGB565(245,222,179)
#define colWhite RGB565(255,255,255)
#define colWhiteSmoke RGB565(245,245,245)
#define colYellow RGB565(255,255, 0)
#define colYellowGreen RGB565(139,205, 50)
// background
#define BCKGRDCOL RGB565(138,235,244)
// bird
#define BIRDCOL RGB565(255,254,174)
// pipe
#define PIPECOL  RGB565(99,255,78)
// pipe highlight
#define PIPEHIGHCOL  RGB565(250,255,250)
// pipe seam
#define PIPESEAMCOL  RGB565(0,0,0)
// floor
#define FLOORCOL RGB565(246,240,163)
// grass (col2 is the stripe color)
#define GRASSCOL  RGB565(141,225,87)
#define GRASSCOL2 RGB565(156,239,88)

// bird sprite
// bird sprite colors (Cx name for values to keep the array readable)
#define C0 BCKGRDCOL
#define C1 RGB565(195,165,75)
#define C2 BIRDCOL
#define C3 colWhite
#define C4 colRed
#define C5 RGB565(251,216,114)

static unsigned int birdcol[] =
{ C0, C0, C1, C1, C1, C1, C1, C0,
  C0, C1, C2, C2, C2, C1, C3, C1,
  C0, C2, C2, C2, C2, C1, C3, C1,
  C1, C1, C1, C2, C2, C3, C1, C1,
  C1, C2, C2, C2, C2, C2, C4, C4,
  C1, C2, C2, C2, C1, C5, C4, C0,
  C0, C1, C2, C1, C5, C5, C5, C0,
  C0, C0, C1, C5, C5, C5, C0, C0};

void setAddrWindow(unsigned char x0, unsigned char y0, unsigned char x1, unsigned char y1);
void ST7735_pushColor(unsigned int color); // for what?
void ST7735_drawPixel(unsigned char x, unsigned char y, unsigned int color);
void ST7735_fillScreen(unsigned int color);
void ST7735_initR(void); // initialize a ST7735 chip
void ST7735_drawString(unsigned char x, unsigned char y, char *c, unsigned int color, unsigned char size);
void ST7735_drawChar(unsigned char x, unsigned char y, char c, unsigned int color, unsigned char size);
void ST7735_fillCircle(unsigned char x0, unsigned char y0, unsigned char r, unsigned int color);
void ST7735_drawCircle(unsigned char x0, unsigned char y0, unsigned char r, unsigned int color);
void ST7735_setRotation(unsigned char m);
void ST7735_drawRect(unsigned char x, unsigned char y, unsigned char w, unsigned char h, unsigned int color);
void ST7735_fillRect(unsigned char x, unsigned char y, unsigned char w, unsigned char h, unsigned int color);
void ST7735_drawVerticalLine(unsigned char x, unsigned char y, unsigned char length, unsigned int color);
void ST7735_drawHorizontalLine(unsigned char x, unsigned char y, unsigned char length, unsigned int color);
void ST7735_drawFastLine(unsigned char x, unsigned char y, unsigned char length, unsigned int color, unsigned char rotflag);
void ST7735_drawLine(int x0, int y0, int x1, int y1, unsigned int color);
void ST7735_writeInteger(int x, int y, int v, unsigned int colour, int size);
void ST7735_test();
void loadBitmap(char* filename, int width, int height);
unsigned char ST7735_getRotation();


char madctl;


static const char Alpha1[] = {
                  0x00,0x00,0x00,0x00,0x00,  // 20 space
                  0x00,0x00,0x5f,0x00,0x00,  // 21 !
                  0x00,0x07,0x00,0x07,0x00,  // 22 "
                  0x14,0x7f,0x14,0x7f,0x14,  // 23 #
                  0x24,0x2a,0x7f,0x2a,0x12,  // 24 $
                  0x23,0x13,0x08,0x64,0x62,  // 25 %
                  0x36,0x49,0x55,0x22,0x50,  // 26 &
                  0x00,0x05,0x03,0x00,0x00,  // 27 '
                  0x00,0x1c,0x22,0x41,0x00,  // 28 (
                  0x00,0x41,0x22,0x1c,0x00,  // 29 )
                  0x14,0x08,0x3e,0x08,0x14,  // 2a *
                  0x08,0x08,0x3e,0x08,0x08,  // 2b +
                  0x00,0x50,0x30,0x00,0x00,  // 2c ,
                  0x08,0x08,0x08,0x08,0x08,  // 2d -
                  0x00,0x60,0x60,0x00,0x00,  // 2e .
                  0x20,0x10,0x08,0x04,0x02,  // 2f /
                  0x3e,0x51,0x49,0x45,0x3e,  // 30 0
                  0x00,0x42,0x7f,0x40,0x00,  // 31 1
                  0x42,0x61,0x51,0x49,0x46,  // 32 2
                  0x21,0x41,0x45,0x4b,0x31,  // 33 3
                  0x18,0x14,0x12,0x7f,0x10,  // 34 4
                  0x27,0x45,0x45,0x45,0x39,  // 35 5
                  0x3c,0x4a,0x49,0x49,0x30,  // 36 6
                  0x01,0x71,0x09,0x05,0x03,  // 37 7
                  0x36,0x49,0x49,0x49,0x36,  // 38 8
                  0x06,0x49,0x49,0x29,0x1e,  // 39 9
                  0x00,0x36,0x36,0x00,0x00,  // 3a :
                  0x00,0x56,0x36,0x00,0x00,  // 3b ;
                  0x08,0x14,0x22,0x41,0x00,  // 3c <
                  0x14,0x14,0x14,0x14,0x14,  // 3d =
                  0x00,0x41,0x22,0x14,0x08,  // 3e >
                  0x02,0x01,0x51,0x09,0x06,  // 3f ?
                  0x32,0x49,0x79,0x41,0x3e,  // 40 @
                  0x7e,0x11,0x11,0x11,0x7e,  // 41 A
                  0x7f,0x49,0x49,0x49,0x36,  // 42 B
                  0x3e,0x41,0x41,0x41,0x22,  // 43 C
                  0x7f,0x41,0x41,0x22,0x1c,  // 44 D
                  0x7f,0x49,0x49,0x49,0x41,  // 45 E
                  0x7f,0x09,0x09,0x09,0x01,  // 46 F
                  0x3e,0x41,0x49,0x49,0x7a,  // 47 G
                  0x7f,0x08,0x08,0x08,0x7f,  // 48 H
                  0x00,0x41,0x7f,0x41,0x00,  // 49 I
                  0x20,0x40,0x41,0x3f,0x01,  // 4a J
                  0x7f,0x08,0x14,0x22,0x41,  // 4b K
                  0x7f,0x40,0x40,0x40,0x40,  // 4c L
                  0x7f,0x02,0x0c,0x02,0x7f,  // 4d M
                  0x7f,0x04,0x08,0x10,0x7f,  // 4e N
                  0x3e,0x41,0x41,0x41,0x3e,  // 4f O
                  0x7f,0x09,0x09,0x09,0x06,  // 50 P
                  0x3e,0x41,0x51,0x21,0x5e}; // 51 Q

static const char Alpha2[] = {
                  0x7f,0x09,0x19,0x29,0x46,
                  0x46,0x49,0x49,0x49,0x31,  // 53 S
                  0x01,0x01,0x7f,0x01,0x01,  // 54 T
                  0x3f,0x40,0x40,0x40,0x3f,  // 55 U
                  0x1f,0x20,0x40,0x20,0x1f,  // 56 V
                  0x3f,0x40,0x38,0x40,0x3f,  // 57 W
                  0x63,0x14,0x08,0x14,0x63,  // 58 X
                  0x07,0x08,0x70,0x08,0x07,  // 59 Y
                  0x61,0x51,0x49,0x45,0x43,  // 5a Z
                  0x00,0x7f,0x41,0x41,0x00,  // 5b [
                  0x02,0x04,0x08,0x10,0x20,  // 5c 55
                  0x00,0x41,0x41,0x7f,0x00,  // 5d ]
                  0x04,0x02,0x01,0x02,0x04,  // 5e ^
                  0x40,0x40,0x40,0x40,0x40,  // 5f _
                  0x00,0x01,0x02,0x04,0x00,  // 60 `
                  0x20,0x54,0x54,0x54,0x78,  // 61 a
                  0x7f,0x48,0x44,0x44,0x38,  // 62 b
                  0x38,0x44,0x44,0x44,0x20,  // 63 c
                  0x38,0x44,0x44,0x48,0x7f,  // 64 d
                  0x38,0x54,0x54,0x54,0x18,  // 65 e
                  0x08,0x7e,0x09,0x01,0x02,  // 66 f
                  0x0c,0x52,0x52,0x52,0x3e,  // 67 g
                  0x7f,0x08,0x04,0x04,0x78,  // 68 h
                  0x00,0x44,0x7d,0x40,0x00,  // 69 i
                  0x20,0x40,0x44,0x3d,0x00,  // 6a j
                  0x7f,0x10,0x28,0x44,0x00,  // 6b k
                  0x00,0x41,0x7f,0x40,0x00,  // 6c l
                  0x7c,0x04,0x18,0x04,0x78,  // 6d m
                  0x7c,0x08,0x04,0x04,0x78,  // 6e n
                  0x38,0x44,0x44,0x44,0x38,  // 6f o
                  0x7c,0x14,0x14,0x14,0x08,  // 70 p
                  0x08,0x14,0x14,0x18,0x7c,  // 71 q
                  0x7c,0x08,0x04,0x04,0x08,  // 72 r
                  0x48,0x54,0x54,0x54,0x20,  // 73 s
                  0x04,0x3f,0x44,0x40,0x20,  // 74 t
                  0x3c,0x40,0x40,0x20,0x7c,  // 75 u
                  0x1c,0x20,0x40,0x20,0x1c,  // 76 v
                  0x3c,0x40,0x30,0x40,0x3c,  // 77 w
                  0x44,0x28,0x10,0x28,0x44,  // 78 x
                  0x0c,0x50,0x50,0x50,0x3c,  // 79 y
                  0x44,0x64,0x54,0x4c,0x44,  // 7a z
                  0x00,0x08,0x36,0x41,0x00,  // 7b {
                  0x00,0x00,0x7f,0x00,0x00,  // 7c |
                  0x00,0x41,0x36,0x08,0x00,  // 7d }
                  0x10,0x08,0x08,0x10,0x08,  // 7e ~
                  0x78,0x46,0x41,0x46,0x78}; // 7f &brvbar;


//Define pins
#define LCD_RESET 	LATCbits.LATC3   // reset
#define LCD_CS 		LATCbits.LATC4	 // chip select	
#define LCD_RS 		LATCbits.LATC5	 // data or command


#define drawPixel(a, b, c) setAddrWindow(a, b, a, b); ST7735_pushColor(c)
