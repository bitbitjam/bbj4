#ifndef ZCONSOLE_H
#define ZCONSOLE_H

#include <gb/gb.h> 
#include "ZGBConfig.h"

#define FONT_TILE_COUNT 59
#define INIT_FONT(FONT, FONT_BANK, TARGET)  InitScrollTiles(255 - FONT_TILE_COUNT, FONT_TILE_COUNT, FONT, FONT_BANK); \
											font_idx = 255 - FONT_TILE_COUNT; print_target = TARGET

extern UINT8 print_x, print_y, font_idx, print_target;

typedef enum {
	PRINT_BKG,
	PRINT_WIN
} PRINT_TARGET;


void UIntToString(UINT16 n, unsigned char* str);
#ifdef PRINT_SIGNED_ENABLED
void IntToString (INT16  n, unsigned char* str);
#endif
#ifdef PRINT_HEX_ENABLED
void UIntToHexString(UINT16 n, unsigned char* str);
#endif

void Printf(const char* txt, ...);
#define PRINT_POS(X, Y) print_x = X; print_y  = Y
#define PRINT(X, Y, TXT) PRINT_POS(X,Y); Printf(TXT)

#ifdef NDEBUG 
#define INIT_CONSOLE
#define DPrintf
#define DPRINT_POS
#define DPRINT
#else
#define INIT_CONSOLE(FONT, FONT_BANK, NLINES) \
	print_target = PRINT_WIN;\
	print_x = 0;\
	print_y = 0;\
	font_idx = 255 - FONT_TILE_COUNT;\
	InitScrollTiles(255 - FONT_TILE_COUNT, FONT_TILE_COUNT, FONT, FONT_BANK);\
	WX_REG = 7;\
  WY_REG = (144 - (NLINES << 3));\
	SHOW_WIN;

#define DPrintf Printf
#define DPRINT_POS PRINT_POS
#define DPRINT PRINT

#endif


#endif
