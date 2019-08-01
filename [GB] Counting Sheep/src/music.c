
#include <gb/hardware.h>

const unsigned int notes[]={
	44,  156, 262, 363, 457, 547, 631, 710, 786, 854, 923, 986,
	1046,1102,1155,1205,1253,1297,1339,1379,1417,1452,1486,1517,
	1546,1575,1602,1627,1650,1673,1694,1714,1732,1750,1767,1783,
	1798,1812,1825,1837,1849,1860,1871,1881,1890,1899,1907,1915,
	1923,1930,1936,1943,1949,1954,1959,1964,1969,1974,1978,1982,
	1985,1988,1992,1995,1998,2001,2004,2006,2009,2011,2013,2015
};
#define C	0
#define CS	1
#define D	2
#define DS	3
#define EF	3
#define E	4
#define F	5
#define FS	6
#define G	7
#define GS	8
#define A	9
#define AS	10
#define BF	10
#define B	11
#define OCTAVE	12
#define O	12
#define DN	13
#define UP	14
#define TEMPO	22
#define LENGTH	23
#define VOLUME	24
#define R	25
#define LOOP	254
#define END		255


const unsigned char loser[]={
	TEMPO,50,VOLUME,0x8,O,4,
	GS,8,FS,8,E,8,D,8,C,8,
	D,8,C,8,
	O,DN,
	G,8,F,8,E,8,D,8,C,2,

	R,2,R,2,R,2,R,2,
};
const unsigned char popcorn[]={
	TEMPO,30,VOLUME,0x8,O,4,
	
	B,8,  FS,8,D,8,FS,8, B,4,  B,8,A,8,
	B,8,  FS,8,D,8,FS,8, B,4,  B,8,O,UP,CS,8,
	D,8,CS,8,D,8,O,DN,B,8,O,UP, CS,8,O,DN,B,8,O,UP,CS,8,O,DN,A,8,
	B,8,A,8,B,8,  G,8,  B,4, B,8,A,8,

	LOOP
};
const unsigned char twinkle_twinkle[]={
	TEMPO,45,
	VOLUME,0x7,
	O,6,
	
	C,4,C,4,G,4,G,4,
	A,4,A,4,G,2,
	F,4,F,4,E,4,E,4,
	D,4,D,4,C,2,
	
	G,4,G,4,F,4,F,4,
	E,4,E,4,D,2,
	G,4,G,4,F,4,F,4,
	E,4,E,4,D,2,
	
	C,4,C,4,G,4,G,4,
	A,4,A,4,G,2,
	F,4,F,4,E,4,E,4,
	D,4,D,4,C,2,

	LOOP
};




extern unsigned char tempo,octave,length,lsb,msb,wait,volume;

extern unsigned char *song_data,*song_start;


void waitdo(){
	wait=3600/tempo/length;
}
void play_note(){
	NR22_REG=(volume<<4)|(0<<3)|(7);
	NR23_REG=lsb;
	NR24_REG=(1<<7)|msb;
	waitdo();
}

extern unsigned char a,b;

void parse_song(){
  while(1){
	a=*(song_data++);
	b=*(song_data++);
	if(a<OCTAVE){
		lsb=notes[(octave-3)*OCTAVE+a]&0xff;
		msb=notes[(octave-3)*OCTAVE+a]>>8;
		length=b;
		play_note();
		break;
	}else if(a==O){
		if(b==DN)octave--;
		else if(b==UP)octave++;
		else octave=b;
	}else if(a==TEMPO){
		tempo=b;
	}else if(a==VOLUME){
		volume=b;
	}else if(a==R){
		NR22_REG=0;
		length=b;
		waitdo();
	}else if(a==LOOP){
		song_data=song_start;
		break;
	}
  }
}
