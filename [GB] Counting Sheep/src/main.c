// CABBAGE 2017

#include <gb/gb.h>

#include "sndsys.c"
extern const unsigned char popcorn[];
extern const unsigned char loser[];
extern const unsigned char twinkle_twinkle[];


#include "gfx/map_gameover.c"
#include "gfx/tilemap1.c"
#include "gfx/map_titlescreen.c"
#include "gfx/gfx_tileset.c"
#include "gfx/gfx_sheep.c"

unsigned char foo,bar;
unsigned int i,j;
unsigned int joy0,lastjoy0;
unsigned char tick;
unsigned char buf[16];

#define ASPR	1
#define ATILE	6
#define SSPR	0
#define STILE	1
#define FIX	8
unsigned char xx,yy;
unsigned int x,y;
unsigned int vx=0,vy=0;
unsigned char ang=0;
unsigned char tile;
unsigned char walk_spd=128;
unsigned char anim_t=0;
#define DEL_WALK	12
#define DEL_JUMP	8

int ang_v=1;

unsigned char s_n=8,s_min=8,s_max=40;

unsigned char hp,max_hp=3;

#define WALK	0
#define JUMP	1
#define WALKOFF	2
#define GAMEOVER	255
unsigned char state=0;

unsigned char YY_START;
#define X_START	(248<<FIX)
#define Y_START ((unsigned int)YY_START<<FIX)

#define DIGTILE	6
unsigned int score;
unsigned int hiscore[3];

#define M_EASY	0
#define M_NORMAL	1
#define M_HARD	2
unsigned char game_mode;

const unsigned char sin[]={0, 0, 5, 10, 15, 20, 25, 30, 35, 40, 45, 49, 54, 59, 64, 69, 74, 79, 83, 88, 93, 97, 102, 107, 111, 116, 120, 125, 129, 133, 138, 142, 146, 150, 154, 158, 162, 166, 170, 173, 177, 181, 184, 187, 191, 194, 197, 201, 204, 207, 210, 212, 215, 218, 220, 223, 225, 228, 230, 232, 234, 236, 238, 240, 241, 243, 244, 246, 247, 248, 250, 251, 252, 252, 253, 254, 254, 255, 255, 255};
const unsigned char cos[]={255, 255, 255, 255, 254, 254, 253, 252, 252, 251, 250, 248, 247, 246, 244, 243, 241, 240, 238, 236, 234, 232, 230, 228, 225, 223, 220, 218, 215, 212, 210, 207, 204, 201, 197, 194, 191, 187, 184, 181, 177, 173, 170, 166, 162, 158, 154, 150, 146, 142, 138, 133, 129, 125, 120, 116, 111, 107, 102, 97, 93, 88, 83, 79, 74, 69, 64, 59, 54, 49, 45, 40, 35, 30, 25, 20, 15, 10, 5, 0};
const unsigned char TILE_TYPE[]={0,0,0,0,1,1,0,0,0,0,0,0,0,0,0,0,0,0,0,0,0,0,0,0,0,0,0,0,0,0,0,0,0,0,0,0,0,0,0,0,0,0,0,0,0,0,0,0,0,0,0,0,0,0,0,0,0,0,0,0,0,0,0,0,0,0,0,0,0,0,0,0,0,0,0,0,0,0,0,0,1,1,1,1,1,1,1,1,1,1,1,1,1,1,1,1,0,0,0,0,0,0,0,0,0,0,0,0,0,0,0,0,0,0,0,0,0,0,0,0,0,0,0,0,0,0,0,0,};
const unsigned char map_digits[]={6,7,8,9,10,11,12,13,14,15,16,17,18,19,20,21,22,23,24,25,3,3};
#define G	16

unsigned char map_awake[]={199,200,201,190,};
unsigned char map_zz[]={
	196,2,2, 2,197,198,
	196,2,2, 2,197,2,
	196,2,2, 2,2,2,
	2,2,2, 2,2,2,
	2,2,2, 2,2,198,
	2,2,2, 2,197,198,	
};

unsigned char zzt,zzf;
void zz_anim(){
	zzt++;
	if(zzt%32==0){
		zzf++;
		if(zzf==6)zzf=0;
		set_bkg_tiles(13,14,3,2,&map_zz[zzf*6]);
	}
}
void wake_up(){
	set_bkg_tiles(13,14,3,2,&map_zz[18]);
	set_bkg_tiles(18,15,2,2,&map_awake);
}
unsigned char map_brdr1[]={
	45,47,45,47,45,47,45,47,45,47,
	45,47,45,47,45,47,45,47,45,47,45,
};
unsigned char map_brdr2[]={
	40,42,40,42,40,42,40,42,40,42,
	40,42,40,42,40,42,40,42,40,42,40,
};
unsigned char brdr_t;
#define D_BRDR	120
void brdr_anim(){
	brdr_t++;
	if(brdr_t==D_BRDR*2){
		set_bkg_tiles(0,0,20,1,&map_brdr1[0]);
		set_bkg_tiles(0,13,20,1,&map_brdr2[0]);
		brdr_t=0;
	}else if(brdr_t==D_BRDR){
		set_bkg_tiles(0,0,20,1,&map_brdr1[1]);
		set_bkg_tiles(0,13,20,1,&map_brdr2[1]);
	}
}

unsigned char score_x,score_y;
void draw_score(){
	bar=0;
	j=score;
	if(score>=1000){
		foo=DIGTILE+2*(j/1000);
		buf[0]=foo;
		buf[4]=foo+1;
	}else{
		buf[0]=2;
		buf[4]=2;
	}
	if(score>=100){
		j=j%1000;
		foo=DIGTILE+2*(j/100);
		buf[1]=foo;
		buf[5]=foo+1;
	}else{
		buf[1]=2;
		buf[5]=2;
	}
	if(score>=10){
		j=j%100;
		foo=DIGTILE+2*(j/10);
		buf[2]=foo;
		buf[6]=foo+1;
	}else{
		buf[2]=2;
		buf[6]=2;
	}
	
	i=DIGTILE+2*(j%10);
	buf[3]=i;
	buf[7]=i+1;
	set_bkg_tiles((score_x+bar),score_y,4,2,buf);

}

const unsigned char map_hp[]={28,30,29,31, 28,30,29,31, 28,30,29,31, 28,30,29,31, 28,30,29,31, };
const unsigned char map_hp_empty[]={32,34,33,35, 32,34,33,35, 32,34,33,35, 32,34,33,35, 32,34,33,35, };
#define HP_X	1
#define HP_Y	15
void draw_hp(){
	foo=0;
	while(foo!=max_hp){
	if(foo<hp)
		set_bkg_tiles(HP_X+foo*2,HP_Y,2,2,map_hp);
	else
		set_bkg_tiles(HP_X+foo*2,HP_Y,2,2,map_hp_empty);
	foo++;
	}
}

void respawn(){
	x=X_START;
	y=Y_START;
	xx=x>>FIX;
	yy=y>>FIX;
	
	vx=0;vy=0;
	state=WALK;
	anim_t=0;
}

void gameplay(){
  while(state!=GAMEOVER){
	lastjoy0=joy0;
	wait_vbl_done();
	joy0=joypad();
	tick++;
	
	zz_anim();
	brdr_anim();
	
	anim_t++;
	if(state==WALK){
		
		x+=walk_spd;
		
		ang+=ang_v;
		if(ang==0 || ang>=78)ang_v*=-1;
		
		move_sprite(ASPR,((x+16*(unsigned int)cos[ang])>>FIX)+8,((y-16*(unsigned int)sin[ang])>>FIX)+16);
		
		
		if(xx<160 && joy0 && !lastjoy0){

			vx=3*(unsigned int)cos[ang];
			vy=3*(unsigned int)sin[ang];
			
			state=JUMP;
			anim_t=0;
			
			move_sprite(ASPR,0,0);
			
			sfx_jump();
		}
		
		if(anim_t==DEL_WALK*2){
			set_sprite_tile(SSPR,STILE);
		}else if(anim_t==DEL_WALK){
			set_sprite_tile(SSPR,STILE+3);
		}else if(anim_t==DEL_WALK*3){
			set_sprite_tile(SSPR,STILE+4);
		}else if(anim_t==DEL_WALK*4){
			set_sprite_tile(SSPR,STILE);
			anim_t=0;
		}
		
	}
	
	
	
	if(state==JUMP){
		vy-=G;
		
		if(anim_t==DEL_JUMP){
			set_sprite_tile(SSPR,STILE+7);
		}else if(anim_t==DEL_JUMP*2){
			set_sprite_tile(SSPR,STILE+8);
		}else if(anim_t==DEL_JUMP*3){
			set_sprite_tile(SSPR,STILE+9);
		}else if(anim_t==DEL_JUMP*4){
			set_sprite_tile(SSPR,STILE+6);
			anim_t=0;
		}
		
		
		
		if(yy>YY_START){
			sfx_land();
			
			y=Y_START;
			anim_t=0;
			vx=0;
			vy=0;
			set_sprite_tile(SSPR,STILE);
			if(xx<80){
				state=WALK;	
			}else{
				
				sfx_pickup();
				
				score++;
				draw_score();
				
				if(game_mode!=M_HARD){
					if(hp<max_hp){
						hp++;
						draw_hp();
					}
				}
				state=WALKOFF;
			}
		}
	
	}
	
	if(state==WALKOFF){
		x+=walk_spd;
		x+=walk_spd;
		x+=walk_spd;

		if(anim_t==DEL_WALK*2){
			set_sprite_tile(SSPR,STILE);
		}else if(anim_t==DEL_WALK){
			set_sprite_tile(SSPR,STILE+3);
		}else if(anim_t==DEL_WALK*3){
			set_sprite_tile(SSPR,STILE+4);
		}else if(anim_t==DEL_WALK*4){
			set_sprite_tile(SSPR,STILE);
			anim_t=0;
		}
		
		if(xx>160){
			respawn();
		}
	}
	
	
	x+=vx;
	y-=vy;

	
	xx=x>>FIX;
	yy=y>>FIX;
	
	get_bkg_tiles((xx+4)/8,(yy+4)/8,1,1,&tile);
	if(yy>160 || TILE_TYPE[tile]==1){
		
		sfx_velcro();
		sfx_oops();
		
		
		i=get_sprite_tile(SSPR);
		set_sprite_tile(s_n,i);
		move_sprite(s_n,xx+8,yy+16);
		s_n++;
		if(s_n==s_max)
			s_n=s_min;
		
		if(hp==0){
			vx=0;
			vy=0;
			anim_t=0;
			state=GAMEOVER;
			move_sprite(ASPR,0,0);
		}else{
			hp--;
			draw_hp();
			respawn();
		}
		
	}
	
	move_sprite(SSPR,xx+8,yy+16);
  }
}


#define CUR_X	6
#define CUR_Y	10
unsigned char sel;

#define hiscore_x	15
#define hiscore_y	1
void draw_hiscore(){
	bar=0;
	j=hiscore[sel];
	if(hiscore[sel]>=1000){
		foo=DIGTILE+2*(j/1000);
		buf[0]=foo;
		buf[4]=foo+1;
	}else{
		buf[0]=2;
		buf[4]=2;
	}
	if(hiscore[sel]>=100){
		j=j%1000;
		foo=DIGTILE+2*(j/100);
		buf[1]=foo;
		buf[5]=foo+1;
	}else{
		buf[1]=2;
		buf[5]=2;
	}
	if(hiscore[sel]>=10){
		j=j%100;
		foo=DIGTILE+2*(j/10);
		buf[2]=foo;
		buf[6]=foo+1;
	}else{
		buf[2]=2;
		buf[6]=2;
	}
	
	i=DIGTILE+2*(j%10);
	buf[3]=i;
	buf[7]=i+1;
	set_bkg_tiles((hiscore_x+bar),hiscore_y,4,2,buf);
}




void titlescreen(){
	set_bkg_tiles(0,0,20,18,map_titlescreen);
	draw_hiscore();

	set_sprite_tile(0,STILE);
	move_sprite(0,8+CUR_X*8,16+CUR_Y*8+sel*16);
	anim_t=0;
	
	DISPLAY_ON;
	waitpadup();
	while(1){
		lastjoy0=joy0;
		wait_vbl_done();
		joy0=joypad();
		move_sprite(0,8+CUR_X*8,16+CUR_Y*8+sel*16);
		
		anim_t++;
		if(anim_t==DEL_WALK*2){
			set_sprite_tile(SSPR,STILE);
		}else if(anim_t==DEL_WALK){
			set_sprite_tile(SSPR,STILE+3);
		}else if(anim_t==DEL_WALK*3){
			set_sprite_tile(SSPR,STILE+4);
		}else if(anim_t==DEL_WALK*4){
			set_sprite_tile(SSPR,STILE);
			anim_t=0;
		}
		
		if(joy0&J_A || joy0&J_B || joy0&J_START){
			sfx_start();
			break;
			
		}
		if(joy0&J_UP && !(lastjoy0&J_UP)){
			if(sel!=0){
				sel--;
				draw_hiscore();
				sfx_beep();
			}
		}else if(joy0&J_DOWN && !(lastjoy0&J_DOWN)){
			if(sel!=2){
				sel++;
				draw_hiscore();
				sfx_beep();
			}
		}
	}
	
	game_mode=sel;
	if(game_mode==M_EASY){
		YY_START=70;
	}
	else if(game_mode==M_NORMAL){
		YY_START=76;
	}
	else if(game_mode==M_HARD){
		YY_START=72;
	}
	
	DISPLAY_OFF;
}



void main(){
	
	joy0=joypad();
	wait_vbl_done();
	ENABLE_RAM_MBC1;
	j=0;
	for(i=0;i!=8;i++){
		if(*(volatile unsigned char*)(0xA000+i)==0x42)j++;
	}
	joy0=joypad();
	if(j!=8 || (joy0&J_START && joy0&J_SELECT)){

		for(i=0;i<8;i++){
			*(volatile unsigned char*)(0xA000+i)=0x42;
		}
		for(i=0;i<8;i++){
			*(volatile unsigned char*)(0xA008+i)=0x00;
		}
	}
	hiscore[0]=*(volatile unsigned int*)(0xA008);
	hiscore[1]=*(volatile unsigned int*)(0xA00a);
	hiscore[2]=*(volatile unsigned int*)(0xA00c);
	DISABLE_RAM_MBC1;
	
	
	SFX_ON=1;
	MUSIC_ON=1;
	music_disable();
	disable_interrupts();
	add_VBL(play_music);
	enable_interrupts();
	
	
	music_init();
	sel=1;
_MAIN_RESET:

	DISPLAY_OFF;
	SHOW_BKG;
	SHOW_SPRITES;
	

	

	
	
	set_bkg_data(0,256,gfx_tileset);
	
	OBP0_REG=2|(1<<4)|(3<<6);
	set_sprite_data(STILE,16,gfx_sheep);

	for(i=0;i<40;i++){
		set_sprite_tile(i,STILE);
		move_sprite(i,0,0);
	}
	
	
	song_data=&twinkle_twinkle;
	song_start=song_data;
	music_enable();
	titlescreen();
	music_disable();
	
	
	x=X_START;
	y=Y_START;	
	set_sprite_tile(ASPR,ATILE);
	anim_t=0;
	set_bkg_tiles(0,0,20,18,tilemap1);
	set_sprite_tile(2,11);
	move_sprite(2,8+8*16,16+8*13);
	
	score_x=8;
	score_y=15;
	score=0;
	draw_score();
	max_hp=3;
	hp=max_hp;
	draw_hp();
	
	brdr_t=D_BRDR-1;
	brdr_anim();
	zzf=2;
	zzt=255;
	zz_anim();
	
	tick=255;
	state=WALK;
	DISPLAY_ON;
	
	song_data=&popcorn;
	song_start=song_data;
	music_enable();
	
	gameplay();
	
	wake_up();
	music_disable();
	
	
	song_data=&loser;
	song_start=song_data;
	music_enable();
	
	foo=hiscore[game_mode];
	bar=score;
	if(bar>foo){
		hiscore[game_mode]=bar;

		ENABLE_RAM_MBC1;
		*(volatile unsigned int*)(0xA008+(2*game_mode))=bar;
		DISABLE_RAM_MBC1;
	}
	for(i=0;i<11*2;i++)buf[i]=2;
	set_bkg_tiles(HP_X,HP_Y,11,2,map_gameover);
	tick=256-32;
	for(i=0;i<140;i++){
		wait_vbl_done();
		tick++;
		if(tick==32){
			set_bkg_tiles(HP_X,HP_Y,11,2,map_gameover);
			tick=0;
		}else if(tick==16){
			set_bkg_tiles(HP_X,HP_Y,11,2,buf);
		}
	}
	
	music_disable();
	wait_vbl_done();
	goto _MAIN_RESET;
}

