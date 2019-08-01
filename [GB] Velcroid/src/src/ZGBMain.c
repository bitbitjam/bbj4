#include "ZGBMain.h"

#include "StateMenu.h"
#include "StateGame.h"
#include "StateWin.h"
#include "StateStory.h"


#include "SpritePlayer.h"
#include "SpriteEnemy1.h"
#include "SpriteTarget.h"
#include "SpriteExplosion.h"
#include "SpriteBooster.h"
#include "SpriteMissile.h"
#include "SpritePlasmaUpgrade.h"

#include "../res/src/sheep.h"
#include "../res/src/explosion.h"
#include "../res/src/enemy1.h"
#include "../res/src/target.h"
#include "../res/src/booster.h"
#include "../res/src/missile.h"
#include "../res/src/plasmaupgrade.h"

UINT8 next_state = STATE_STORY;

SET_N_STATES(N_STATES);
SET_N_SPRITE_TYPES(N_SPRITE_TYPES);

void InitStates() {
	INIT_STATE(STATE_STORY);
	INIT_STATE(STATE_MENU);
	INIT_STATE(STATE_GAME);
	INIT_STATE(STATE_WIN);
}

void InitSprites() {
	INIT_SPRITE(SPRITE_PLAYER, sheep, 3, FRAME_16x16, 16);
	INIT_SPRITE(SPRITE_ENEMY1, enemy1, 3, FRAME_16x16, 3);
	INIT_SPRITE(SPRITE_EXPLOSION, explosion, 3, FRAME_16x16, 5);	
	INIT_SPRITE(SPRITE_BOOSTER, booster, 3, FRAME_16x16, 20);	
	INIT_SPRITE(SPRITE_TARGET, target, 3, FRAME_16x16, 5);	
	INIT_SPRITE(SPRITE_MISSILE, missile, 3, FRAME_16x16, 5);	
	INIT_SPRITE(SPRITE_PLASMAUPGRADE, plasmaupgrade, 3, FRAME_16x16, 5);	
}

#include "Math.h"
UINT8 GetTileReplacement(UINT8* tile_ptr, UINT8* tile) {
	if(current_state == STATE_GAME) {
		if(U_LESS_THAN(255 - (UINT16)*tile_ptr, N_SPRITE_TYPES)) {
			*tile = 0;
			return 255 - (UINT16)*tile_ptr;
		}

		*tile = *tile_ptr;
	}

	return 255u;
}