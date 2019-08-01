#ifndef ZGBMAIN_H
#define ZGBMAIN_H

#include "main.h"

typedef enum {
	STATE_BOOT,
	STATE_OPENING,
	STATE_TITLE,
	STATE_PRE,
	STATE_GAME,

	N_STATES
} STATE;

typedef enum {
	SPRITE_PLAYER,
	SPRITE_HELIFOLLOWER,
	SPRITE_FIREA,
	SPRITE_SHEEP,
	SPRITE_IN1,
	SPRITE_IN2,
	SPRITE_IN3,

	N_SPRITE_TYPES
} SPRITE_TYPE;

#endif