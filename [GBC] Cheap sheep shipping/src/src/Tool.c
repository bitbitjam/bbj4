#include "Tool.h"
#include "ZGBMain.h"

#include "Print.h"
#include "BankManager.h"
#include "Scroll.h"

#include <stdarg.h>

#include "..\res\src\ShippyTiles2.h"

const unsigned  char SheepyWindowTemplate[] =
{
  0x6E,0x6F,0x6F,0x6F,0x6F,0x6F,0x6F,0x6F,0x6F,0x6F,
  0x6F,0x6F,0x6F,0x6F,0x6F,0x6F,0x6F,0x6F,0x6F,0x70,
  0x74,0x50,0x52,0x45,0x53,0x53,0x7F,0x42,0x7F,0x46,
  0x4F,0x52,0x7F,0x52,0x49,0x47,0x48,0x54,0x30,0x73
};

const unsigned char crash[] = {0x74,0x7F,0x7F,0x5D,0x5D,0x5D,0x7F,0x43,0x52,0x41, 0x53,0x48,0x5B,0x7F,0x5D,0x5D,0x5D,0x7F,0x7F,0x73}; //0
const unsigned char up[] = {0x7F,0x55,0x50,0x5B,0x5B,0x7F,0x2E,0x73}; //13
const unsigned char left[] = {0x7F,0x4C,0x45,0x46,0x54,0x5B,0x2F,0x73}; //13
const unsigned char congrats[] = {0x74,0x7F,0x43,0x4F,0x4E,0x47,0x52,0x41,0x54,0x55, 0x4C,0x41,0x54,0x49,0x4F,0x4E,0x53,0x5B,0x7F,0x73};


void Cheap_initWindow() {
	
	/*print_target = PRINT_WIN;
	print_x = 0;
	print_y = 0;
	font_idx = 255 - 45;
	
	SHOW_WIN;
	//InitWindow(0, 0, 3, 3, testWin, 3);
	set_win_tiles(print_x, print_y, 1, 1, font_idx + 37);*/
	INIT_FONT(ShippyTiles2, 3, PRINT_WIN);
	WX_REG = 7;
	WY_REG = (144 - (2 << 3));
	InitScrollTilesColor(0x80, 128, ShippyTiles2, 3); //yap, los cargo en la vram
	
}

void Cheap_drawWindow() {
	/*PRINT_POS(0, 0);
	Printf("Test text");
	PRINT_POS(0, 0);
	Cheap_customCHAR(0xEE);*/ //65 193
	UINT8 i;
	for (i=0; i<20; i++) {
		PRINT_POS(i, 0);
		Cheap_customCHAR(SheepyWindowTemplate[i] + 128);
	}
	for (i=20; i<40; i++) {
		PRINT_POS(i-20, 1);
		Cheap_customCHAR(SheepyWindowTemplate[i] + 128);
	}
	Cheap_drawUp();
	
}

void Cheap_drawLeft() {
	UINT8 i;
	for (i=0; i<8; i++) {
		PRINT_POS(12+i, 1);
		Cheap_customCHAR(left[i] + 128);
	}
}

void Cheap_drawRight() {
	UINT8 i;
	for (i=33; i<40; i++) {
		PRINT_POS(i-20, 1);
		Cheap_customCHAR(SheepyWindowTemplate[i] + 128);
	}
}

void Cheap_drawUp() {
	UINT8 i;
	for (i=0; i<8; i++) {
		PRINT_POS(12+i, 1);
		Cheap_customCHAR(up[i] + 128);
	}
	
}

void Cheap_drawCongrats() {
	UINT8 i;
	for (i=0; i<20; i++) {
		PRINT_POS(i, 1);
		Cheap_customCHAR(congrats[i] + 128);
	}
}

void Cheap_drawCrash() {
  	UINT8 i;
	for (i=0; i<20; i++) {
		PRINT_POS(i, 1);
		Cheap_customCHAR(crash[i] + 128);
	}
}

void Cheap_drawHIDE() {
	HIDE_WIN;
}

void Cheap_drawSHOW() {
	SHOW_WIN;
}


void Cheap_customCHAR(unsigned char c){
	set_win_tiles(print_x, print_y, 1, 1, &c);
}