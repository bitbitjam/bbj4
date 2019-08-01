#pragma bank=2
#include "ZGBMain.h"

#include "SpriteManager.h"

#include "SpriteIN3.h"
#include "SpriteIN1.h"

UINT8 bank_SPRITE_IN3 = 2;

const UINT8 anim_IN3[] = {1, 4};

void Start_SPRITE_IN3() {
	
	struct AnimData* data = THIS->custom_data;
	SetSpriteAnim(THIS, anim_IN3, 15);
	data -> count = 0;
}

void Update_SPRITE_IN3(){
	struct AnimData* data = THIS->custom_data;
	data -> count++;
	if (data -> count == 8) {
		THIS -> x ++;
		data -> count = 0;
	}
}

void Destroy_SPRITE_IN3(){
	
}