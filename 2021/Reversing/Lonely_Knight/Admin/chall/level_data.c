




enum{COIN_REG, COIN_END};

//NOTE MAX_COINS = 12

//y, room, x, type
//y = TURN_OFF end of list
const unsigned char level_1_coins[]={
	0x90, 0, 0x70, COIN_REG, 
	0xc0, 1, 0x40, COIN_REG, 
	0x60, 1, 0x90, COIN_REG,  
	0x80, 2, 0x00, COIN_REG, 
	0xa1, 2, 0x70, COIN_REG, 
	0x69, 3, 0xa0, COIN_REG, 
	0x71, 4, 0xd0, COIN_REG, 
	0x75, 5, 0xf0, COIN_REG, 
	0xc3, 6, 0x20, COIN_REG, 
	0xb9, 7, 0xc0, COIN_END, 	
	TURN_OFF
};

const unsigned char level_2_coins[]={
	0xa0, 0, 0x20, COIN_REG, 
	0xa0, 1, 0x40, COIN_REG,
	0x60, 2, 0x70, COIN_REG, 
	0xaf, 3, 0x20, COIN_REG, 
	0xbc, 3, 0x70, COIN_REG,
	0xc1, 5, 0x50, COIN_REG,
	0x7a, 6, 0x90, COIN_REG, 
	0x9a, 6, 0xd0, COIN_REG, 
	0x60, 7, 0x30, COIN_END, 
	0xa0, 7, 0x40, COIN_REG, 
	TURN_OFF
};

const unsigned char level_3_coins[]={
	0x80, 0, 0x80, COIN_REG, 
	0x70, 1, 0x50, COIN_REG,
	0x80, 1, 0xd0, COIN_REG,
	0x80, 2, 0x40, COIN_REG, 
	0x80, 2, 0x80, COIN_REG,
	0x80, 2, 0xc0, COIN_REG, 
	0x80, 3, 0x30, COIN_REG, 
	0xa0, 7, 0x25, COIN_END, 
	0x70, 7, 0x80, COIN_REG, 
	0xb0, 7, 0xd0, COIN_REG, 
	TURN_OFF
};

const unsigned char level_4_coins[]={
	0x69, 1, 0x50, COIN_REG, 
	0x79, 1, 0x80, COIN_REG,
	0x8a, 1, 0xd0, COIN_REG,
	0x8f, 2, 0x40, COIN_REG, 
	0x8b, 2, 0x80, COIN_REG,
	0x81, 2, 0xc0, COIN_REG, 
	0x80, 3, 0x30, COIN_REG, 
	0xa0, 7, 0x25, COIN_REG, 
	0xc0, 7, 0x80, COIN_END, 
	0xb0, 7, 0xe0, COIN_REG, 
	TURN_OFF
};

const unsigned char * const Coins_list[]={
	level_1_coins, level_2_coins, level_3_coins , level_4_coins
};




enum{ENEMY_CHASE, ENEMY_BOUNCE};

//NOTE MAX_ENEMY = 10

//NOTE, after testing, we can only handle 4 enemies on the same screen

//y, room, x
//y = TURN_OFF end of list
const unsigned char level_1_enemies[]={

/* stress test	
	0x11,0,0xe2,ENEMY_CHASE,
	0x21,0,0xe4,ENEMY_CHASE,
	0x31,0,0xe6,ENEMY_CHASE,
	0x41,0,0xe8,ENEMY_CHASE,
	0x51,0,0xe8,ENEMY_CHASE,
	0x61,0,0xe8,ENEMY_CHASE,
	0x71,0,0xe8,ENEMY_CHASE,
*/
	
	0xc0, 0, 0xc0, ENEMY_CHASE, 
	0xc0, 1, 0xe0, ENEMY_CHASE, 
	0xc0, 2, 0x30, ENEMY_CHASE,  
	0xc0, 3, 0x90, ENEMY_CHASE, 
	0xb0, 4, 0x20, ENEMY_CHASE,  
	0xc0, 5, 0xb0, ENEMY_CHASE, 
	0x80, 6, 0x00, ENEMY_CHASE, 
	0xc0, 7, 0x90, ENEMY_CHASE, 
	TURN_OFF
};


const unsigned char level_2_enemies[]={
	0xc0, 0, 0x90, ENEMY_BOUNCE, 
	0xc0, 1, 0xd0, ENEMY_BOUNCE, 
	0x40, 2, 0x40, ENEMY_BOUNCE, 
	0xc0, 3, 0x30, ENEMY_BOUNCE, 
	0xc0, 4, 0x80, ENEMY_BOUNCE, 
	0xc0, 5, 0x20, ENEMY_BOUNCE, 
	0xc0, 6, 0x20, ENEMY_BOUNCE, 
	0xc0, 7, 0x60, ENEMY_BOUNCE, 
	TURN_OFF
};

	
const unsigned char level_3_enemies[]={
	0xc0, 0, 0xc0, ENEMY_BOUNCE, 
	0xc0, 1, 0xf0, ENEMY_BOUNCE, 
	0xc0, 2, 0x80, ENEMY_CHASE, 
	0xc0, 3, 0xd0, ENEMY_CHASE, 
	0xc0, 4, 0x40, ENEMY_BOUNCE, 
	0xc0, 5, 0x80, ENEMY_BOUNCE, 
	0xc0, 6, 0xc0, ENEMY_BOUNCE, 
	0xb0, 7, 0x10, ENEMY_CHASE,  
	TURN_OFF
};

const unsigned char level_4_enemies[]={
	0xc0, 0, 0xc0, ENEMY_BOUNCE, 
	0xc0, 1, 0xf0, ENEMY_BOUNCE, 
	0xc0, 2, 0x80, ENEMY_CHASE, 
	0xc0, 3, 0xd0, ENEMY_CHASE, 
	0xc0, 4, 0x40, ENEMY_BOUNCE, 
	0xc0, 5, 0x80, ENEMY_BOUNCE, 
	0xc0, 6, 0xc0, ENEMY_BOUNCE, 
	0xb0, 7, 0x10, ENEMY_BOUNCE, 
	0xb0, 7, 0x60, ENEMY_CHASE,  
	TURN_OFF
};

const unsigned char * const Enemy_list[]={
	level_1_enemies, level_2_enemies, level_3_enemies,level_4_enemies
};














// 5 bytes per metatile definition, tile TL, TR, BL, BR, palette 0-3
// T means top, B means bottom, L left,R right
// 51 maximum # of metatiles = 255 bytes
// 5th byte, 	1000 0000 = floor collision
// 				0100 0000 = all collision, solid
//				0000 0011 = palette

const unsigned char metatiles1[]={
	0, 0, 0, 0,  0,
	1, 1, 1, 1,  0,
	2, 2, 2, 2,  0,
	3, 3, 3, 3,  0,
	4, 4, 4, 4,  0,
	20, 20, 20, 20,  0,
	5, 7, 24, 26,  0,
	18, 18, 18, 18,  0,
	1, 1, 1, 1,  1,
	2, 2, 2, 2,  1,
	3, 3, 3, 3,  1,
	17, 17, 17, 17,  1,
	18, 18, 18, 18,  1,
	5, 7, 24, 26,  1,
	20, 20, 20, 20,  2,
	4, 4, 4, 4,  2,
	18, 18, 18, 18,  2,
	1, 1, 1, 1,  2,
	2, 2, 2, 2,  2,
	3, 3, 3, 3,  2,
	5, 7, 24, 26,  2,
	18, 18, 18, 18,  3,
	17, 17, 17, 17,  3,
	1, 1, 1, 1,  3,
	2, 2, 2, 2,  3,
	3, 3, 3, 3,  3,
	5, 7, 24, 26,  3
};

#define COL_DOWN 0x80
#define COL_ALL 0x40
/*
const unsigned char is_solid[]={
	0,
	COL_DOWN,
	COL_ALL+COL_DOWN,
	COL_DOWN,
	COL_DOWN,
	COL_DOWN,
	0,
	0,
	0,
	0,
	0,
	0
};
*/
const unsigned char is_solid[]={
	0,
	0,
	0,
	0,
	0,
	0,
	0,
	0,
	0,
	0,
	0,
	0
};

#include "BG/Level1.c"
#include "BG/Level2.c"
#include "BG/Level3.c"
#include "BG/Level4.c"

const unsigned char * const Levels_list[]={
Level1_0,Level1_1,Level1_2,Level1_3,Level1_4,Level1_5,Level1_6,Level1_7,
Level2_0,Level2_1,Level2_2,Level2_3,Level2_4,Level2_5,Level2_6,Level2_7,
Level3_0,Level3_1,Level3_2,Level3_3,Level3_4,Level3_5,Level3_6,Level3_7,
Level4_0,Level4_1,Level4_2,Level4_3,Level4_4,Level4_5,Level4_6,Level4_7
};

const unsigned char Level_offsets[]={
	0,8,16,24
};

#define MAX_ROOMS (8-1)
#define MAX_SCROLL (MAX_ROOMS*0x100)-1
// data is exactly 240 bytes, 16 * 15
// doubles as the collision map data

