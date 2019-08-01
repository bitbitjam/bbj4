#pragma bank=1
#include "ZGBMain.h"
UINT8 init_bank = 1;

#include "StateGame.h"
#include "StatePre.h"
#include "StateBoot.h"
#include "StateOpening.h"
#include "StateTitle.h"

#include "SpritePlayer.h"
#include "SpriteHeliFollower.h"
#include "SpriteFireA.h"
#include "SpriteSheep.h"
#include "SpriteIN1.h"
#include "SpriteIN2.h"
#include "SpriteIN3.h"

#include "../res/src/helicopterSprite.h"
#include "../res/src/fireSprite.h"
#include "../res/src/sheepSprite.h"

UINT8 next_state = STATE_BOOT;
UINT8 CheapActualLevel = 0;

SET_N_STATES(N_STATES);
SET_N_SPRITE_TYPES(N_SPRITE_TYPES);

void InitStates() {
	INIT_STATE(STATE_BOOT);
	INIT_STATE(STATE_OPENING);
	INIT_STATE(STATE_TITLE);
	INIT_STATE(STATE_PRE);
	INIT_STATE(STATE_GAME);
}

void InitSprites() {
	//CONST, textura, banco, tamanio frame, cuantos frames cargo
	INIT_SPRITE_COLOR(SPRITE_PLAYER, helicopterSprite, 3, FRAME_16x16, 8);
	INIT_SPRITE_COLOR(SPRITE_HELIFOLLOWER, helicopterSprite, 3, FRAME_16x16, 8);
	INIT_SPRITE_COLOR(SPRITE_FIREA, fireSprite, 3, FRAME_16x16, 8);
	INIT_SPRITE_COLOR(SPRITE_SHEEP, sheepSprite, 3, FRAME_16x16, 8);
	INIT_SPRITE_COLOR(SPRITE_IN1, helicopterSprite, 3, FRAME_16x16, 8);
	INIT_SPRITE_COLOR(SPRITE_IN2, helicopterSprite, 3, FRAME_16x16, 8);
	INIT_SPRITE_COLOR(SPRITE_IN3, sheepSprite, 3, FRAME_16x16, 8);
	//INIT_SPRITE_COLOR(SPRITE_STARTPOS, nullSprite, 3, FRAME_16x16, 1);
}