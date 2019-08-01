#include "ZGBMain.h"

UINT8 GetTileReplacement(UINT8* tile_ptr, UINT8* tile) {
	
	//*tile = 1;
	//return 255u;
	/*if(current_state == STATE_GAME) {
		if(U_LESS_THAN(255 - (UINT16)*tile_ptr, N_SPRITE_TYPES)) {
			*tile = 0;
			return 255 - (UINT16)*tile_ptr;
		}

		*tile = *tile_ptr;
	}

	return 255u;*/
	
	if(current_state == STATE_GAME) {
		*tile = 1; //dejar cielo
		switch(*tile_ptr) {
			//case 86: return SPRITE_PLAYER;
			case 45: return SPRITE_SHEEP;
			//limpieza de tiles key
			case 44: return 255u;
			case 49: return 255u;
			case 50: return 255u;
			case 51: return 255u;
			case 52: return 255u;
		}
		//aplicar el tile
		*tile = *tile_ptr;
				
	}
	
	return 255u;
}