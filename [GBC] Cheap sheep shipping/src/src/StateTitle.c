#pragma bank=2
#include "StateTitle.h"
UINT8 bank_STATE_TITLE = 2;

#include "ZGBMain.h"
#include "Scroll.h"
#include "SpriteManager.h"

#include "..\res\src\TitleTiles.h"
#include "..\res\src\TitleMap.h"

#include "Tool.h"
#include "gbt_player.h"

#include "Palette.h"
#include "Keys.h"

extern UINT8 CheapActualLevel;
extern UINT8* main_mod_Data[];

const UINT16 bgTitle_palette[] = {PALETTE_FROM_HEADER(TitleTiles)};
extern UINT16 sprites_palette[];

void Start_STATE_TITLE() {
	
	CheapActualLevel = 0;
	
	HIDE_WIN;
	
	SetPalette(BG_PALETTE, 0, 8, bgTitle_palette, bank_STATE_TITLE);
	SetPalette(SPRITES_PALETTE, 0, 8, sprites_palette, bank_STATE_TITLE);
	
	PlayMusic(main_mod_Data, 4, 1);
	
	SpriteManagerLoad(SPRITE_IN1);
	SpriteManagerLoad(SPRITE_IN2);
	SpriteManagerLoad(SPRITE_IN3);
	SpriteManagerAdd(SPRITE_IN1, 0, 88);
	SpriteManagerAdd(SPRITE_IN2, -16, 88);
	SpriteManagerAdd(SPRITE_IN3, 0, 96);
	
	InitScrollTilesColor(0, 160, TitleTiles, 3);
	InitScroll(TitleMapWidth, TitleMapHeight, TitleMap, 0, 0, 3);
	SHOW_BKG;
	
}

void Update_STATE_TITLE() {

	//para que al pasar de nivel se alcance a leer la historia
	if (KEY_TICKED(J_B)){
		SetState(STATE_PRE);
	}
}