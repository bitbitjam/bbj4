#pragma bank=2
#include "StatePre.h"
UINT8 bank_STATE_PRE = 2;

#include "ZGBMain.h"
#include "Scroll.h"
#include "SpriteManager.h"

#include "..\res\src\shippyTiles2.h"
#include "..\res\src\PreLevel1Map.h"
#include "..\res\src\PreLevel2Map.h"
#include "..\res\src\PreLevel3Map.h"
#include "..\res\src\PreLevelEndingMap.h"

#include "Tool.h"
#include "gbt_player.h"

#include "Palette.h"
#include "Keys.h"

extern UINT8 CheapActualLevel;
extern UINT8* jingle_mod_Data[];

extern const UINT16 bg_palette[];
extern UINT8 n_sprite_types;

UINT16 precont = 0;

void Start_STATE_PRE() {
	
	UINT8 i;
	unsigned char *selectedPre;
	UINT16 selectedPreW;
	UINT16 selectedPreH;
	
	for(i = 0; i != n_sprite_types; ++ i) {
		SpriteManagerLoad(i);
	}
	
	precont = 0;
	HIDE_WIN;
	
	SetPalette(BG_PALETTE, 0, 8, bg_palette, bank_STATE_PRE);
	
	switch(CheapActualLevel) {
		case 0:
			selectedPre = PreLevel1Map;
			selectedPreW = PreLevel1MapWidth;
			selectedPreH = PreLevel1MapHeight;
			break;
		case 1:
			selectedPre = PreLevel2Map;
			selectedPreW = PreLevel2MapWidth;
			selectedPreH = PreLevel2MapHeight;
			break;
		case 2:
			selectedPre = PreLevel3Map;
			selectedPreW = PreLevel3MapWidth;
			selectedPreH = PreLevel3MapHeight;
			break;
		case 3:
			selectedPre = PreLevelEndingMap;
			selectedPreW = PreLevelEndingMapWidth;
			selectedPreH = PreLevelEndingMapHeight;
			break;
		default:
			break;
	}
	
	
	PlayMusic(jingle_mod_Data, 4, 0);
	
	InitScrollTilesColor(0, 128, ShippyTiles2, 3);
	InitScroll(selectedPreW, selectedPreH, selectedPre, 0, 0, 3);
	SHOW_BKG;
	
}

void Update_STATE_PRE() {
	precont++;
	//para que al pasar de nivel se alcance a leer la historia
	if (precont > 60 && KEY_TICKED(J_B)){
		if (CheapActualLevel == 3) {
			SetState(STATE_OPENING);
		} else {
			SetState(STATE_GAME);
		}
	}
}