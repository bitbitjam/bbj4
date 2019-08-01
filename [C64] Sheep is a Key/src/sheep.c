
#include <stdlib.h>
#include <time.h>
#include <conio.h>

typedef  unsigned int byte;
typedef  unsigned short word;
#include "level.h"
#define CHARSET 0xE800

word color_lookup[] = {
	0xd800,
	0xd828,
	0xd850,
	0xd878,
	0xd8a0,
	0xd8c8,
	0xd8f0,
	0xd918,
	0xd940,
	0xd968,
	0xd990,
	0xd9b8,
	0xd9e0,
	0xda08,
	0xda30,
	0xda58,
	0xda80,
	0xdaa8,
	0xdad0,
	0xdaf8,
	0xdb20,
	0xdb48,
	0xdb70,
	0xdb98,
	0xdbc0
};

word lookup[] = {
	0x0400,
	0x0428, 
	0x0450, 
	0x0478, 
	0x04a0, 
	0x04c8, 
	0x04f0, 
	0x0518, 
	0x0540, 
	0x0568, 
	0x0590, 
	0x05b8, 
	0x05e0, 
	0x0608,
	0x0630, 
	0x0658, 
	0x0680, 
	0x06a8, 
	0x06d0, 
	0x06f8,  
	0x0720, 
	0x0748, 
	0x0770, 
	0x0798,
	0x07c0
};
		

#pragma staticlocals (1); 

#define lda_i(b) asm ("lda #%b",(char)b)
#define sta_a(b) asm ("sta %w",b)
#define lda_a(b) asm ("lda %w",b)
#define eor_i(b) asm ("eor #%b",(char)b)

	
#define wr(idx) (__AX__=(idx), 	       	\
       	       	asm ("sta $2000"),      \
                asm ("lda $2000"),      \
                asm ("ldx #$00"),	\
		__AX__)
		
#define joy() (\
		lda_i(255),\
		sta_a(0xdc00),\
		lda_a(0xdc00),\
		eor_i(0xff),\
		__A__\
		)

#define store(v) (\
	asm("sta %v",v),\
	__A__ \
)		

#define bit(v,b) (\
	asm("lda %v",v),\
	asm("and #%b",(char) b),\
	__A__)
	
#define addZP8(v,b) (\
	asm("clc"),\
	asm("lda #%v",(char) b),\
	asm("adc (%v)",v),\
	asm("sta %v",v),\
	asm("bcc ok"),\
	asm("inc (%v+1)",v),\
	asm	("ok:"),\
	)
byte db_cell_color=1;		
byte db_ch=0;
byte db_w=0;
byte db_h=0;
byte db_color=0;
byte db_y=0;
byte db_x=0;

/*void drawbox () {
	
	asm ("lda %v",db_y);
	asm ("asl");
	asm ("tay");
	asm ("lda %v,y",lookup);
	asm ("sta $02");
	asm ("lda %v+1,y",lookup);
	asm ("sta $03");
	
	asm("clc");
	asm("lda %v",db_x);
	asm("adc $02");
	asm("sta $02");	
	asm("lda #$0");
	asm("adc $03");
	asm("sta $03");

	asm ("lda %v",db_y);
	asm ("asl");
	asm ("tay");
	asm ("lda %v,y",color_lookup);
	asm ("sta $04");
	asm ("lda %v+1,y",color_lookup);
	asm ("sta $05");
	
	asm("clc");
	asm("lda %v",db_x);
	asm("adc $04");
	asm("sta $04");	
	asm("lda #$0");
	asm("adc $05");
	asm("sta $05");
	
asm ("next_row:");	
	asm ("ldy #0");
asm ("next_col:");
	asm ("lda %v",db_ch);
	asm ("sta ($02),y");
	asm ("lda %v",db_cell_color);
	asm ("sta ($04),y");
	asm ("iny");
	asm ("cpy %v",db_w);
	asm ("jne next_col");
	asm ("clc");
	asm ("lda #40");
	asm ("adc $02");
	asm ("sta $02");
	asm ("lda #$0");
	asm ("adc $03");
	asm ("sta $03");
	
	asm ("clc");
	asm ("lda #40");
	asm ("adc $04");
	asm ("sta $04");
	asm ("lda #$0");
	asm ("adc $05");
	asm ("sta $05");
	asm ("dec %v",db_h);
	asm ("jne next_row");
	
	
}*/

void drawbox () {
	int i,j;
	char *s = (char *) lookup[db_y]+db_x;
	char *c = (char *) color_lookup[db_y]+db_x;
	int w=db_x+db_w;
	int h=db_y+db_h;
	int dw = 40-db_w;
	
	for (i=db_y;i<h;i++) {
		for ( j=db_x;j<w;j++) {
			*s=db_ch;
			*c=db_cell_color;
			s++;
			c++;
		}
		
		s+=dw;
		c+=dw;
	}
}

/*void drawblock () {
	
	byte rowlen=5;
	
	asm("lda #$00");
	asm("sta $02");
	asm("lda #$04");
	asm("sta $03");

	asm("ldy #$0");
	asm("lda #$00");
	asm("sta ($02),y");
	asm("iny");
asm("nch:");
	asm("lda #$01");
	asm("sta ($02),y");
	asm("iny");
	asm("cpy #$10");
	asm("jne nch");

	asm("lda #$02");
	asm("sta ($02),y");

	asm ("clc");
	asm ("lda #40");
	asm ("adc $02");
	asm ("sta $02");
	asm ("bcc ok2");
	asm ("inc $3");
	asm	("ok2:");	
	
asm ("next_row1:");
	asm("ldy #$0");
	asm("lda #$03");
	asm("sta ($02),y");
	asm("iny");
asm("nch1:");
	asm("lda #$04");
	asm("sta ($02),y");
	asm("iny");
	asm("cpy #$10");
	asm("jne nch1");

	asm("lda #$05");
	asm("sta ($02),y");

	asm ("clc");
	asm ("lda #40");
	asm ("adc $02");
	asm ("sta $02");
	asm ("bcc ok3");
	asm ("inc $3");
	asm	("ok3:");	
	
	asm ("dec %v",rowlen);
	asm ("jne next_row1");
	
	
}*/
static const unsigned char data[] = 
{
	4,64,0,4,64,0,21,127,224,121,127,248,93,255,254,117,255,251,85,255,255,86,255,250,86,255,236,87,255,248,26,255,236,11,190,184,10,171,168,6,174,164,4,106,164,1,64,17,1,16,17,0,80,68,0,68,68,0,4,4,0,0,0,
	140,0,0,0,0,0,0,0,0,0,0,0,0,0,0,0,0,0,0,0,0,0,0,0,0,0,0,0,0,0,0,0,0,0,0,0,0,0,0,0,0,0,0,0,0,0,0,0,0,0,0,0,0,0,0,0,0,0,0,0,0,0,0,0,140,0,0,0,4,64,0,4,64,0,21,127,224,121,127,248,93,255,254,117,255,251,85,
	255,255,86,255,250,86,255,236,87,255,248,26,255,236,11,190,184,10,171,168,6,174,164,20,106,164,81,64,68,69,0,17,68,0,17,4,0,17,4,0,1,140,0,0,0,0,0,0,0,0,0,0,0,0,0,0,0,0,0,0,0,0,0,0,0,0,0,0,0,0,0,0,0,0,
	0,0,0,0,0,0,0,0,0,0,0,0,0,0,0,0,0,0,0,0,0,0,0,0,0,0,0,0,0,0,0,140,0,1,16,0,1,16,11,253,84,47,253,109,191,255,117,239,255,93,255,255,85,175,255,149,59,255,149,47,255,213,59,255,164,46,190,224,42,234,160,
	26,186,144,26,169,16,68,1,64,68,4,64,17,5,0,17,17,0,16,16,0,0,0,0,140,0,0,0,0,0,0,0,0,0,0,0,0,0,0,0,0,0,0,0,0,0,0,0,0,0,0,0,0,0,0,0,0,0,0,0,0,0,0,0,0,0,0,0,0,0,0,0,0,0,0,0,0,0,0,0,0,0,0,0,0,0,0,0,140,0,
	0,0,0,1,16,0,1,16,11,253,84,47,253,109,191,255,117,239,255,93,255,255,85,175,255,149,59,255,149,47,255,213,59,255,164,46,190,224,42,234,160,26,186,144,26,169,20,17,1,69,68,0,81,68,0,17,68,0,16,64,0,16,
	140,0,0,0,0,0,0,0,0,0,0,0,0,0,0,0,0,0,0,0,0,0,0,0,0,0,0,0,0,0,0,0,0,0,0,0,0,0,0,0,0,0,0,0,0,0,0,0,0,0,0,0,0,0,0,0,0,0,0,0,0,0,0,0,140,0 	
};



/*static const unsigned char charset[] = 
{
	21,127,127,127,127,127,127,127,85,255,255,255,255,255,255,255,84,253,253,253,253,253,253,253,127,127,127,127,127,127,127,127,255,255,255,255,255,255,255,255,253,253,253,253,253,253,253,253,0,0,0,0,0,0,
	0,0,0,0,0,0,0,0,0,0,0,0,0,0,0,0,0,0,0,0,0,0,0,0,0,0,0,0,0,0,0,0,0,0,0,0,0,0,0,0,0,0,0,0,0,0,0,0,0,0,0,0,0,0,0,0,0,0,0,0,0,0,0,0,0,0,0,0,0,0,0,0,0,0,0,0,0,0,0,0,0,0,0,0,0,0,0,0,0,0,0,0,0,0,0,0,0,0,0,0,0,
	0,0,0,0,0,0,0,0,0,0,0,0,0,0,0,0,0,0,0,0,0,0,0,0,0,0,0,0,0,0,0,0,0,0,0,0,0,0,0,0,0,0,0,0,0,0,0,0,0,0,0,0,0,0,0,0,0,0,0,0,0,0,0,0,0,0,0,0,0,0,0,0,0,0,0,0,0,0,0,0,0,0,0,0,0,0,0,0,0,0,0,0,0,0,0,0,0,0,0,0,0,
	0,0,0,0,0,0,0,0,0,0,0,0,0,0,0,0,0,0,0,0,0,0,0,0,0,0,0,0,0,0,0,0,0,0,0,0,0,0,0,0,0,0,0,0,0,0,0,0,0,0,0,0,0,0,0,0,0,0,0,0,0,0,0,0,0,0,0,0,0,0,0,0,0,0,0,0,0,0,0,0,0,0,0,0,0,0,0,0,0,0,0,0,0,0,0,0,0,0,0,0,0,
	0,0,0,0,0,0,0,0,0,0,0,0,0,0,0,0,0,0,0,0,0,0,0,0,0,0,0,0 	
};*/
byte anim=0;
byte frame=10;
byte jump=0,floor=0,newfloor=0;

void move_player (word x,word y) {
	
	byte aid;
	--frame;
	if (frame==0) {
		if (floor==0 || floor==2) aid = 0xf4;
		else aid=0xf0;
		if (anim==0) {
			asm("lda %v",aid);        //set sprite data
			asm ("sta $07f8"); 
			anim=1;
		} else {
			asm ("inc $07f8");
			asm ("inc $07f8");			
			anim=0;
		}
		frame=10;
	}
	//*((char *) 0xd021)=0;
	
	*((char *) 0xd025)=0;
	*((char *) 0xd026)=1;

	*((char *) 0xd027)=12;
	*((char *) 0xd028)=0;
	
	*((char *) 0xd015)=1;

	*((char *) 0xd000)=x;
	*((char *) 0xd001)=y;
	
	*((char *) 0xd002)=x;
	*((char *) 0xd003)=y;

	*((char *) 0xD01c )=3;
	
	if (x>255) {
		*((char *) 0xd010)=3;
	}
	else
		*((char *) 0xd010)=0;
	
	
}
 void waitvsync() {
	
	 asm("wait:");
	 asm ("lda $d012");
	 asm ("cmp #$ff");
	 asm ("jne wait");
 }
 

void draw_level (byte *level) {
	int i=0;
	
	db_ch=27;
     db_cell_color=10;db_w=40;db_h=8;db_y=0;db_x=0;
	 drawbox();
	 db_cell_color=11;db_w=40;db_h=8;db_y=8;db_x=0;
	 drawbox();
	 
	 db_cell_color=12;db_w=40;db_h=8;db_y=16;db_x=0;
	 drawbox();

	
	while (level[i]!=END) {
		byte type=level[i++];
		db_x=level[i++];
		db_y=level[i++];
		db_w=level[i++];
		db_h=level[i++];		
		db_cell_color=14;
		db_ch=28;
		drawbox();
		
		
	}
}

int check_collision (short px,short py) {
	short xx=px/8-3;
	short yy=py/8-5;
	

	char *s = (char *) lookup[yy]+xx;

	char *o=s;

	
if (xx<0)	 return 0;
if (xx>37) return 0;
		
	     //if (*s==1)return 1;	
	//s++;if (*s==1) return 1;
	//s++;if (*s==1) return 1;
	
	s=o+40;
	
	if (*s==28)return 1;	s++;		
	if (*s==28) return 1;
	//s++;if (*s==1) return 1;
	
	//s=o+40;
	
	   //  if (*s==1)return 1;	
	//s++;if (*s==1) return 1;
	//s++;if (*s==1) return 1;
		

		return 0;
	
}
#define poke(m,v) *((char *)m)=v
#define peek(m) *((char *)m)


int main (void)
{
	word j;
    int levid=0;
	short tq;
	short q=0;
    short x=0x80;
	short y=0x80;
	byte d;
	short e;
	int orgchar;
	
	short posx[] = {0,320,0};
	short posy[] = {8*8+29,8*8+29+64,8*8+29+128};
	short ext[] = {350,0,350};
	char dir[] = {1,2,1};
	
	
	int kill=0;

	
		
	orgchar = *((char *) 0xd018)*40;
  
	for (j=0;j<512;j++) {
		*((char *) 0x3c00+j)=data[j];
	}
	
	/*for (j=0;j<384;j++) {
		*((char *) 0x3000+j)=charset[j];
	}*/
	
	poke (56334,(peek(56334) & 254));
	poke (1,(peek(1)&251));
	
	for (j=0;j<100*8;j++) {
		*((char *) 0x3000+j)=*((char*)53248 +j) ;
	}

	for (j=27*8;j<29*8;j++) {
		*((char *) 0x3000+j)=255 ;
	}

	poke (1,(peek(1)|4));
	poke (56334, (peek(56334) | 1));

	
	poke (53272,21);

	asm ("lda #$1C");//      ;charset at $3000
	asm ("sta $d018");

	/*asm("lda #200");	
	asm("ora #16");
	asm ("sta $d016");
*/
	
	asm("lda #$01");
	asm ("sta $d015");
	asm("lda #$80");
	asm ("sta $d000");
	asm("sta $d001");
	
 
	draw_level(levels[levid]);
	 
	 x=posx[floor];
	 y=posy[floor];
	 d=dir[floor];
	 e=ext[floor];
	 
	 asm("lda #$01");
	 asm ("sta $d021");
	 
	 asm("lda #$00");
	 asm ("sta $d022");

	 asm("lda #$09");
	 asm ("sta $d023");

	 

	 while(1) {
		
		 j=joy();	
	
		 if (d==1) {x++;if (x==e) newfloor=1;}
		else if (d==2) {x--; if (x==e)newfloor=1;}
	
		
		if (newfloor==1) {
			++floor;
			if (floor>2) {
					floor=0;
					levid++;
					if (levels[levid]==0) {
						break;
					}
					draw_level(levels[levid]);					
			}
			
			x=posx[floor];
			y=posy[floor];
			d=dir[floor];
			e=ext[floor];
			newfloor=0;
		} else if (check_collision (x,y+q)==1) {
			x=posx[floor];
			y=posy[floor];
			d=dir[floor];
			e=ext[floor];
			kill++;
		}
		
		if (jump==0 && bit(j,16)) {
			jump=1;
			q=0;
		}
		
		if (jump==1) {
			q=q-1;
			if (q<-30) {
				jump=3;
				tq=0;
			}
		} else if (jump==2) {
			q=q+1;
			if (q>0) {
				jump=0;
				q=0;
			}
		} else if (jump==3) {
			tq++;
			if (tq>4) 
				jump=2;
		}
		
		move_player(x,y+q);
		
		
		 //asm ("jsr %v+3",musicplayer);
		 waitvsync();
		
		 gotoxy (0,24);
		 cprintf ("level %d/10 death %d",levid+1,kill);
	
	}
	*((char *) 0xd015)=0;
	clrscr();
	gotoxy (5,10);
	cprintf ("congratulation you did it!!! ");
	gotoxy (11,13);
	cprintf ("only %03d death ",kill);
    /* Done */
    return EXIT_SUCCESS;
}
