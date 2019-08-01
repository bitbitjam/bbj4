#pragma bank=2
#include "SpritePlasmaUpgrade.h"
#include "Keys.h"
#include "SpriteManager.h"
#include "ZGBMain.h"
#include "Print.h"

UINT8 bank_SPRITE_PLASMAUPGRADE = 2;

const UINT8 anim_plasma[] = {2, 0,1};


void Start_SPRITE_PLASMAUPGRADE() 
{
	SetSpriteAnim(THIS, anim_plasma, 7);
}

void Update_SPRITE_PLASMAUPGRADE() 
{
	
	
}

void Destroy_SPRITE_PLASMAUPGRADE() 
{

}