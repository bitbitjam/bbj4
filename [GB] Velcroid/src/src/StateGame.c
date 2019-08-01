#pragma bank=2
#include "StateGame.h"
UINT8 bank_STATE_GAME = 2;

#include "..\res\src\tiles.h"
#include "..\res\src\map.h"
#include "..\res\src\room_01.h"
#include "..\res\src\room_02.h"
#include "..\res\src\room_03.h"
#include "..\res\src\gametextmap.h"

#include "ZGBMain.h"
#include "Scroll.h"
#include "SpriteManager.h"
#include "Keys.h"

#include "Print.h"
#include "../res/src/font.h"


UINT8 collision_tiles[] = {1,2,3,4,5,6,7,8,9,10,11,12,13,14,15,16,17,18,19,20,21,22,23,24,25,26,27,28,29,30,31,32,33,34,35,36,37,38,39,40,42,43,0};
UINT8 nextX;
UINT8 nextY;
extern UINT8 text_index ;
extern UINT8 winCounter;
UINT8 show_win;
UINT8 reading;

typedef struct RoomData
{
	UINT8* map;
	UINT16 mapW;
	UINT16 mapH;
	UINT16 door_t_x;
	UINT16 door_t_y;
	UINT8 door_t_map_id;
	UINT16 door_r_x;
	UINT16 door_r_y;
	UINT8 door_r_map_id;
	UINT16 door_d_x;
	UINT16 door_d_y;
	UINT8 door_d_map_id;
	UINT16 door_l_x;
	UINT16 door_l_y;
	UINT8 door_l_map_id;
};

const struct RoomData roomsDatas[] = 
{
	{map,mapWidth,mapHeight,			30,30,0u,		254,160,3u,			10<<3,20<<3,1u,		0,0,0u},
	{room_01,room_01Width,room_01Height,9<<3,2<<3,0u,	19<<3,11<<3,2u,		0,0,0u,				24,124,0u},
	{room_02,room_02Width,room_02Height,0,0,0u,			0,0,0u,				0,0,0u,				24,124,0u},
	{room_03,room_03Width,room_03Height,0,0,0u,			0,0,0u,				5<<3,19<<3,4u,		2<<3,5<<3,0u},
	{room_03,room_03Width,room_03Height,0,0,0u,			0,0,0u,				5<<3,19<<3,4u,		2<<3,5<<3,0u},
};

extern UINT8 n_sprite_types;
extern UINT8 next_room;
extern UINT8 current_room;
extern UINT8 entry_point;
extern UINT8 game_paused;
extern UINT8 plasma_upgraded;

void GetEntryPoint()
{	
	switch(entry_point)
	{	
		case 0:
			next_room = roomsDatas[current_room].door_t_map_id;			
			nextX = roomsDatas[next_room].door_d_x;
			nextY = roomsDatas[next_room].door_d_y;
		break;
		case 1:
			next_room = roomsDatas[current_room].door_r_map_id;
			nextX = roomsDatas[next_room].door_l_x;
			nextY = roomsDatas[next_room].door_l_y;
		break;
		case 2:
			next_room = roomsDatas[current_room].door_d_map_id;
			nextX = roomsDatas[next_room].door_t_x;
			nextY = roomsDatas[next_room].door_t_y;
		break;
		case 3:
			next_room = roomsDatas[current_room].door_l_map_id;
			nextX = roomsDatas[next_room].door_r_x;
			nextY = roomsDatas[next_room].door_r_y;
		break;
	}
}

void InstantiateUniqueSprites()
{
	struct Sprite* s;
	switch(next_room)
	{
		case 2:
		if(!plasma_upgraded)
		{
			s = SpriteManagerAdd(SPRITE_PLASMAUPGRADE, 22<<3,13<<3);
		}
		break;
	}
}

void Start_STATE_GAME() 
{
	UINT8 i;
	SPRITES_8x16;
	
	//BGP_REG = (0x03u << 4 << 2)|(0x03u<< 4)|(0x03u << 2)| (0x03u);
	//OBP0_REG = (0x01u << 4 << 2)|(0x02u<< 4)|(0x03u << 2)| (0x00u);
	//OBP1_REG = (0x03u << 4 << 2)|(0x03<< 4)|(0x03u << 2)| (0x03u);	
	
	
	for(i = 0; i != n_sprite_types; ++ i) {
		SpriteManagerLoad(i);
	}
	
	GetEntryPoint();	
	
	if(next_room == 4)
	{
		SetState(STATE_WIN);
		return;
	}
	
	
	scroll_target = SpriteManagerAdd(SPRITE_PLAYER, nextX, nextY);
	scroll_target->flags= S_PALETTE;
	
	SHOW_SPRITES;
	
	InitScrollTiles(0, 44, tiles, 3);
	InitScroll(roomsDatas[next_room].mapW, roomsDatas[next_room].mapH, roomsDatas[next_room].map, collision_tiles, 0, 3);
	
	InstantiateUniqueSprites();
	
	SHOW_BKG;
	
	InitWindow(0,0,gametextmapWidth,gametextmapHeight,gametextmap,3);	
	move_win(7, 140 );
	SHOW_WIN;
	INIT_CONSOLE(font, 3, 2);
	
	current_room = next_room;
}


void Update_STATE_GAME() 
{
	if(game_paused == 1 && show_win && !reading)
	{
		reading = 1;
		winCounter = 10;
		INIT_FONT(font, 3, PRINT_WIN);			
		
		switch(text_index)
		{
			case 0:
				PRINT_POS(1, 1);
				Printf("     Welcome");
				PRINT_POS(1, 3);
				Printf(" to Bleatstar   ");
			break;
			case 1:
				PRINT_POS(1, 1);
				
				Printf("  Plasma Blaaster  ");
				PRINT_POS(1, 3);
				Printf("    UNLOCKED");
			break;
			case 2:
				PRINT_POS(1, 1);
				Printf("BAAAA             ");
				PRINT_POS(1, 3);
				Printf("                  ");
			break;
		}	
	}
	
	if(game_paused == 1 && KEY_TICKED(J_A) )
	{
		show_win = 0;
		winCounter = 10;
		game_paused = -game_paused;
		reading = 0;
	}

	if(winCounter > 0)
	{
		winCounter -= 1;
		if(show_win)
		{			
			move_win(7, 100+ winCounter*4);
		}
		else
		{				
			move_win(7, 140 - winCounter*4);
		}
	}
}