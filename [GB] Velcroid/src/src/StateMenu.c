#pragma bank=2
#include "StateGame.h"
UINT8 bank_STATE_MENU = 2;

#include "..\res\src\tiles.h"
#include "..\res\src\introtiles.h"
#include "..\res\src\bgmap.h"
#include "..\res\src\map.h"
#include "..\res\src\intromap.h"
#include "..\res\src\windowmap.h"

#include "ZGBMain.h"
#include "Scroll.h"
#include "SpriteManager.h"

#include "Keys.h"

#include "Print.h"
#include "../res/src/font.h"

extern UINT8 n_sprite_types;

const UINT8 menuItems = 1;
const UINT8 maxInputTimer = 20;

UINT8 text_index  = 0;
UINT8 selection = 0;
UINT8 winCounter = 0;
UINT8 plasma_upgraded = 0;

void ChangeSelection(INT8 s)
{
	PRINT_POS(2, 2);
	if(s == 0)
	{
		Printf("OPTION 1");
	}
	else
	{
		Printf("OPTION 2");
	}
}

 UINT8 entry_point;
 UINT8 next_room;
 UINT8 current_room;
 UINT8 game_paused;

void Start_STATE_MENU() 
{
	SPRITES_8x16;
	SHOW_SPRITES;
	
	entry_point = 2;
	current_room = 1;
	next_room = 0;
	game_paused = -1;
	
	InitScrollTiles(0, 120, introtiles, 3);
	InitScroll(intromapWidth, intromapHeight, intromap, 0, 0, 3);
	SHOW_BKG;	
	InitWindow(0,0,windowmapWidth,windowmapHeight,windowmap,3);
	SHOW_WIN;
	move_win(7, 200);
	winCounter = 12;
	text_index = 0;
	
	
	INIT_FONT(font, 3, PRINT_WIN);
	
	
	PRINT_POS(6, 2);
	Printf("PRESS A");
	INIT_FONT(font, 3, PRINT_BKG);
	PRINT_POS( 1, 10);
	Printf("LAUNCH SPACESHEEP");
	PRINT_POS(2, 1);
	Printf("MAIKEL ORTEGA'S");
	PRINT_POS(14, 7);
	Printf("2017");
}

void Update_STATE_MENU() 
{
	if(KEY_TICKED(J_B) )
	{
		if(selection < menuItems)
		{
			selection += 1;			
		}
		else
		{
			selection = 0;
			
		}
		move_win(7, 200);
		winCounter = 12;	
		ChangeSelection(selection);
	}
	
	if(KEY_TICKED(J_A) )
	{
		SetState(STATE_GAME);
		move_win(0,200);
	}
	
	if(winCounter > 0)
	{
		winCounter -= 1 << delta_time;
		move_win(7, 100+ winCounter*4);
	}
}


