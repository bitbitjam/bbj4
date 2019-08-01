#pragma bank=2
#include "StateGame.h"
UINT8 bank_STATE_GAME = 2;

#include "..\res\src\shippyTiles2.h"
#include "..\res\src\testLevel2.h"
#include "..\res\src\hardLevel.h"
#include "..\res\src\OMFGLevel.h"

#include "../res/src/helicopterSprite.h"
#include "../res/src/fireSprite.h"
#include "../res/src/sheepSprite.h"

#include "ZGBMain.h"
#include "Scroll.h"
#include "SpriteManager.h"

#include "Tool.h"
#include "gbt_player.h"

#include "Palette.h"
const UINT16 bg_palette[] = {PALETTE_FROM_HEADER(ShippyTiles2)};
extern UINT8* idle_mod_Data[];
//const UINT16 sprites_palette[] = {PALETTE_FROM_HEADER(helicopterSprite)};

UINT16 sprites_palette[] = {
	PALETTE_INDEX(helicopterSprite, 0),
	PALETTE_INDEX(fireSprite, 1),
	PALETTE_INDEX(sheepSprite,  2),
	PALETTE_INDEX(helicopterSprite, 3),
	PALETTE_INDEX(helicopterSprite, 4),
	PALETTE_INDEX(helicopterSprite, 5),
	PALETTE_INDEX(helicopterSprite, 6),
	PALETTE_INDEX(helicopterSprite, 7)
};

extern UINT8 HeliIsCrashed;
extern SheepCreated;

INT16 AirportINIT;
INT16 AirportEND;
INT16 DropZoneINIT;
INT16 DropZoneEND;

extern UINT8 CheapActualLevel;

void Start_STATE_GAME() {
	UINT8 i;
	UINT8 collision_tiles[] = {121, 122, 32, 33, 41, 42, 43, 0}; //termina siempre en 0
	
	UINT16 heliStartX, heliStartY;
	UINT16 sheeStartX, sheeStartY;
	
	unsigned char *selectedLevel;
	UINT16 selectedLevelW;
	UINT16 selectedLevelH;
	
	PlayMusic(idle_mod_Data, 4, 1);
	
	SetPalette(BG_PALETTE, 0, 8, bg_palette, bank_STATE_GAME);
	SetPalette(SPRITES_PALETTE, 0, 8, sprites_palette, bank_STATE_GAME);
	
	SheepCreated = 0;
	
	switch(CheapActualLevel) {
		case 0:
			selectedLevel = TestLevel2;
			selectedLevelW = TestLevel2Width;
			selectedLevelH = TestLevel2Height;
			break;
		case 1:
			selectedLevel = HardLevel;
			selectedLevelW = HardLevelWidth;
			selectedLevelH = HardLevelHeight;
			break;
		case 2:
			selectedLevel = OMFGLevel;
			selectedLevelW = OMFGLevelWidth;
			selectedLevelH = OMFGLevelHeight;
			break;
		default:
			break;
	}
	
	
	//buscar puntos de partida para oveja y para helicoptero
	//ScrollFindTile(TestLevel2Width, TestLevel2Height, TestLevel2, 3, 44, &heliStartX, &heliStartY);
	ScrollFindTile(selectedLevelW, selectedLevel, 3, 44, 0, 0, selectedLevelW, selectedLevelH, &heliStartX, &heliStartY);
	heliStartX <<=3;
	heliStartY = (heliStartY -1) <<=3;
	
	//heliStartX = 0;
	//heliStartY = 0;
	//
	
	ScrollFindTile(selectedLevelW, selectedLevel, 3, 49, 0, 0, selectedLevelW, selectedLevelH, &AirportINIT, &i);
	ScrollFindTile(selectedLevelW, selectedLevel, 3, 50, 0, 0, selectedLevelW, selectedLevelH, &AirportEND, &i);
	ScrollFindTile(selectedLevelW, selectedLevel, 3, 51, 0, 0, selectedLevelW, selectedLevelH, &DropZoneINIT, &i);
	ScrollFindTile(selectedLevelW, selectedLevel, 3, 52, 0, 0, selectedLevelW, selectedLevelH, &DropZoneEND, &i);

	scroll_target = SpriteManagerAdd(SPRITE_PLAYER, heliStartX, heliStartY);
	SpriteManagerAdd(SPRITE_HELIFOLLOWER, 0, 0);
	SpriteManagerAdd(SPRITE_FIREA, 0, 0);
	
	//INIT_CONSOLE(font, 3, 2);
	
	//18 es suelo firme
	//37, 44 son alternativas a suelo firme
	//41 42 43 es cancha aterrizaje
	//
	InitScrollTilesColor(0, 127, ShippyTiles2, 3);
	InitScroll(selectedLevelW, selectedLevelH, selectedLevel, collision_tiles, 0, 3);
	SHOW_BKG;
	
	//set_win_data(0,44,font);
	Cheap_initWindow();
	Cheap_drawSHOW();
	Cheap_drawWindow();
	//Cheap_drawCongrats();
	
}

void Update_STATE_GAME() {
	//SHOW_WIN;
}