#ifndef ZGBMAIN_H
#define ZGBMAIN_H

#include "main.h"

typedef enum {
	STATE_GAME,
	STATE_MENU,
	STATE_GAMEOVER,
	STATE_GAMEEND,

	N_STATES
} STATE;

typedef enum {
	SPRITE_PLAYER,
	SPRITE_CROSSHAIR,
	SPRITE_BIRD,
	SPRITE_WOLF,
	SPRITE_POLKAMAN,
	SPRITE_LIFE,
	SPRITE_PLATFORM,
	SPRITE_BUBBLE,
	SPRITE_POP,
	SPRITE_FRIENDSHEEP,

	N_SPRITE_TYPES
} SPRITE_TYPE;

#endif