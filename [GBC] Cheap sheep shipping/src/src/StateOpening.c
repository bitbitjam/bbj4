#pragma bank=2
#include "StateOpening.h"
UINT8 bank_STATE_OPENING = 2;

#include "ZGBMain.h"
#include "Scroll.h"
#include "SpriteManager.h"

#include "..\res\src\OpeningTiles.h"
#include "..\res\src\OpeningMap.h"

#include "Tool.h"
#include "gbt_player.h"

#include "Palette.h"
#include "Keys.h"

extern UINT8 CheapActualLevel;
extern UINT8* jingle_mod_Data[];

const UINT16 bgOpening_palette[] = {PALETTE_FROM_HEADER(OpeningTiles)};

void Start_STATE_OPENING() {
	
	CheapActualLevel = 0;
	
	NR52_REG = 0x80; //Enables sound, you should always setup this first
    NR51_REG = 0xFF; //Enables all channels (left and right)
    NR50_REG = 0x77; //Max volume
	
	HIDE_WIN;
	
	SetPalette(BG_PALETTE, 0, 8, bgOpening_palette, bank_STATE_OPENING);
	
	PlayMusic(jingle_mod_Data, 4, 0);
	
	InitScrollTilesColor(0, 128, OpeningTiles, 4);
	InitScroll(OpeningMapWidth, OpeningMapHeight, OpeningMap, 0, 0, 4);
	SHOW_BKG;
	
}

void Update_STATE_OPENING() {

	//para que al pasar de nivel se alcance a leer la historia
	if (KEY_TICKED(J_B)){
		SetState(STATE_TITLE);
	}
}