#define ACCEL 0x30
#define GRAVITY 0x50
#define MAX_SPEED 0x240
#define JUMP_VEL -0x600
#define MAX_RIGHT 0x9000



#pragma bss-name(push, "ZEROPAGE")

// GLOBAL VARIABLES
unsigned char pad1;
unsigned char pad1_new;
unsigned char collision;
unsigned char collision_L;
unsigned char collision_R;
unsigned char collision_U;
unsigned char collision_D;
unsigned char coordinates;
unsigned char temp1;
unsigned char temp2;
unsigned char temp3;
unsigned char temp4;
unsigned int temp5;
unsigned int temp6;
unsigned int ind;
unsigned char eject_L; // from the left
unsigned char eject_R; // remember these from the collision sub routine
unsigned char eject_D; // from below
unsigned char eject_U; // from up
unsigned char direction; //facing left or right?
#define LEFT 0
#define RIGHT 1
#define UP 2
#define DOWN 3

int address;
unsigned char x; // room loader code
unsigned char y;
unsigned char nt;
unsigned char index;
unsigned char index2;
unsigned char index3=0;
unsigned char room;
unsigned char map;
unsigned int scroll_x;
unsigned int scroll_y;
unsigned char scroll_count;
unsigned int pseudo_scroll_x;
//unsigned int pseudo_scroll_y;
unsigned char L_R_switch;
unsigned char old_x;
unsigned char old_y;
//unsigned char old_y;
unsigned char temp_x;
unsigned char temp_y;
unsigned char song;
#define MAX_SONGS 2
enum {SONG_GAME, SONG_PAUSE};
enum {SFX_JUMP, SFX_DING, SFX_NOISE};

unsigned char game_mode;
enum {MODE_TITLE, MODE_GAME, MODE_PAUSE, MODE_SWITCH, MODE_END, MODE_GAME_OVER};

unsigned char coins;
unsigned char lives;
const unsigned char * pointer;
unsigned char level;
unsigned char offset;
unsigned char level_up;
unsigned char bright;
unsigned char bright_count;
unsigned char death;
unsigned char order;
unsigned char order1;
unsigned char order2=0;
unsigned char timer;
unsigned char enemy_frames; //in case of skipped frames
unsigned char map_loaded; //only load it once
unsigned char short_jump_count;


#pragma bss-name(push, "BSS")

unsigned char c_map[240];
unsigned char c_map2[240];

struct Base {
	unsigned char x;
	unsigned char y;
	unsigned char width;
	unsigned char height;
};

struct Base Generic; 
struct Base Generic2; 

struct Hero {
	unsigned int x; // low byte is sub-pixel
	unsigned int y;
	signed int vel_x; // speed, signed, low byte is sub-pixel
	signed int vel_y;
};

struct Hero BoxGuy1;
// the width and height should be 1 less than the dimensions (14x12)
// note, I'm using the top left as the 0,0 on x,y

#define HERO_WIDTH 13
#define HERO_HEIGHT 11


#define MAX_COINS 10
unsigned char coin_x[MAX_COINS];
unsigned char coin_y[MAX_COINS];
unsigned char coin_active[MAX_COINS];
unsigned char coin_room[MAX_COINS];
unsigned char coin_actual_x[MAX_COINS];
unsigned char coin_type[MAX_COINS];
unsigned char player_special_order[MAX_COINS];
unsigned char player_order[MAX_COINS];
unsigned char index_order_1[MAX_COINS]={0,2,1,3,4,5,6,8,7,9};
unsigned char index_order_2[MAX_COINS]={0,1,2,4,3,5,6,7,9,8};
unsigned char index_order_3[MAX_COINS]={0,1,2,4,3,5,6,8,9,7};
unsigned char index_order_4[MAX_COINS]={2,0,1,5,3,4,6,9,7,8};
const unsigned char * const index_list[]={
	index_order_1, index_order_2, index_order_3 , index_order_4
};
unsigned char special_order_1[MAX_COINS]={0,1,2,4,3,5,6,8,7,9};
unsigned char special_order_2[MAX_COINS]={0,1,2,3,4,5,7,6,9,8};
unsigned char special_order_3[MAX_COINS]={0,2,1,4,5,3,6,9,8,7};
unsigned char special_order_4[MAX_COINS]={1,0,2,4,5,3,6,7,9,8};
const unsigned char * const special_list[]={
special_order_1, special_order_2 , special_order_3 , special_order_4
};

#define TURN_OFF 0xff
#define COIN_WIDTH 7
#define COIN_HEIGHT 11
#define BIG_COIN 13


#define MAX_ENEMY 16
unsigned char enemy_x[MAX_ENEMY];
unsigned char enemy_y[MAX_ENEMY];
unsigned char enemy_active[MAX_ENEMY];
unsigned char enemy_room[MAX_ENEMY];
unsigned char enemy_actual_x[MAX_ENEMY];
unsigned char enemy_type[MAX_ENEMY];
const unsigned char * enemy_anim[MAX_ENEMY];

#define ENEMY_WIDTH 13
#define ENEMY_HEIGHT 13


//for shuffling 16 enemies
const unsigned char shuffle_array[]={
0,1,2,3,4,5,6,7,8,9,10,11,12,13,14,15,
15,14,13,12,11,10,9,8,7,6,5,4,3,2,1,0,
0,2,4,6,8,10,12,14,1,3,5,7,9,11,13,15,
15,13,11,9,7,5,3,1,14,12,10,8,6,4,2,0	
};


const unsigned char palette_title[]={
//0x0f, 0x00, 0x10, 0x30,
0x0f,0x04,0x15,0x32,
0, 0, 0, 0,
0, 0, 0, 0,
0, 0, 0, 0
}; 


const unsigned char title_color_rotate[]={
	0x32,0x22,0x30,0x37
};



const unsigned char palette_bg[]={ 0x0f,0x00,0x10,0x30,
									0x0f,0x01,0x21,0x31,
									0x0f,0x06,0x16,0x26,
									0x0f,0x09,0x19,0x29 };



const unsigned char palette_sp[]={
0x22, 0x01, 0x11, 0x10,
0x22, 0x17, 0x28, 0x38,
0x22, 0x06, 0x16, 0x37,
0x22, 0x03, 0x13, 0x33,
}; 







const unsigned char END_TEXT[]="The end of the game.";
const unsigned char END_TEXT2[]="I guess you won?";
const unsigned char END_TEXT3[]="Lives: ";
const unsigned char DEAD_TEXT[]="You died.";

#include "NES_ST/title.h"
#include "NES_ST/FLAG.h"


// PROTOTYPES
void load_title(void);
void reset_special(void);
void reset_ind(void);
void load_room(void);
void load_room_1(void);
void draw_sprites(void);
void movement(void);	
void bg_collision(void);
void draw_screen_R(void);
void new_cmap(void);
void bg_collision_sub(void);
void bg_check_low(void);
char get_position(void);
void enemy_moves(void);
void sprite_collisions(void);
void check_spr_objects(void);
void sprite_obj_init(void);
void set_sprite_zero(void);
void update_hud(void);
void bg_collision_fast(void);
unsigned char check_order(void);
unsigned char check_special_order(void);