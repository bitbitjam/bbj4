#pragma bank=2
#include "StateWin.h"
UINT8 bank_STATE_WIN = 2;

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

UINT8 txt_indx = 0;

void ClearText()
{
	
		PRINT_POS(0, 0);
		Printf("                     ");
		PRINT_POS(0, 1);
		Printf("                     ");
		PRINT_POS(0, 2);
		Printf("                     ");
		PRINT_POS(0, 3);
		Printf("                     ");
		PRINT_POS(0, 4);
		Printf("                     ");
		PRINT_POS(0, 5);
		Printf("                     ");
		PRINT_POS(0, 6);
		Printf("                     ");
		PRINT_POS(0, 7);
		Printf("                     ");
		PRINT_POS(0, 8);
		Printf("                     ");
		PRINT_POS(0, 9);
		Printf("                     ");
		PRINT_POS(0, 11);
		Printf("                     ");
		PRINT_POS(0, 12);
		Printf("                     ");
		PRINT_POS(0, 13);
		Printf("                     ");
		PRINT_POS(0, 14);
		Printf("                     ");
		PRINT_POS(0, 15);
		Printf("                     ");
		PRINT_POS(0, 16);
		Printf("                     ");
		PRINT_POS(0, 17);
		Printf("                     ");
		
}

void ShowText(UINT8 indx)
{
		PRINT_POS(2, 2);
		Printf("CONGRATULATIONS!");
		PRINT_POS(4, 3);
		Printf(" YOU COMPLETED ");
		
		PRINT_POS(3, 4);
		Printf("THE BITBITJAM4");
		
		PRINT_POS(7, 5);
		Printf("VERSION!");
		
		PRINT_POS(5, 8);
		Printf("07-07-2017");
		PRINT_POS(7, 9);
		Printf("VELCROID");
		PRINT_POS(9, 10);
		Printf("by");
		PRINT_POS(4, 11);
		Printf("MAIKEL ORTEGA");
		PRINT_POS(4, 13);
		Printf("POWERED BY:");
		PRINT_POS(4, 14);
		Printf("ZGB and GBDK");
}

void Start_STATE_WIN() 
{
	SPRITES_8x16;
	SHOW_SPRITES;

	SHOW_BKG;	

	InitWindow(0,0,windowmapWidth,windowmapHeight,windowmap,3);
	SHOW_WIN;
	move_win(0, 0);	
	INIT_FONT(font, 3, PRINT_WIN);
	
	ClearText();
	ShowText(0);
}



void Update_STATE_WIN() 
{
	if(KEY_TICKED(J_A) )
	{
		SetState(STATE_MENU);
	}
}


