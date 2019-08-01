#pragma bank=2
#include "SpriteExplosion.h"
#include "Keys.h"
#include "SpriteManager.h"
#include "ZGBMain.h"
#include "Print.h"

UINT8 bank_SPRITE_EXPLOSION = 2;

const UINT8 anim_explosion[] = {6, 0,1,2,3,4,4};


void Start_SPRITE_EXPLOSION() 
{
	SetSpriteAnim(THIS, anim_explosion, 15);
}

void Update_SPRITE_EXPLOSION() 
{
	if(THIS-> current_frame >= 5)
	{
		SpriteManagerRemove(THIS_IDX);
	}
	
}

void Destroy_SPRITE_EXPLOSION() 
{

}