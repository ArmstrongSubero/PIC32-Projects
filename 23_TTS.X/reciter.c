#include <stdio.h>
#include <string.h>
#include "reciter.h"
#include "ReciterTabs.h"
#include "uart1.h"

unsigned char A0, X0, Y0;

// secure copy of input string
// initially contains text but will later be converted to Phonemes
unsigned char strInputCopy[256];   

void Code37055(unsigned char mem59)
{
	X0 = mem59;
	X0--;
	A0 = strInputCopy[X0];
	Y0 = A0;
	A0 = tab36376[Y0];
	return;
}

void Code37066(unsigned char mem58)
{
	X0 = mem58;
	X0++;
	A0 = strInputCopy[X0];
	Y0 = A0;
	A0 = tab36376[Y0];
}

unsigned char GetRuleByte(unsigned char mem62, unsigned char mem63, unsigned char Y0)
{
	_UINT32_ address = ((_UINT32_)mem62+((_UINT32_)mem63<<8));
	address -= 32000;
	return rules[address+Y0];
}


_INT32_ TextToPhonemes(char *input)
{
	unsigned char mem56;      //output position for phonemes
	unsigned char mem57;
	unsigned char mem58;
	unsigned char mem59;
	unsigned char mem60;
	unsigned char mem61;
	unsigned char mem62;
	unsigned char mem63;
	unsigned char mem64;	 // position of '=' or current character
	unsigned char mem65;     // position of ')'
	unsigned char mem66;     // position of '('
	unsigned char mem36653;
	// unsigned char i;

	strInputCopy[0] = 32;

	// secure copy of input
	// because input will be overwritten by phonemes
	// MD: we should not copy all 255 characters because the original string may be shorter
	// should just stop at the end of string marker.
	// However fixing it is not easy because other parts of the code will still process 255 characters.
	// We fix it at caller side by filling initial buffer with space (32)
	X0 = 1;
	Y0 = 0;
	do
	{
		//pos36499:
		A0 = input[Y0] & 127;
		if ( A0 >= 112) A0 = A0 & 95;
		else if ( A0 >= 96) A0 = A0 & 79;

		strInputCopy[X0] = A0;

		X0++;
		Y0++;
	} while (Y0 != 255);

	X0 = 255;
	A0 = 27;
	strInputCopy[X0] = 27;
	mem61 = 255;


pos36550:
	A0 = 255;
	mem56 = 255;


pos36554:
	while(1)
	{
		mem61++;
		X0 = mem61;
		A0 = strInputCopy[X0];
		mem64 = A0;
		if (A0 == 27)    // '['
		{
			mem56++;
			X0 = mem56;
			A0 = 155;
			input[X0] = 155;

			return 1;
		}

		if (A0 != 46) break;   // '.'
		X0++;
		Y0 = strInputCopy[X0];
		A0 = tab36376[Y0] & 1;
		if(A0 != 0) break;
		mem56++;
		X0 = mem56;
		A0 = 46;
		input[X0] = 46;
	}


	//pos36607:
	A0 = mem64;
	Y0 = A0;
	A0 = tab36376[A0];
	mem57 = A0;
	if((A0&2) != 0)
	{
		mem62 = 165;
		mem63 = 146;
		goto pos36700;
	}

	//pos36630:
	A0 = mem57;
	if(A0 != 0) goto pos36677;
	A0 = 32;
	strInputCopy[X0] = 32;
	mem56++;
	X0 = mem56;
	if (X0 > 120) goto pos36654;
	input[X0] = A0;
	goto pos36554;

	// -----

	//36653 is unknown. Contains position

pos36654:
	input[X0] = 155;
	A0 = mem61;
	mem36653 = A0;

	return 1;

	mem61 = mem36653;
	goto pos36550;

pos36677:
	A0 = mem57 & 128;
	if(A0 == 0)
	{
		//36683: BRK
		return 0;
	}

	// go to the right rule for this character.
	X0 = mem64 - 65;
	mem62 = tab37489[X0];
	mem63 = tab37515[X0];

	// -------------------------------------
	// go to next rule
	// -------------------------------------

pos36700:

	// find next rule
	Y0 = 0;
	do
	{
		mem62 += 1;
		mem63 += (mem62 == 0)?1:0;
		A0 = GetRuleByte(mem62, mem63, Y0);
	} while ((A0 & 128) == 0);
	Y0++;

	//pos36720:
	// find '('
	while(1)
	{
		A0 = GetRuleByte(mem62, mem63, Y0);
		if (A0 == 40) break;      //'('
		Y0++;
	}
	mem66 = Y0;

	//pos36732:
	// find ')'
	do
	{
		Y0++;
		A0 = GetRuleByte(mem62, mem63, Y0);
	} while(A0 != 41);
	mem65 = Y0;

	//pos36741:
	// find '='
	do
	{
		Y0++;
		A0 = GetRuleByte(mem62, mem63, Y0);
		A0 = A0 & 127;

	} while (A0 != 61);   // '='
	mem64 = Y0;

	X0 = mem61;
	mem60 = X0;

	Y0 = mem66;
	Y0++;
	//pos36759:
	while(1)
	{
		mem57 = strInputCopy[X0];
		A0 = GetRuleByte(mem62, mem63, Y0);
		if (A0 != mem57) goto pos36700;
		Y0++;
		if(Y0 == mem65) break;
		X0++;
		mem60 = X0;
	}


	//pos36787:
	A0 = mem61;
	mem59 = mem61;

pos36791:
	while(1)
	{
		mem66--;
		Y0 = mem66;
		A0 = GetRuleByte(mem62, mem63, Y0);
		mem57 = A0;
		//36800: BPL 36805
		if ((A0 & 128) != 0) goto pos37180;
		X0 = A0 & 127;
		A0 = tab36376[X0] & 128;
		if (A0 == 0) break;
		X0 = mem59-1;
		A0 = strInputCopy[X0];
		if (A0 != mem57) goto pos36700;
		mem59 = X0;
	}


	//pos36833:
	A0 = mem57;
	if (A0 == 32) goto pos36895;     // ' '
	if (A0 == 35) goto pos36910;     // '#'
	if (A0 == 46) goto pos36920;
	if (A0 == 38) goto pos36935;
	if (A0 == 64) goto pos36967;
	if (A0 == 94) goto pos37004;
	if (A0 == 43) goto pos37019;
	if (A0 == 58) goto pos37040;
	//	Code42041();    //Error
	//36894: BRK
	return 0;

	// --------------

pos36895:
	Code37055(mem59);
	A0 = A0 & 128;
	if(A0 != 0) goto pos36700;
pos36905:
	mem59 = X0;
	goto pos36791;

	// --------------

pos36910:
	Code37055(mem59);
	A0 = A0 & 64;
	if(A0 != 0) goto pos36905;
	goto pos36700;

	// --------------


pos36920:
	Code37055(mem59);
	A0 = A0 & 8;
	if(A0 == 0) goto pos36700;
pos36930:
	mem59 = X0;
	goto pos36791;

	// --------------

pos36935:
	Code37055(mem59);
	A0 = A0 & 16;
	if(A0 != 0) goto pos36930;
	A0 = strInputCopy[X0];
	if (A0 != 72) goto pos36700;
	X0--;
	A0 = strInputCopy[X0];
	if ((A0 == 67) || (A0 == 83)) goto pos36930;
	goto pos36700;

	// --------------

pos36967:
	Code37055(mem59);
	A0 = A0 & 4;
	if(A0 != 0) goto pos36930;
	A0 = strInputCopy[X0];
	if (A0 != 72) goto pos36700;
	if ((A0 != 84) && (A0 != 67) && (A0 != 83)) goto pos36700;
	mem59 = X0;
	goto pos36791;

	// --------------


pos37004:
	Code37055(mem59);
	A0 = A0 & 32;
	if(A0 == 0) goto pos36700;
pos37014:
	mem59 = X0;
	goto pos36791;

	// --------------

pos37019:
	X0 = mem59;
	X0--;
	A0 = strInputCopy[X0];
	if ((A0 == 69) || (A0 == 73) || (A0 == 89)) goto pos37014; //'E' 'I' 'Y0'
	goto pos36700;

	// --------------

pos37040:
	Code37055(mem59);
	A0 = A0 & 32;
	if(A0 == 0) goto pos36791;
	mem59 = X0;
	goto pos37040;

	//---------------------------------------


pos37077:
	X0 = mem58+1;
	A0 = strInputCopy[X0];
	if (A0 != 69) goto pos37157;   // 'E'
	X0++;
	Y0 = strInputCopy[X0];
	X0--;
	A0 = tab36376[Y0] & 128;
	if(A0 == 0) goto pos37108;
	X0++;
	A0 = strInputCopy[X0];
	if (A0 != 82) goto pos37113;     // 'R'
pos37108:
	mem58 = X0;
	goto pos37184;
pos37113:
	if ((A0 == 83) || (A0 == 68)) goto pos37108;  // 'S' 'D'
	if (A0 != 76) goto pos37135; // 'L'
	X0++;
	A0 = strInputCopy[X0];
	if (A0 != 89) goto pos36700;
	goto pos37108;

pos37135:
	if (A0 != 70) goto pos36700;
	X0++;
	A0 = strInputCopy[X0];
	if (A0 != 85) goto pos36700;
	X0++;
	A0 = strInputCopy[X0];
	if (A0 == 76) goto pos37108;
	goto pos36700;

pos37157:
	if (A0 != 73) goto pos36700;
	X0++;
	A0 = strInputCopy[X0];
	if (A0 != 78) goto pos36700;
	X0++;
	A0 = strInputCopy[X0];
	if (A0 == 71) goto pos37108;
	//pos37177:
	goto pos36700;

	// -----------------------------------------

pos37180:
	A0 = mem60;
	mem58 = A0;

pos37184:
	Y0 = mem65 + 1;

	//37187: CPY 64
	//	if(? != 0) goto pos37194;
	if(Y0 == mem64) goto pos37455;
	mem65 = Y0;
	//37196: LDA (62),Y0
	A0 = GetRuleByte(mem62, mem63, Y0);
	mem57 = A0;
	X0 = A0;
	A0 = tab36376[X0] & 128;
	if(A0 == 0) goto pos37226;
	X0 = mem58+1;
	A0 = strInputCopy[X0];
	if (A0 != mem57) goto pos36700;
	mem58 = X0;
	goto pos37184;
pos37226:
	A0 = mem57;
	if (A0 == 32) goto pos37295;   // ' '
	if (A0 == 35) goto pos37310;   // '#'
	if (A0 == 46) goto pos37320;   // '.'
	if (A0 == 38) goto pos37335;   // '&'
	if (A0 == 64) goto pos37367;   // ''
	if (A0 == 94) goto pos37404;   // ''
	if (A0 == 43) goto pos37419;   // '+'
	if (A0 == 58) goto pos37440;   // ':'
	if (A0 == 37) goto pos37077;   // '%'
	//pos37291:
	//	Code42041(); //Error
	//37294: BRK
	return 0;

	// --------------
pos37295:
	Code37066(mem58);
	A0 = A0 & 128;
	if(A0 != 0) goto pos36700;
pos37305:
	mem58 = X0;
	goto pos37184;

	// --------------

pos37310:
	Code37066(mem58);
	A0 = A0 & 64;
	if(A0 != 0) goto pos37305;
	goto pos36700;

	// --------------


pos37320:
	Code37066(mem58);
	A0 = A0 & 8;
	if(A0 == 0) goto pos36700;

pos37330:
	mem58 = X0;
	goto pos37184;

	// --------------

pos37335:
	Code37066(mem58);
	A0 = A0 & 16;
	if(A0 != 0) goto pos37330;
	A0 = strInputCopy[X0];
	if (A0 != 72) goto pos36700;
	X0++;
	A0 = strInputCopy[X0];
	if ((A0 == 67) || (A0 == 83)) goto pos37330;
	goto pos36700;

	// --------------


pos37367:
	Code37066(mem58);
	A0 = A0 & 4;
	if(A0 != 0) goto pos37330;
	A0 = strInputCopy[X0];
	if (A0 != 72) goto pos36700;
	if ((A0 != 84) && (A0 != 67) && (A0 != 83)) goto pos36700;
	mem58 = X0;
	goto pos37184;

	// --------------

pos37404:
	Code37066(mem58);
	A0 = A0 & 32;
	if(A0 == 0) goto pos36700;
pos37414:
	mem58 = X0;
	goto pos37184;

	// --------------

pos37419:
	X0 = mem58;
	X0++;
	A0 = strInputCopy[X0];
	if ((A0 == 69) || (A0 == 73) || (A0 == 89)) goto pos37414;
	goto pos36700;

	// --------------

pos37440:
	Code37066(mem58);
	A0 = A0 & 32;
	if(A0 == 0) goto pos37184;
	mem58 = X0;
	goto pos37440;
pos37455:
	Y0 = mem64;
	mem61 = mem60;
pos37461:
	//37461: LDA (62),Y0
	A0 = GetRuleByte(mem62, mem63, Y0);
	mem57 = A0;
	A0 = A0 & 127;
	if (A0 != 61)
	{
		mem56++;
		X0 = mem56;
		input[X0] = A0;
	}

	//37478: BIT 57
	//37480: BPL 37485  //not negative flag
	if ((mem57 & 128) == 0 )goto pos37485; //???
	goto pos36554;
pos37485:
	Y0++;
	goto pos37461;

}



