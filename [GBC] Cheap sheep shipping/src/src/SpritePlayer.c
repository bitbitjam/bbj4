#pragma bank=2

#include "SpriteManager.h"
#include "Sprite.h"

#include "ZGBMain.h"

#include "SpritePlayer.h"
#include "SpriteFireA.h"
#include "SpriteSheep.h"
#include "Keys.h"
#include "Scroll.h"

#include "Tool.h"

#include "gbt_player.h"

#define COUNT_RALENTIZE 2 //default 5
#define COUNT_SAFEY 8 //frames / COUNT_RALENTIZE ... 7

#define DIFICULTAD 2 //2 FACIL 1 DIFICIL

INT8 HeliData_x_accel;
INT8 HeliData_y_accel;
INT8 HeliData_ralentize;
INT8 HeliData_button_turn;
INT8 HeliData_pressed;
INT8 HeliData_safeYCount;
INT8 HeliData_gravityEffect;
INT8 HeliData_tierraFirme;

INT8 HeliIsCrashed;
INT8 HeliX;
INT8 HeliY;
INT8 HeliWarn;
INT8 HeliDX;
INT8 HeliDY;

INT16 HeliLevelComplete;

extern INT16 AirportINIT;
extern INT16 AirportEND;
extern INT16 DropZoneINIT;
extern INT16 DropZoneEND;

struct Sprite* HeliPtr;

extern UINT8 SheepTaken;

UINT8 bank_SPRITE_PLAYER = 2;

const UINT8 anim_leftA[] = {2, 0, 4};
const UINT8 anim_rightA[] = {2, 3, 7};

struct Sprite* CurrentSheepSprite;

extern const UINT8 anim_sheepIDLE[];
extern const UINT8 anim_sheepDOWN[];
extern const UINT8 anim_sheepUP[];
extern const UINT8 anim_sheepLEFT[];
extern const UINT8 anim_sheepRIGHT[];

extern UINT8* crash_mod_Data[];
extern UINT8* idle_mod_Data[];
extern UINT8* running_mod_Data[];
extern UINT8* stall_mod_Data[];
extern UINT8* start_mod_Data[];
extern UINT8* stop_mod_Data[];

extern UINT8 CheapActualLevel;
extern UINT16 precont;

void Start_SPRITE_PLAYER() {
	
	struct HeliShareDataA* data = THIS->custom_data;
	HeliData_x_accel = 0;
	HeliData_y_accel = 0;
	HeliData_ralentize = 0;
	HeliData_button_turn = 0;
	HeliData_pressed = 0;
	
	HeliWarn = 0;
	HeliLevelComplete = 0;
	
	HeliData_safeYCount = 0;
	HeliData_gravityEffect = 1;
	
	HeliData_tierraFirme = 1;
	
	HeliIsCrashed = 0;
	HeliPtr = THIS;
	
	CurrentSheepSprite = 0;
	
	
	HeliX = THIS -> x;
	HeliY = THIS -> y;
	
	HeliDX = HeliX;
	HeliDY = HeliY;
	
	SetSpriteAnim(THIS, anim_leftA, 30); //velocidad en fps
	data ->dir = 0;
}

void Update_SPRITE_PLAYER() {
	INT8 negx = 0, negy = 0, i;
	unsigned  char actualTile;
	struct Sprite* spr;
	
	struct HeliShareDataA* data = THIS->custom_data;
	
	if (HeliIsCrashed == 0) {
		if(KEY_PRESSED(J_B)) {
		//si en el estado anterior estaba no presionado
		if (HeliData_pressed == 0) {
			HeliData_pressed = 1; //marcarlo como presionado
		}
		
		switch(HeliData_button_turn) {
			case 0:	//up
				if (HeliData_tierraFirme) PlayMusic(start_mod_Data, 4, 1);
				HeliData_safeYCount = 0;
				HeliData_gravityEffect = 1;
				if (HeliData_y_accel > -2) HeliData_y_accel --;
				HeliData_tierraFirme = 0;
				if (SheepTaken == 1) SetSpriteAnim(CurrentSheepSprite,anim_sheepUP, 15);
				break;
			case 1: //left
				if (!HeliData_tierraFirme) {
					if (HeliData_x_accel > -2) HeliData_x_accel --;
					SetSpriteAnim(THIS, anim_leftA, 30); //velocidad en fps
					data ->dir = 0;
				}
				if (SheepTaken == 1) SetSpriteAnim(CurrentSheepSprite,anim_sheepLEFT, 15);

				break;
			case 2: //up
				HeliData_safeYCount = 0;
				HeliData_gravityEffect = 1;
				if (HeliData_y_accel > -2) HeliData_y_accel --;
				if (SheepTaken == 1) SetSpriteAnim(CurrentSheepSprite,anim_sheepUP, 15);
				break;
			case 3: //right
				if (!HeliData_tierraFirme) {
					if (HeliData_x_accel < 2) HeliData_x_accel ++;
					SetSpriteAnim(THIS, anim_rightA, 30);
					data ->dir = 1;
				}
				if (SheepTaken == 1) SetSpriteAnim(CurrentSheepSprite,anim_sheepRIGHT, 15);
				break;
			default:
				break;
		}
		
	} else {
		//si en el estado anterior estaba presionado
		if (HeliData_pressed == 1) {
			HeliData_pressed = 0; //marcar como no presionado
			HeliData_button_turn ++; //siguiente boton
			if (HeliData_button_turn == 4) {
				HeliData_button_turn = 0;
			}
			
			switch(HeliData_button_turn ) {
				
				case 0:
					Cheap_drawUp();
					break;
				case 1:
					Cheap_drawLeft();
					break;
				case 2:
					Cheap_drawUp();
					break;
				case 3:
					Cheap_drawRight();
					break;
				default:
					break;

			}
		}
	}
	}
	
	HeliDX = HeliData_x_accel;
	HeliDY = HeliData_y_accel;
	
	if (HeliData_y_accel > DIFICULTAD && !HeliWarn && !HeliIsCrashed) {
		PlayMusic(stall_mod_Data, 4, 1);
		HeliWarn = 1;
	}
	
	if (HeliData_y_accel <= DIFICULTAD && HeliWarn && !HeliIsCrashed) {
		PlayMusic(running_mod_Data, 4, 1);
		HeliWarn = 0;
	}
		
	actualTile = TranslateSprite(THIS, HeliData_x_accel, HeliData_y_accel);
	//DPRINT_POS(0, 0);
	//DPrintf("CODIGO:%d                    ", HeliData_y_accel);
	//si topo con algo
	if (actualTile != 0) {
		
		//si el delta y es positivo se se estrella
		//si la velocidad vertical es de caida libre, se estrella
		if (HeliData_y_accel > DIFICULTAD || HeliDY < 0 ) {
				//crash!
				PlayMusic(crash_mod_Data, 4, 1);
				HeliIsCrashed = 1;
				HeliData_y_accel = 0;
				Cheap_drawCrash();
				if (CurrentSheepSprite) {
					SpriteManagerRemove(CurrentSheepSprite);
				}
				//SpriteManagerRemove(THIS);
		} else {
			//anular aceleracion porque estamos en suelo firme
			if (!HeliData_tierraFirme && !HeliIsCrashed) PlayMusic(stop_mod_Data, 4, 1);
			HeliData_safeYCount = 0;
			HeliData_gravityEffect = 1;
			HeliData_tierraFirme = 1;
			
			//cambiar el control hacia arriba (saltandose el actual), con direccion opuesta a la pared que choque.
			if (HeliDX < 0) {
				HeliData_button_turn = 2;
			} else {
				HeliData_button_turn = 0;
			}
			
			
			if (!HeliIsCrashed) Cheap_drawUp();
			
			//Si tengo oveja, dejarla alli
			if (SheepTaken == 1) {
				if (  (( THIS -> x)>> 3 ) >= DropZoneINIT  && ((THIS -> x) >> 3 ) <= DropZoneEND ) {
					SheepTaken = 2;
					CurrentSheepSprite -> y -=8;
					SetSpriteAnim(CurrentSheepSprite,anim_sheepIDLE, 15);
					//DPrintf("TOOK                   ");
				}

			}
			
			//si deje la oveja y estoy en la base
			if (SheepTaken == 2 && !HeliIsCrashed) {
				if ( ((THIS -> x) >> 3) >= AirportINIT && ((THIS -> x) >> 3)  <= AirportEND ) {
					Cheap_drawCongrats();
					CheapActualLevel++;
					HeliLevelComplete = 1;
					precont = 0;
					SetState(STATE_PRE);
				}

			}
		}
	}
	
	//ver colision con ovejas
	SPRITEMANAGER_ITERATE(i, spr) {
		if(spr->type == SPRITE_SHEEP) {
			if(CheckCollision(THIS, spr) && SheepTaken == 0) {
				//acoplar
				SheepTaken = 1;
				CurrentSheepSprite = spr;
			}
		}
	}
	
	HeliData_ralentize++;
	if (HeliData_ralentize == COUNT_RALENTIZE) {
		HeliData_ralentize = 0;
		
		//despues dividirlo en 2... siempre y cuando no sea 0
		if (HeliData_x_accel < 0 ) {
			negx = 1;
			HeliData_x_accel = - HeliData_x_accel;
		}
		HeliData_x_accel >>= 1;
		
		if (negx == 1) {
			HeliData_x_accel = - HeliData_x_accel;
		}
		
		//y tirar el y hacia abajo lo mas que se pueda!
		HeliData_safeYCount++;
		if ( HeliData_safeYCount > COUNT_SAFEY) {
			HeliData_safeYCount =0;
			HeliData_gravityEffect++;
		}
		if (HeliData_y_accel < HeliData_gravityEffect )HeliData_y_accel ++;		
	}
}

void Destroy_SPRITE_PLAYER() {
}