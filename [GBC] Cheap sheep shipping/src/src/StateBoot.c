#pragma bank=2
#include "StateBoot.h"
UINT8 bank_STATE_BOOT = 2;

#include "ZGBMain.h"
#include "Scroll.h"
#include "SpriteManager.h"

#include "..\res\src\BootTiles.h"
#include "..\res\src\BootMap.h"

#include "Tool.h"
#include "gbt_player.h"

#include "Palette.h"
#include "Keys.h"

const UINT16 bgBoot_palette[] = {PALETTE_FROM_HEADER(BootTiles)};
extern UINT8 n_sprite_types;

UINT16 cheapInitCounter;

void Start_STATE_BOOT() {
	
	UINT8 i;
	
	cheapInitCounter = 0;
	
	SPRITES_8x16;
	for(i = 0; i != n_sprite_types; ++ i) {
		SpriteManagerLoad(i);
	}
	SHOW_SPRITES;
	
	NR52_REG = 0x80; //Enables sound, you should always setup this first
    NR51_REG = 0xFF; //Enables all channels (left and right)
    NR50_REG = 0x77; //Max volume
	
	HIDE_WIN;
	
	SetPalette(BG_PALETTE, 0, 8, bgBoot_palette, bank_STATE_BOOT);

	InitScrollTilesColor(0, 128, BootTiles, 4);
	InitScroll(BootMapWidth, BootMapHeight, BootMap, 0, 0, 4);
	SHOW_BKG;
	
}

void Update_STATE_BOOT() {
	cheapInitCounter++;
	if (cheapInitCounter > 120) {
		SetState(STATE_OPENING);
	}
	//para que al pasar de nivel se alcance a leer la histor
}