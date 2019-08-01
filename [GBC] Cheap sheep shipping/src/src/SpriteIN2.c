#pragma bank=2
#include "ZGBMain.h"

#include "SpriteManager.h"

#include "SpriteIN2.h"
#include "SpriteIN1.h"

UINT8 bank_SPRITE_IN2 = 2;

const UINT8 anim_rightIN2[] = {2, 2, 6};

void Start_SPRITE_IN2() {
	
	struct AnimData* data = THIS->custom_data;
	SetSpriteAnim(THIS, anim_rightIN2, 30);
	data -> count = 0;
}

void Update_SPRITE_IN2(){
	struct AnimData* data = THIS->custom_data;
	data -> count++;
	if (data -> count == 8) {
		THIS -> x ++;
		data -> count = 0;
	}
}

void Destroy_SPRITE_IN2(){
	
}