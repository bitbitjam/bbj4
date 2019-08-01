//-----------------------------LICENSE NOTICE------------------------------------
//  This file is part of CPCtelera: An Amstrad CPC Game Engine
//  Copyright (C) 2015 ronaldo / Fremos / Cheesetea / ByteRealms (@FranGallegoBR)
//
//  This program is free software: you can redistribute it and/or modify
//  it under the terms of the GNU Lesser General Public License as published by
//  the Free Software Foundation, either version 3 of the License, or
//  (at your option) any later version.
//
//  This program is distributed in the hope that it will be useful,
//  but WITHOUT ANY WARRANTY; without even the implied warranty of
//  MERCHANTABILITY or FITNESS FOR A PARTICULAR PURPOSE.  See the
//  GNU Lesser General Public License for more details.
//
//  You should have received a copy of the GNU Lesser General Public License
//  along with this program.  If not, see <http://www.gnu.org/licenses/>.
//------------------------------------------------------------------------------

#include <stdio.h>
#include <cpctelera.h>
#include "tiles.h"  
#include "pant1.h"
#include "pant2.h"
#include "pant3.h"
#include "pant4.h"
#include "pant5.h"
#include "pant6.h" 
#include "prota.h"
#include "frame_arriba.h" 
#include "frame_abajo.h"
#include "coin.h"



__at(0x200) const unsigned char G_song[641];

#define SI 1
#define NO 0

#define ANCHO  80
#define ALTO  160

#define ANCHOPROTA   (16/2)
#define ALTOPROTA    19

#define ORIGEN_MAPA_Y   32
#define ORIGEN_MAPA     cpctm_screenPtr(CPCT_VMEM_START, 0, ORIGEN_MAPA_Y)

typedef struct {
   u8  mira;
   u8* sprite;
} TFrame;

typedef struct {
   u8 x, y;
   u8 px, py;
   u8 mover;
   u8 estado;
   u8* sprite;
   u8 mira;
   u8 salto;
} TProta;

// Mirando hacia
enum {
      M_derecha   = 0
   ,  M_izquierda
} EMirar;

// pantallas de juego
enum {
    PT_menu  = 0
   ,  PT_juego
   ,  PT_ganador
} EEventos;


// Eventos del personaje
enum {
      EV_detenerse = 0
   ,  EV_moverse
   ,  EV_saltar
   ,  EV_numEventos
} EEventos;

// Estados del personaje
enum {
      ST_quieto  = 0
   ,  ST_andando
   ,  ST_prepSalto
   ,  ST_saltando
   ,  ST_cayendo
   ,  ST_aterrizando
   ,  ST_numEstados
} EEstados;

// Mapas
#define NUM_MAPAS 9
u8* const mapas[NUM_MAPAS] = { g_map1, g_map1, g_map2, g_map3, g_map1, g_map4, g_map5, g_map5, g_map6 };

//Posiciones monedas
u8 const moneda_x[NUM_MAPAS] = { 45 , 25, 50, 50, 40, 40, 40, 50, 55 }; 
u8 const moneda_y[NUM_MAPAS] = { 42 , 42,  42, 42, 35, 52, 52, 45, 35 };


// Control de salto
#define PASOS_SALTO  20
const CPCT_2BITARRAY(g_tablaSalto, PASOS_SALTO) = {
     CPCT_ENCODE2BITS(3, 3, 3, 3) 
   , CPCT_ENCODE2BITS(3, 3, 2, 2)
   , CPCT_ENCODE2BITS(2, 2, 2, 1)
   , CPCT_ENCODE2BITS(1, 1, 1, 1)
   , CPCT_ENCODE2BITS(1, 0, 0, 0)
};

// Máscara de transparencia
cpctm_createTransparentMaskTable(g_tablatrans, 0x100, M0, 0);

u8* mapa;
u8  num_mapa;
TProta prota;
u8 estado_juego;
u8 puntos;
u8 cambioPuntos;
u8 coinCogida;

void playmusic() {
   __asm 
      exx
      .db #0x08
      push af
      push bc
      push de
      push hl
      call _cpct_akp_musicPlay
      pop hl
      pop de
      pop bc
      pop af
      .db #0x08
      exx
   __endasm;
}

u8 colisionConProta(u8 coinx, u8 coiny, u8 coinw,u8 coinh )
{
	if ( prota.x > coinx+coinw || prota.y > coiny + coinh || prota.x + G_PROTA_W < coinx || prota.y + G_PROTA_H < coiny )
	{
		return 0;
	}
	else
	{
		return 1;
	}

}

void interrupcion() {
   static u8 kk;

   if (++kk == 5) {
      playmusic();
      cpct_scanKeyboard_if();
      kk = 0;
   }
}

void dibujarMapa() {
   cpct_etm_drawTilemap2x4(g_map1_W, g_map1_H, ORIGEN_MAPA, mapa);
    dibujarCoin();
}

void dibujarCoin() {
   u8* pvmem = cpct_getScreenPtr(CPCT_VMEM_START, moneda_x[num_mapa], moneda_y[num_mapa]);
   cpct_drawSprite(g_coin, pvmem, G_COIN_W, G_COIN_H);
}

void dibujarProta() {
   u8* pvmem = cpct_getScreenPtr(CPCT_VMEM_START, prota.x, prota.y);
   cpct_drawSpriteMaskedAlignedTable(prota.sprite, pvmem, G_PROTA_W, G_PROTA_H, g_tablatrans);
}

void borrarProta() {
   u8 w = 4 + (prota.px & 1);
   u8 h = 7 + (prota.py & 3 ? 1 : 0);
   cpct_etm_drawTileBox2x4(prota.px / 2, (prota.py-ORIGEN_MAPA_Y) / 4, w, h, 40, ORIGEN_MAPA, mapa);
}

void borrarCoin() {
   u8 w = 4 + (moneda_x[num_mapa] & 1);
   u8 h = 7 + (moneda_y[num_mapa] & 3 ? 1 : 0);
   cpct_etm_drawTileBox2x4(moneda_x[num_mapa] / 2, (moneda_y[num_mapa]-ORIGEN_MAPA_Y) / 4, w, h, 40, ORIGEN_MAPA, mapa);
}

u8* obtenerTilePtr(u8 x, u8 y) {
   return mapa + (y-ORIGEN_MAPA_Y)/4*g_map1_W + x/2;
}

void ajustarAlSuelo() {
   prota.y = (prota.y & 0b11111100) + 1;
}

u8 sobreSuelo() {
   u8* tileSuelo = obtenerTilePtr(prota.x+2, prota.y + ALTOPROTA+1);
   if ( ( *tileSuelo > 19 && *tileSuelo < 24  ) || ( *(tileSuelo+G_PROTA_W/2-3) > 19 && *(tileSuelo+G_PROTA_W/2-3) < 24) )
      return 1;

   return 0;
}

void avanzarMapa() {
   if (num_mapa < NUM_MAPAS-1) {
      mapa = mapas[++num_mapa];
      prota.x = prota.px = 0;
      prota.mover = SI;
      coinCogida=NO;
      dibujarMapa();
      //cpct_drawStringM0("no final",cpctm_screenPtr(CPCT_VMEM_START, 10, 10),14,0);
   }
   else
   {
   		//cpct_drawStringM0("final",cpctm_screenPtr(CPCT_VMEM_START, 10, 10),14,0);	
   		irGanador();
   		estado_juego = PT_ganador;
   }
}

void retrocederMapa() {
   if (num_mapa > 0) {
      mapa = mapas[--num_mapa];
      prota.x = prota.px = ANCHO - G_PROTA_W;
      prota.mover = SI;
      dibujarMapa();
   }
}

void moverDerecha() { 
   if (prota.x + G_PROTA_W < ANCHO) {
      prota.x++;
   } else {
      avanzarMapa();
   }
}

void moverIzquierda() {
   if (prota.x > 0) {
      prota.x--;
   } else {
      retrocederMapa();
   }
}

void redibujarProta() {
   borrarProta();
   prota.px = prota.x;
   prota.py = prota.y;
   dibujarProta();
}

u8 compruebaTeclas(const cpct_keyID* k, u8 numk) {
   u8 i;
//   cpct_scanKeyboard_if();
   if (cpct_isAnyKeyPressed()) {
      for(i=1; i <= numk; i++, k++) {
         if (cpct_isKeyPressed(*k))
            return i;
      }
   }
   return 0;
}

void quieto_entrar();

void aterrizando_entrar() {
   prota.estado = ST_aterrizando;
   prota.mover  = SI;
}

void aterrizando() {
   prota.mover = SI;    
    quieto_entrar();
}

void cayendo_entrar() {
   prota.estado = ST_cayendo;
   prota.mover  = SI;
   prota.salto  = PASOS_SALTO - 3;
}

void descender() {
   prota.y += cpct_get2Bits(g_tablaSalto, prota.salto);
   if (prota.salto > 1)
      prota.salto--;
}

void cayendo() {
   if (colisionConProta(moneda_x[num_mapa], moneda_y[num_mapa], 8,16 ) && !coinCogida)
	{
		borrarCoin();
		cambioPuntos=SI;
		puntos++;
		//cpct_drawStringM0("col",cpctm_screenPtr(CPCT_VMEM_START, 16, 100),14,0);	
		coinCogida=SI;
	}
   descender();
   if (sobreSuelo()) {
      ajustarAlSuelo();
      aterrizando_entrar();
   }
   prota.mover=SI;
}

void quieto_entrar() {
   prota.estado = ST_quieto;
   prota.mover  = SI;
}

void andando_entrar(u8 mirar);
void prepSalto_entrar();

void quieto() {
   static const cpct_keyID keys[3] = {Key_CursorUp};
   u8 k = compruebaTeclas(keys, 3);
   switch(k) {
      case 0: break; // Nada que hacer
      case 1: saltando_entrar(); break;
   }
}

void ascender() {
   prota.y -= cpct_get2Bits(g_tablaSalto, prota.salto);
   if (prota.y < ORIGEN_MAPA_Y)
      prota.y = ORIGEN_MAPA_Y;
   if (++prota.salto == PASOS_SALTO)
      cayendo_entrar();
}

void saltando_entrar() {
   prota.estado = ST_saltando;
   prota.mover  = SI;
   prota.salto  = 0;
}

void saltando() {
	if (colisionConProta(moneda_x[num_mapa], moneda_y[num_mapa], 8,16 ) && !coinCogida)
	{
		borrarCoin();
		cambioPuntos=SI;
		puntos++;
		//cpct_drawStringM0("col",cpctm_screenPtr(CPCT_VMEM_START, 16, 100),14,0);	
		coinCogida=SI;
	}
   if (!cpct_isKeyPressed(Key_CursorUp)) {
      cayendo_entrar();
   } else {
      /*static const cpct_keyID keys[2] = {Key_CursorRight, Key_CursorLeft};
      u8 k = compruebaTeclas(keys, 2);
      switch(k) {
         case 0: break;
         case 1: moverDerecha();   break;
         case 2: moverIzquierda(); break;
      }*/
      ascender();
      prota.mover = SI;
   }
}


void prepSalto_entrar() {
   
   prota.estado = ST_prepSalto;
   prota.mover  = SI;
}

void prepSalto_animar() {
      saltando_entrar();
}

void prepSalto() {
   static const cpct_keyID keys[1] = {Key_CursorUp};
   u8 k = compruebaTeclas(keys, 1);
   switch(k) {
      case 0: quieto_entrar(); break; 
      case 1: prepSalto_animar(); break;
   }
   prota.mover = SI;
}

void andando_entrar(u8 mirar) {
   prota.estado = ST_andando;
   prota.mira   = mirar;
   prota.mover  = SI;
}

void andando_animar(u8 mirar) {
   prota.mira  = mirar;
}

void andando() {
   static const cpct_keyID keys[3] = {Key_CursorUp};
   u8 k = compruebaTeclas(keys, 3);
   switch(k) {
      case 0: andando_entrar();    break;
      case 1: prepSalto_entrar(); break;
   }
   prota.mover = SI;
   if (!sobreSuelo())
      cayendo_entrar();
}

void ejecutarEstado() {
   switch(prota.estado) {
      case ST_quieto:      andando();      break;
      case ST_andando:     andando();     break;
      case ST_prepSalto:   prepSalto();   break;
      case ST_saltando:    saltando();    break;
      case ST_cayendo:     cayendo();     break;
      case ST_aterrizando: aterrizando(); break;
   }
}

void resetTeclas()
{
static const cpct_keyID keys[1] = {Key_CursorUp};
   u8 k = compruebaTeclas(keys, 1); 

}

void inicializar() {
   cpct_disableFirmware();
   cpct_setVideoMode(0); 
   cpct_setPalette(g_palette, 16);
   cpct_setBorder(HW_BLACK);
   cpct_etm_setTileset2x4(g_tileset);
   estado_juego=PT_menu;
   cambioPuntos=SI;
   //resetTeclas();
   cpct_akp_musicInit(G_song);
   resetJuego();
   /*cpct_drawSprite(g_frame_arriba_0, cpctm_screenPtr(CPCT_VMEM_START,  0	, 0), G_FRAME_ARRIBA_0_W, G_FRAME_ARRIBA_0_H);
   cpct_drawSprite(g_frame_arriba_1, cpctm_screenPtr(CPCT_VMEM_START,  40	, 0), G_FRAME_ARRIBA_0_W, G_FRAME_ARRIBA_0_H);
 
   //cpct_drawSprite(g_frame_abajo_0, cpctm_screenPtr(CPCT_VMEM_START, 0, 144), G_FRAME_ABAJO_0_W, G_FRAME_ABAJO_0_H);
   //cpct_drawSprite(g_frame_abajo_1, cpctm_screenPtr(CPCT_VMEM_START, 40, 144), G_FRAME_ABAJO_0_W, G_FRAME_ABAJO_0_H);

   //cpct_drawStringM0("0000",cpctm_screenPtr(CPCT_VMEM_START, 17, 178),14,0);
   mapa = g_map1; 
   num_mapa = 0;
   prota.x = prota.px = 5;
   prota.y = prota.py = 45;
  
   prota.sprite  = g_prota;
   dibujarMapa();
   dibujarProta();
   cpct_akp_musicInit(G_song);
   cpct_setInterruptHandler(interrupcion);
   estado_juego=PT_menu;*/
}

void irMenu()
{
	estado_juego=PT_menu;
	cpct_clearScreen_f64(cpct_px2byteM0(0,0));
	cpct_drawSprite(g_frame_arriba_0, cpctm_screenPtr(CPCT_VMEM_START,  0	, 0), G_FRAME_ARRIBA_0_W, G_FRAME_ARRIBA_0_H);
   cpct_drawSprite(g_frame_arriba_1, cpctm_screenPtr(CPCT_VMEM_START,  40	, 0), G_FRAME_ARRIBA_0_W, G_FRAME_ARRIBA_0_H);
 
  

   //cpct_drawStringM0("0000",cpctm_screenPtr(CPCT_VMEM_START, 17, 178),14,0);	
    mapa = g_map1; 
   num_mapa = 0;
   prota.x = prota.px = 5;
   prota.y = prota.py = 45;
   prota.estado = ST_quieto;
   prota.mira   = M_derecha;
   prota.mover  = NO;
   prota.sprite  = g_prota;
   dibujarMapa();
   dibujarProta();
   //cpct_akp_musicInit(G_song);
   cpct_drawStringM0("Press UP key",cpctm_screenPtr(CPCT_VMEM_START, 16, 75),14,0);	
   cpct_drawStringM0("Code + GFX",cpctm_screenPtr(CPCT_VMEM_START, 20, 160),14,0);	
   cpct_drawStringM0("by @Pixelartm",cpctm_screenPtr(CPCT_VMEM_START, 16, 170),14,0);	
   cpct_drawStringM0("Music by MCklain",cpctm_screenPtr(CPCT_VMEM_START, 10, 180),14,0);	

   //cpct_akp_musicInit(G_song);
   cpct_setInterruptHandler(interrupcion);

}

void irGanador()
{
	estado_juego=PT_ganador;
	cpct_clearScreen_f64(cpct_px2byteM0(0,0));
	cpct_drawSprite(g_frame_arriba_0, cpctm_screenPtr(CPCT_VMEM_START,  0	, 0), G_FRAME_ARRIBA_0_W, G_FRAME_ARRIBA_0_H);
   cpct_drawSprite(g_frame_arriba_1, cpctm_screenPtr(CPCT_VMEM_START,  40	, 0), G_FRAME_ARRIBA_0_W, G_FRAME_ARRIBA_0_H);
 
  

   
   prota.x = prota.px = 35;
   prota.y = prota.py = 50;
   prota.estado = ST_quieto;
   prota.mira   = M_derecha;
   prota.mover  = NO;
   prota.sprite  = g_prota;
   dibujarProta();
   //cpct_akp_musicInit(G_song);
   cpct_drawStringM0("Well done Velcro!",cpctm_screenPtr(CPCT_VMEM_START, 5, 100),14,0);	
   //cpct_drawStringM0("Code + GFX",cpctm_screenPtr(CPCT_VMEM_START, 20, 160),14,0);	
   //cpct_drawStringM0("by @Pixelartm",cpctm_screenPtr(CPCT_VMEM_START, 16, 170),14,0);	

   //cpct_akp_musicInit(G_song);
   cpct_setInterruptHandler(interrupcion);

}

void resetJuego()
{
   cpct_drawSprite(g_frame_arriba_0, cpctm_screenPtr(CPCT_VMEM_START,  0	, 0), G_FRAME_ARRIBA_0_W, G_FRAME_ARRIBA_0_H);
   cpct_drawSprite(g_frame_arriba_1, cpctm_screenPtr(CPCT_VMEM_START,  40	, 0), G_FRAME_ARRIBA_0_W, G_FRAME_ARRIBA_0_H);
 
   cpct_drawSprite(g_frame_abajo_0, cpctm_screenPtr(CPCT_VMEM_START, 0, 144), G_FRAME_ABAJO_0_W, G_FRAME_ABAJO_0_H);
   cpct_drawSprite(g_frame_abajo_1, cpctm_screenPtr(CPCT_VMEM_START, 40, 144), G_FRAME_ABAJO_0_W, G_FRAME_ABAJO_0_H);

   //cpct_drawStringM0("   0",cpctm_screenPtr(CPCT_VMEM_START, 17, 178),14,0);	
   cambioPuntos=SI;
   puntos=0;
   mapa = g_map1; 
   num_mapa = 0	;
   prota.x = prota.px = 5;
   prota.y = prota.py = 45;
   prota.estado = ST_cayendo;
   prota.mira   = M_derecha;
   prota.mover  = SI;
   prota.sprite  = g_prota;
   coinCogida = NO;
   dibujarMapa();
   dibujarProta();
   //cpct_akp_musicInit(G_song);
   cpct_setInterruptHandler(interrupcion);

}

void comprobarTeclaArriba()
{
   static const cpct_keyID keys[3] = {Key_CursorUp};
   u8 k = compruebaTeclas(keys, 3);
   if ( k == 1)
   {
      	estado_juego=PT_juego; 
      	resetJuego(); 
     
   }
}

void comprobarTeclaArribaGO()
{
   static const cpct_keyID keys[3] = {Key_CursorUp};
   u8 k = compruebaTeclas(keys, 3);
   if ( k == 1)
   {
      	estado_juego=PT_menu; 
      	irMenu(); 
     
   }
}




void main(void) {
	u8 str[6];
	u8 cont = 0;
   inicializar();

   // Loop forever
   while (1) {
   	  
   	  switch(estado_juego) {
   	 	 case PT_juego:

		      ejecutarEstado();

		      if(prota.y > 125)
		      {
		      	//resetJuego();
		      	irMenu();
		      }
		      
		      if (cambioPuntos)
		      {
		      	sprintf(str,"%5u",puntos);
		      	cpct_drawStringM0(str,cpctm_screenPtr(CPCT_VMEM_START, 17, 178),14,0);
		      	cambioPuntos=NO;
		      }
		      

		      if (prota.mover) {
		         cpct_waitVSYNC();
		         redibujarProta();
		         prota.mover = SI;
		         if (cont > 0){
		         	moverDerecha();
		         	cont=0;
		         }
		         else
		         {
		         	cont++;
		         }
		      }
		      break;
      	case PT_menu:
      		comprobarTeclaArriba();
      		break;
     	case PT_ganador:
     		comprobarTeclaArribaGO();
     		break;
    } 
   }
}
