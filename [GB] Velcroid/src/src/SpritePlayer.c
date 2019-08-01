#pragma bank=2
#include "SpritePlayer.h"
#include "Keys.h"
#include "SpriteManager.h"
#include "ZGBMain.h"
#include "Math.h"
#include "Print.h"

UINT8 bank_SPRITE_PLAYER = 2;
const UINT8 anim_walk_left[] = {2, 1, 0};
const UINT8 anim_idle_left[] = {1, 0};

const UINT8 anim_boost_down[] = {5, 0,1,2,3,4};
const UINT8 anim_lowburn_down[] = {2,3,4};

const UINT8 anim_boost_left[] = {5, 5,6,7,8,9};
const UINT8 anim_lowburn_left[] = {2,8,9};

const UINT8 anim_boost_up[] = {5, 10,11,12,13,14};
const UINT8 anim_lowburn_up[] = {2,13,14};

const UINT8 anim_boost_right[] = {5, 15,16,17,18,19};
const UINT8 anim_lowburn_right[] = {2,18,19};



const UINT8 maxForce = 60;
const UINT8 maxMissileTimer = 80;
const UINT8 distance = 100;
const UINT8 accel = 10;


struct PlayerData
{	
	fixed vx;
	fixed vy;
	fixed tx;
	fixed ty;
};




UINT8 dir = 1;


INT8 forceRemaining = 0;

struct Sprite* enemies[10];

struct Sprite* sprBooster;

struct Sprite* selectedEnemy;
UINT8 selectedIndex;


UINT16 lastDistance;
UINT8 pressCounter = 0;
UINT8 numEnemies = 0;
UINT8 tile_collision = 0;
UINT8 missileTimer = 0;

INT16 DispLeft(INT16 a, INT16 b) {
	return a >> b;
}

INT16 DispRight(INT16 a, INT16 b) {
	return a << b;
}


extern UINT8 plasma_upgraded;
extern UINT8 show_win;
extern UINT8 text_index;
extern UINT8 next_room;
extern UINT8 current_room;
extern UINT8 entry_point;
extern UINT8 game_paused;

UINT8 missiles;

void OnVelcroCollision()
{
	struct PlayerData* playerData = (struct PlayerData*) THIS-> custom_data;
	playerData-> vy.w = 0;
	playerData-> vx.w = 0;
}

void CheckCollisionTile() 
{
	switch(tile_collision) 
	{
		case 27u:
			OnVelcroCollision();
			break;
		case 28u:
			OnVelcroCollision();
			break;
		case 29u:
			OnVelcroCollision();
			break;
		case 30u:
			OnVelcroCollision();
			break;
		case 31u:
			entry_point = 0;
			SetState(STATE_GAME);
			break;
		case 32u:
			entry_point = 1;
			SetState(STATE_GAME);
			break;
		case 33u:
			entry_point = 2;
			SetState(STATE_GAME);
			break;
		case 34u:
			entry_point = 3;
			SetState(STATE_GAME);
			break;
		case 39u:
			SetState(STATE_MENU);
			break;
		case 41u:
			SetState(STATE_MENU);
			break;
		case 42u:
			SetState(STATE_MENU);
			break;
		case 43u:
			SetState(STATE_MENU);
			break;
	}
}

void Start_SPRITE_PLAYER() 
{
	struct PlayerData* playerData = (struct PlayerData*) THIS-> custom_data;
	sprBooster = SpriteManagerAdd(SPRITE_BOOSTER, THIS-> x, THIS-> y -10);
	THIS->coll_w = 15;
	THIS->coll_h = 15;
	playerData->vx.w = 0;
	playerData->vy.w = 0;
	missiles = 0;
}

void 	Update_SPRITE_PLAYER() 
{
	struct PlayerData* playerData = (struct PlayerData*) THIS-> custom_data;
	struct PlayerData* missileData;
	struct Sprite* mis;
	struct Sprite* spr;
	UINT8 i;
	
	if(game_paused==1)
	{
		return;
	}
	
	if(KEY_TICKED(J_A) ) 
	{
	}
	
	
	DPRINT_POS(0,0);
	//DPrintf("x:%d y:%d  ", THIS->x, THIS->y);
	DPrintf("CR: %d, NR: %d",current_room, next_room);
	
	if(KEY_PRESSED(J_A))
	{
		pressCounter+= 1;		
		if(pressCounter > 5)
		{
			switch(dir)
			{
				case 0:		
					if( missiles <  3 && pressCounter == 8 && plasma_upgraded)
					{
						missileTimer = maxMissileTimer;
						missiles += 1;
						mis = SpriteManagerAdd(SPRITE_MISSILE, THIS->x, THIS->y+8);
						missileData = mis->custom_data;
						missileData->vy.w  = 300;
						missileData->vx.w  = 0;
					}
					
					playerData->vy.w -= accel ;
				break;
				case 1:
					playerData-> vx.w +=  accel;	
					
					if(missiles <  3 && pressCounter == 8&& plasma_upgraded)
					{
						missileTimer = maxMissileTimer;
						missiles += 1;
						mis = SpriteManagerAdd(SPRITE_MISSILE, THIS->x-16, THIS->y);
						missileData = mis->custom_data;
						missileData->vx.w  = -300;						
						missileData->vy.w  = 0;
					}
				break;
				case 2:
					playerData-> vy.w +=  accel;
					
					if( missiles <  3 && pressCounter == 8&& plasma_upgraded)
					{
						missileTimer = maxMissileTimer;
						missiles += 1;
						mis = SpriteManagerAdd(SPRITE_MISSILE, THIS->x, THIS->y-8);
						missileData = mis->custom_data;
						missileData->vy.w  = -300;
						missileData->vx.w  = 0;
					}
				break;
				case 3:
					playerData-> vx.w -=  accel;	
					
					if( missiles <  3 && pressCounter == 8&& plasma_upgraded)
					{
						missileTimer = maxMissileTimer;
						missiles += 1;
						mis = SpriteManagerAdd(SPRITE_MISSILE, THIS->x+16, THIS->y);
						missileData = mis->custom_data;
						missileData->vx.w  = 300;
						missileData->vy.w  = 0;
					}
				break;
			}
		}
	}
	else
	{
		if(pressCounter > 6)
		{
			
		}
		else if(pressCounter > 0)
		{
			dir++;
			if(dir > 3)
			{
				dir = 0;
			}
		}
		pressCounter = 0;
	}
	
	playerData->tx.w += playerData->vx.w;
	tile_collision = TranslateSprite(THIS, playerData->tx.b.h,0	);
	if(tile_collision)
	{
		playerData->vx.w = -playerData->vx.w;
		playerData->vx.w = DispLeft(playerData->vx.w,1);
		CheckCollisionTile();
	}
	playerData->tx.b.h = 0;
	
	playerData->ty.w += playerData-> vy.w;
	tile_collision = TranslateSprite(THIS, 0,playerData->ty.b.h);
	if(tile_collision)
	{
		playerData->vy.w = -playerData->vy.w;
		playerData->vy.w = DispLeft(playerData->vy.w,1);
		CheckCollisionTile();
	}
	playerData->ty.b.h = 0;
	

	switch(dir)
	{
		case 0:		
			sprBooster-> x = THIS-> x-1;
			sprBooster-> y = THIS-> y + 15;
			if(pressCounter > 0)
			{
				SetSpriteAnim(sprBooster, anim_boost_down, 15);
			}
			else
			{
				SetSpriteAnim(sprBooster, anim_lowburn_down, 10);
			}
		break;
		case 1:
			sprBooster-> x = THIS-> x-16;			
			sprBooster-> y = THIS-> y ;
			if(pressCounter > 0)
			{
				SetSpriteAnim(sprBooster, anim_boost_left, 15);
			}
			else
			{
				SetSpriteAnim(sprBooster, anim_lowburn_left, 10);
			}
		break;
		case 2:
			sprBooster-> x = THIS-> x;
			sprBooster-> y = THIS-> y - 16;
			if(pressCounter > 0)
			{
				SetSpriteAnim(sprBooster, anim_boost_up, 15);
			}
			else
			{
				SetSpriteAnim(sprBooster, anim_lowburn_up, 10);
			}
		break;
		case 3:
		sprBooster-> x = THIS-> x+15;
			sprBooster-> y = THIS-> y;
			if(pressCounter > 0)
			{
				SetSpriteAnim(sprBooster, anim_boost_right, 15);
			}
			else
			{
				SetSpriteAnim(sprBooster, anim_lowburn_right, 10);
			}
		break;
	}
	
	if(missileTimer > 0)
	{
		missileTimer -= 1 << delta_time;
	}
	
	SPRITEMANAGER_ITERATE(i, spr)
	{
		if(spr->type == SPRITE_PLASMAUPGRADE)
		{				
			if(CheckCollision(THIS,spr))
			{				
				SpriteManagerAdd(SPRITE_EXPLOSION, spr->x, spr->y);
				plasma_upgraded = 1;			
				SpriteManagerRemove(i);
				show_win = 1;
				text_index = 1;
				game_paused = 1;
			}
		}
		else if(spr->type == SPRITE_ENEMY1)
		{
			if(CheckCollision(THIS,spr))
			{				
				SetState(STATE_MENU);
			}
		}
	}
}

void Destroy_SPRITE_PLAYER() 
{
	
}