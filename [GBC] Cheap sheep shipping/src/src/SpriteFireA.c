#pragma bank=2
#include "ZGBMain.h"

#include "SpriteManager.h"

#include "SpriteFireA.h"
#include "Print.h"
#include "Keys.h"

#include "SpritePlayer.h"
#include "SpriteHeliFollower.h"

UINT8 bank_SPRITE_FIREA = 2;

extern UINT8 HeliLevelComplete;

const UINT8 anim_fireIA[] = {1, 6};
const UINT8 anim_fireBA[] = {1, 4};
const UINT8 anim_fireFA[] = {2, 0, 2};

UINT8 fireABoomCounter;
UINT8 fireActivated;

extern INT8 HeliIsCrashed;
extern INT8 HeliX;
extern INT8 HeliY;
extern struct Sprite* HeliPtr;
extern struct Sprite* HeliFollowerPtr;


void Start_SPRITE_FIREA() {
	fireABoomCounter = 0;
	fireActivated = 0;
	SetSpriteAnim(THIS, anim_fireIA, 30);
	THIS -> x = HeliPtr -> x;
	THIS -> y = HeliPtr -> y;
	
}

void Update_SPRITE_FIREA() {
	
	THIS -> x = HeliPtr -> x;
	THIS -> y = HeliPtr -> y;
	
	if (HeliIsCrashed == 1) {
		SetSpriteAnim(THIS, anim_fireFA, 30);
		fireActivated = 1;
		HeliIsCrashed = 2;
	}
	
	if (fireActivated) {
		fireABoomCounter++;
		/*if (fireABoomCounter > 30 && HeliIsCrashed == 2) {
			SetSpriteAnim(THIS, anim_fireFA, 30);
			HeliIsCrashed = 3;
		}*/
		
		if (fireABoomCounter == 90) {
			SetState(STATE_GAME);
		}
	}
	
}

void Destroy_SPRITE_FIREA() {
	if (!HeliLevelComplete) {
		SetState(STATE_GAME);
	}
}