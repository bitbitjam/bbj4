#pragma bank=2
#include "SpriteTarget.h"
#include "Keys.h"
#include "SpriteManager.h"
#include "ZGBMain.h"
#include "Print.h"

UINT8 bank_SPRITE_TARGET = 2;

const UINT8 anim_target[] = {3, 0,0,1};


void Start_SPRITE_TARGET() 
{
	SetSpriteAnim(THIS, anim_target, 15);
}

void Update_SPRITE_TARGET() 
{
	
	
}

void Destroy_SPRITE_TARGET() 
{

}