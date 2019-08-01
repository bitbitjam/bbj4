#pragma bank=2
#include "ZGBMain.h"

#include "SpriteManager.h"
#include "SpritePlayer.h"

#include "SpriteSheep.h"
#include "Print.h"
#include "Keys.h"

UINT8 bank_SPRITE_SHEEP = 2;

UINT8 SheepCreated;
UINT8 SheepTaken;

extern INT8 HeliIsCrashed;
extern INT8 HeliX;
extern INT8 HeliY;
extern struct Sprite* HeliPtr;
extern struct Sprite* HeliFollowerPtr;

const UINT8 anim_sheepIDLE[] = {2, 0, 1};
const UINT8 anim_sheepDOWN[] = {1, 2};
const UINT8 anim_sheepUP[] = {1, 5};
const UINT8 anim_sheepLEFT[] = {1, 3};
const UINT8 anim_sheepRIGHT[] = {1, 4};

void Start_SPRITE_SHEEP() {
	
	if (SheepCreated && SheepTaken) {
		SpriteManagerRemove(THIS);
		return;
	} 
	
	SheepCreated = 1;
	SheepTaken = 0;
	SetSpriteAnim(THIS, anim_sheepIDLE, 15);
	
	THIS -> lim_x = 300;
	THIS -> lim_y = 300;
}

void Update_SPRITE_SHEEP() {
	if (SheepTaken==1) {
		THIS -> x = (HeliPtr) -> x;
		THIS -> y = (HeliPtr) -> y + 8;
	}
}

void Destroy_SPRITE_SHEEP() {
	
}