#pragma bank=2
#include "SpriteEnemy1.h"
#include "Keys.h"
#include "SpriteManager.h"
#include "ZGBMain.h"

UINT8 bank_SPRITE_ENEMY1 = 2;
const UINT8 anim_idle[] = {6, 0,1,2,2,1,0};

extern UINT8 game_paused;

struct EnemyInfo
{
	fixed vy;
	fixed ty;
};


void Start_SPRITE_ENEMY1() 
{
	struct EnemyInfo* data = THIS -> custom_data;
	data->vy.b.l = 1 << 6;
	THIS->lim_x = 130;
	THIS->lim_y = 130;
	SetSpriteAnim(THIS, anim_idle, 8);
}

void Update_SPRITE_ENEMY1() 
{
	struct EnemyInfo* data = THIS -> custom_data;
	UINT8 i;
	struct Sprite* spr;
	UINT8 tile_collision;

	if(game_paused == 1)
	{
		return;
	}
	
	data->ty.w += data->vy.w;
	tile_collision = TranslateSprite(THIS, 0,data->ty.b.h << delta_time	);
	if(tile_collision)
	{
		data->vy.w = -data->vy.w;
	}
	data->ty.b.h = 0;
	
	SPRITEMANAGER_ITERATE(i, spr)
	{
		if(spr->type == SPRITE_MISSILE)
		{				
			if(CheckCollision(THIS,spr))
			{				
				SpriteManagerAdd(SPRITE_EXPLOSION, THIS->x, THIS->y);
				SpriteManagerRemove(THIS_IDX);								
				SpriteManagerRemove(i);				
			}
		}
	}
}

void Destroy_SPRITE_ENEMY1() 
{

}