#pragma bank=2
#include "StateGame.h"
UINT8 bank_STATE_STORY = 2;

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
	switch(indx)
	{
		case 0:
			
			PRINT_POS(3, 2);
			Printf("YEAR IS 20X7");
			PRINT_POS(1, 5);
			Printf("THE MUTANT ENTITY");
			PRINT_POS(3, 6);
			Printf("WITH CODENAME: ");
			PRINT_POS(3, 8);
			Printf("(mother sheep)");
			PRINT_POS(1, 10);
			Printf("released a velcro-");
			PRINT_POS(1, 11);
			Printf("based bio-weapon");
			PRINT_POS(1, 12);
			Printf("on the surface of");
			PRINT_POS(1, 13);
			Printf(" PLANET ZEH-BAA.");
			PRINT_POS(6, 17);
			Printf("PRESS A");
		break;
		case 1:
		
		PRINT_POS(5, 2);
		Printf("YOU ARE   ");
		PRINT_POS(8, 3);
		Printf("A");
		PRINT_POS(4, 4);
		Printf("SPACESHEEP   ");
		PRINT_POS(0, 6);
		Printf("THE BEST OF THE BEST");
		PRINT_POS(0, 7);
		Printf("TRAINED FOR YEARS IN");
		PRINT_POS(0, 8);
		Printf("ZERO-GRAV MANEUVERS.");
		PRINT_POS(0, 10);
		Printf("INMUNE TO VELCRO AND");
		PRINT_POS(0, 11);
		Printf("A MASTER OF SHEEP-FU.");
		
		PRINT_POS(6, 17);
		Printf("PRESS A");
		break;
		
		case 2:
		
		PRINT_POS(1, 2);
		Printf("ONLY YOU CAN SAVE ");
		PRINT_POS(1, 3);
		Printf(" THE GALAXY FROM ");
		
		PRINT_POS(2, 4);
		Printf("THE MENACE  OF");
		
		PRINT_POS(2, 5);
		Printf("THAT BIO-WEAPON.");
		
		
		PRINT_POS(0, 10);
		Printf("FROM THE MENACE...  ");
		PRINT_POS(4, 12);
		Printf("OF...");
		PRINT_POS(6, 14);
		Printf("THE...");
		
		PRINT_POS(6, 17);
		Printf("PRESS A");
		break;
	}
	
	
}

void Start_STATE_STORY() 
{
	SPRITES_8x16;
	SHOW_SPRITES;

	SHOW_BKG;	

	InitWindow(0,0,windowmapWidth,windowmapHeight,windowmap,3);
	SHOW_WIN;

	
	
	INIT_FONT(font, 3, PRINT_WIN);
	
	ShowText(0);
}



void Update_STATE_STORY() 
{
	if(KEY_TICKED(J_A) )
	{
		if(txt_indx >1)
		{
			SetState(STATE_MENU);
		}
		txt_indx++;
		ClearText();
		ShowText(txt_indx);
	}
}


