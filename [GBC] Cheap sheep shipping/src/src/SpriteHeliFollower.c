#pragma bank=2
#include "ZGBMain.h"

#include "SpriteManager.h"

#include "SpriteHeliFollower.h"
#include "SpritePlayer.h"
#include "Print.h"
#include "Keys.h"


UINT8 bank_SPRITE_HELIFOLLOWER = 2;

const UINT8 anim_leftB[] = {2, 1, 5};
const UINT8 anim_rightB[] = {2, 2, 6};

struct Sprite* original_player;
struct Sprite* HeliFollowerPtr;


void Start_SPRITE_HELIFOLLOWER() {
	//obtener posicion del sprite player -16 o +16 dependiendo
	
	struct Sprite* spr;
	UINT8 i;
	
	HeliFollowerPtr = THIS;
	
	//buscar SPRITE_PLAYER
	SPRITEMANAGER_ITERATE(i, spr) {
		if(spr->type == SPRITE_PLAYER) {
			original_player = spr;
		}
	}
	
	//empieza siempre izquierda
	THIS -> x = original_player -> x - 16;
	THIS -> y = original_player -> y;
	THIS -> lim_x = 300;
	THIS -> lim_y = 300;
	
	SetSpriteAnim(THIS, anim_leftB, 30); //velocidad en fps
	
}

void Update_SPRITE_HELIFOLLOWER() {
	//obtener datos del sprite original
	struct HeliShareDataA* data = original_player->custom_data;
	
	//si va a la derecha
	if (data->dir == 0) {
		SetSpriteAnim(THIS, anim_leftB, 30);
		THIS -> x = original_player -> x + 16;
	} else {
		//izquierda
		SetSpriteAnim(THIS, anim_rightB, 30);
		THIS -> x = original_player -> x - 16;
	}
	THIS -> y = original_player -> y;
	
}

void Destroy_SPRITE_HELIFOLLOWER() {
	
}
