#pragma bank=2
#include "SpriteMissile.h"
#include "Keys.h"
#include "SpriteManager.h"
#include "ZGBMain.h"
#include "Print.h"

UINT8 bank_SPRITE_MISSILE = 2;

extern UINT8 missiles;

const UINT8 anim_mis[] = {4, 0, 1,2,1};


struct MissileData
{
	fixed vx;
	fixed vy;
	fixed tx;
	fixed ty;
	UINT8 ttl;
};

void Start_SPRITE_MISSILE() 
{
	THIS-> coll_w = 8;
	THIS-> coll_h = 8;
	THIS-> coll_x = 4;
	THIS-> coll_y = 4;
	SetSpriteAnim(THIS, anim_mis, 15);
}

void Update_SPRITE_MISSILE() 
{
	struct MissileData* data = THIS -> custom_data;
	UINT8 tile_collision;
	
	data->tx.w += data->vx.w;
	tile_collision = TranslateSprite(THIS, data->tx.b.h << delta_time,0	);
	if(tile_collision)
	{	
		SpriteManagerRemove(THIS_IDX);
	}
	data->tx.b.h = 0;
	
	
	data->ty.w += data->vy.w;
	tile_collision = TranslateSprite(THIS, 0,data->ty.b.h << delta_time	);
	if(tile_collision)
	{
		SpriteManagerRemove(THIS_IDX);
	}
	data->ty.b.h = 0;
}

void Destroy_SPRITE_MISSILE() 
{
	missiles -= 1u;
	SpriteManagerAdd(SPRITE_EXPLOSION, THIS->x, THIS->y);
}