/*
download 6502 compiler/Assembler from http://cc65.github.io/cc65/
*/

#include "LIB/neslib.h"
#include "LIB/nesdoug.h"
#include "Sprites.h" 
#include "full_game.h"
#include "level_data.c"

	
	
void main (void) {
	
	ppu_off(); // screen off
	
	bank_spr(1);
	
	set_vram_buffer();
	clear_vram_buffer();
	
	load_title();
	
	ppu_on_all(); // turn on screen
	
	scroll_x = 0;
	set_scroll_x(scroll_x);
	while (1){
		while(game_mode == MODE_TITLE){
			ppu_wait_nmi();
			set_music_speed(8);
			
			
			temp1 = get_frame_count();
			temp1 = (temp1 >> 3) & 3;
			pal_col(3,title_color_rotate[temp1]);
			
			
			pad1 = pad_poll(0);
			pad1_new = get_pad_new(0);
			if(pad1_new & PAD_START){
				pal_fade_to(4,0); 
				ppu_off();
				load_room();
				game_mode = MODE_GAME;
				pal_bg(palette_bg);
				song = SONG_GAME;
				music_play(song);
				scroll_x = 0;
				set_scroll_x(scroll_x);
				ppu_on_all();		
				pal_bright(4); 	
			}
			
			
			
		}
		
		
		
		while(game_mode == MODE_GAME){
			ppu_wait_nmi();
			
			set_music_speed(8);
		
			pad1 = pad_poll(0);
			pad1_new = get_pad_new(0);
			
			clear_vram_buffer(); 
			
			
			movement();
			
			check_spr_objects();
			
			sprite_collisions();
			
			set_scroll_x(scroll_x);
			
			draw_screen_R();
			
			//load_room_1();

			draw_sprites();
			
			if(pad1_new & PAD_START){
				game_mode = MODE_PAUSE;
				song = SONG_PAUSE;
				music_play(song);
				color_emphasis(COL_EMP_DARK);
				break; 
			}
			
			
			if(level_up) {
				game_mode = MODE_SWITCH;
				level_up = 0;
				bright = 4;
				bright_count = 0;
				order=0;
				order=check_order();
				if(!order)
				{
					order1=0;
					order1=check_special_order();
					if(!order1){
						death = 0;
						bright = 0;
						scroll_x = 0;
						set_scroll_x(scroll_x);
						ppu_off();
						delay(5);	
						oam_clear();
						clear_vram_buffer();
						game_mode = MODE_GAME_OVER;
						vram_adr(NAMETABLE_A);
						vram_fill(0,1024);
						ppu_on_all();
					}
					if(level==3)
					{
						level=4;
						order2=1;
					}
					else
						level=3;
				}
				else
					++level;
					
			}
			else if(death) {
				death = 0;
				bright = 0;
				scroll_x = 0;
				set_scroll_x(scroll_x);
				ppu_off();
				delay(5);	
				oam_clear();
				clear_vram_buffer();
				game_mode = MODE_GAME_OVER;
				vram_adr(NAMETABLE_A);
				vram_fill(0,1024);
				ppu_on_all();
			}
		}
		
		while(game_mode == MODE_SWITCH){ 
			ppu_wait_nmi();
			++bright_count;
			if(bright_count >= 0x10) { 
				bright_count = 0;
				--bright;
				if(bright != 0xff) pal_bright(bright); 
			}
			set_scroll_x(scroll_x);
			
			if(bright == 0xff) { 
				ppu_off();
				clear_vram_buffer();
				oam_clear();
				scroll_x = 0;
				set_scroll_x(scroll_x);
				if(level < 3)
				{
					load_room();
					game_mode = MODE_GAME;
					ppu_on_all();
					pal_bright(4); 
				}
				else if(level==3&&order1)
				{
					load_room();
					game_mode = MODE_GAME;
					ppu_on_all();
					pal_bright(4);	
				}
				else if (order2){
					pal_bg(palette_title);
					pal_spr(palette_sp);
					vram_adr(NAMETABLE_A);
					vram_unrle(FLAG);
					ppu_on_all();
					pal_bright(4);
				}
				else { 
					game_mode = MODE_END;
					vram_adr(NAMETABLE_A);
					vram_fill(0,1024);
					ppu_on_all();
					pal_bright(4); 
				}
			}
			reset_special();
			reset_ind();
		}
		
		
		
		while(game_mode == MODE_PAUSE){
			ppu_wait_nmi();

			clear_vram_buffer(); 
			pad1 = pad_poll(0); 
			pad1_new = get_pad_new(0);
			
			draw_sprites();
			
			if(pad1_new & PAD_START){
				game_mode = MODE_GAME;
				song = SONG_GAME;
				music_play(song);
				color_emphasis(COL_EMP_NORMAL);
			}
		}
		
		
		
		while(game_mode == MODE_END){
			ppu_wait_nmi();
			oam_clear();
			
			clear_vram_buffer(); 
			multi_vram_buffer_horz(END_TEXT, sizeof(END_TEXT), NTADR_A(6,13));
			multi_vram_buffer_horz(END_TEXT2, sizeof(END_TEXT2), NTADR_A(8,15));
			multi_vram_buffer_horz(END_TEXT3, sizeof(END_TEXT3), NTADR_A(11,17));
			temp1 = (lives / 10) + 0x30;
			temp2 = (lives % 10) + 0x30;
			one_vram_buffer(temp1, NTADR_A(18,17));
			one_vram_buffer(temp2, NTADR_A(19,17));
			set_scroll_x(0);
			music_stop();
		}
		
		
		
		while(game_mode == MODE_GAME_OVER){
			ppu_wait_nmi();
			oam_clear();
			
			clear_vram_buffer(); 
			
			multi_vram_buffer_horz(DEAD_TEXT, sizeof(DEAD_TEXT), NTADR_A(12,14));
			
			set_scroll_x(0);
			
			music_stop();
		}
		
	}
}

void reset_special(void){
	for(ind=0;ind<10;ind++)
		player_special_order[ind]=0;
}

void reset_ind(void){
	for(ind=0;ind<10;ind++)
		player_order[ind]=0;
}

void load_title(void){
	pal_bg(palette_title);
	pal_spr(palette_sp);
	vram_adr(NAMETABLE_A);
	vram_unrle(title);
	game_mode = MODE_TITLE;
}


void load_room_1(void){
	set_data_pointer(Level1_0);
	set_mt_pointer(metatiles1);
	for(y=0; ;y+=0x20){
		for(x=0; ;x+=0x20){
			clear_vram_buffer(); 
			address = get_ppu_addr(0, x, y);
			index = (y & 0xf0) + (x >> 4);
			buffer_4_mt(address, index); 
			flush_vram_update_nmi();
			if (x == 0xe0) break;
		}
		if (y == 0xe0) break;
	}
	
	set_vram_update(NULL); 
	
	
	memcpy (c_map, Level1_0, 240);
	
	sprite_obj_init();
	BoxGuy1.x = 0x4000;
	BoxGuy1.y = 0xc400;
	BoxGuy1.vel_x = 0;
	BoxGuy1.vel_y = 0;
	
	map_loaded = 0;
}



void load_room(void){
	offset = Level_offsets[level];
	
	set_data_pointer(Levels_list[offset]);
	set_mt_pointer(metatiles1);
	for(y=0; ;y+=0x20){ 
		for(x=0; ;x+=0x20){
			clear_vram_buffer(); 
			address = get_ppu_addr(0, x, y);
			index = (y & 0xf0) + (x >> 4);
			buffer_4_mt(address, index); 
			flush_vram_update_nmi();
			if (x == 0xe0) break;
		}
		if (y == 0xe0) break;
	}
	
	
	++offset;
	
	
	set_data_pointer(Levels_list[offset]);
	for(y=0; ;y+=0x20){ 
		x = 0;
		clear_vram_buffer(); 
		address = get_ppu_addr(1, x, y);
		index = (y & 0xf0);
		buffer_4_mt(address, index);
		flush_vram_update_nmi();
		if (y == 0xe0) break;
	}
	
	clear_vram_buffer();
	
	--offset;
	
	memcpy (c_map, Levels_list[offset], 240);
	
	
	sprite_obj_init();
	BoxGuy1.x = 0x4000;
	BoxGuy1.y = 0xc400;
	BoxGuy1.vel_x = 0;
	BoxGuy1.vel_y = 0;
	
	map_loaded = 0;
}




void draw_sprites(void){
	
	oam_clear();
	
	temp_x = high_byte(BoxGuy1.x);
	if(temp_x > 0xfc) temp_x = 1;
	if(temp_x == 0) temp_x = 1;
	// draw 1 hero
	if(direction == LEFT) {
		if(!(pad1 &PAD_A))
			oam_meta_spr(temp_x, high_byte(BoxGuy1.y), RoundSprL);
		else
			oam_meta_spr(temp_x, high_byte(BoxGuy1.y), RoundSprAL);
	}
	else{
		if(!(pad1 &PAD_A))
			oam_meta_spr(temp_x, high_byte(BoxGuy1.y), RoundSprR);
		else
			oam_meta_spr(temp_x, high_byte(BoxGuy1.y), RoundSprAR);
	}
	for(index = 0; index < MAX_COINS; ++index){
		temp_y = coin_y[index];
		if(temp_y == TURN_OFF) continue;
		if(get_frame_count() & 8) ++temp_y; 
		if(!coin_active[index]) continue;
		temp_x = coin_x[index];
		if(temp_x > 0xf0) continue;
		if(temp_y < 0xf0) {
			if(coin_type[index] == COIN_REG){
				oam_meta_spr(temp_x, temp_y, CoinSpr);
			}
			else {
				oam_meta_spr(temp_x, temp_y, BigCoinSpr);
			}
			
		}
	}

	offset = get_frame_count() & 3;
	offset = offset << 4; 
	for(index = 0; index < MAX_ENEMY; ++index){
		index2 = shuffle_array[offset];
		++offset;
		temp_y = enemy_y[index2];
		if(temp_y == TURN_OFF) continue;
		if(!enemy_active[index2]) continue;
		temp_x = enemy_x[index2];
		if(temp_x == 0) temp_x = 1; 
		if(temp_x > 0xf0) continue;
		if(temp_y < 0xf0) {
			oam_meta_spr(temp_x, temp_y, enemy_anim[index2]);
		}
	}
	
	
	//last, draw coin in upper left
	oam_meta_spr(0x10, 0x0f, CoinHud);
	temp1 = (lives / 10) + 0xf0;
	temp2 = (lives % 10) + 0xf0;
	oam_spr(0x20, 0x17, temp1, 1);
	oam_spr(0x28, 0x17, temp2, 1);
}
	
unsigned char check_order(){
	for(index=0;index<MAX_COINS;++index)
	{
		if (player_order[index]!=1)
		{
			return 0;
		}
		
	}
	return 1;
}

unsigned char check_special_order(){
for(index=0;index<MAX_COINS;++index)
	{
		if (player_special_order[index]!=1)
		{
			return 0;
		}
		
	}
	return 1;
	

}
	

void movement(void){
	
// handle x

	old_x = BoxGuy1.x;
	
	if(pad1 & PAD_LEFT){
		direction = LEFT;
		if(BoxGuy1.x <= 0x100) {
			BoxGuy1.vel_x = 0;
			BoxGuy1.x = 0x100;
		}
		else if(BoxGuy1.x < 0x400) { 
			BoxGuy1.vel_x = -0x100;
		}
		else {
			BoxGuy1.vel_x -= ACCEL;
			if(BoxGuy1.vel_x < -MAX_SPEED) BoxGuy1.vel_x = -MAX_SPEED;
		}
	}
	else if (pad1 & PAD_RIGHT){
		
		direction = RIGHT;

		BoxGuy1.vel_x += ACCEL;
		if(BoxGuy1.vel_x > MAX_SPEED) BoxGuy1.vel_x = MAX_SPEED;
	}
	else { // nothing pressed
		if(BoxGuy1.vel_x >= 0x100) BoxGuy1.vel_x -= ACCEL;
		else if(BoxGuy1.vel_x < -0x100) BoxGuy1.vel_x += ACCEL;
		else BoxGuy1.vel_x = 0;
	}
	
	BoxGuy1.x += BoxGuy1.vel_x;
	
	if(BoxGuy1.x > 0xf800) { 
		BoxGuy1.x = 0x100;
		BoxGuy1.vel_x = 0;
	} 
	
	L_R_switch = 1; 
	
	Generic.x = high_byte(BoxGuy1.x); 
	Generic.y = high_byte(BoxGuy1.y);
	Generic.width = HERO_WIDTH;
	Generic.height = HERO_HEIGHT;
	bg_collision();
	if(collision_R && collision_L){ 
		BoxGuy1.x = old_x;
		BoxGuy1.vel_x = 0;
	}
	else if(collision_L) {
		BoxGuy1.vel_x = 0;
		high_byte(BoxGuy1.x) = high_byte(BoxGuy1.x) - eject_L;
		
	}
	else if(collision_R) {
		BoxGuy1.vel_x = 0;
		high_byte(BoxGuy1.x) = high_byte(BoxGuy1.x) - eject_R;
	} 


	

	old_y = BoxGuy1.y;
	
	if(pad1 & PAD_UP){
		direction = UP;
		if(BoxGuy1.y <= 0x100) {
			BoxGuy1.vel_y = 0;
			BoxGuy1.y = 0x100;
		}
		else if(BoxGuy1.y < 0x5fff) { 
			BoxGuy1.vel_y = 0;
		}
		else {
			BoxGuy1.vel_y -= ACCEL;
			if(BoxGuy1.vel_y < -MAX_SPEED) BoxGuy1.vel_y = -MAX_SPEED;
		}
	}
	else if (pad1 & PAD_DOWN){
		
		direction = DOWN;
		if(BoxGuy1.y > 0xc0f0) { 
		BoxGuy1.vel_y = 0;
		}
		else
			BoxGuy1.vel_y += ACCEL;
		if(BoxGuy1.vel_y > MAX_SPEED) BoxGuy1.vel_y = MAX_SPEED;
	}
	else { // nothing pressed
		if(BoxGuy1.vel_y >= 0x100) BoxGuy1.vel_y -= ACCEL;
		else if(BoxGuy1.vel_y < -0x100) BoxGuy1.vel_y += ACCEL;
		else BoxGuy1.vel_y = 0;
	}
	
	BoxGuy1.y += BoxGuy1.vel_y;
	
	if(BoxGuy1.y > 0xf800) { 
		BoxGuy1.y = 0x100;
		BoxGuy1.vel_y = 0;
	} 
	
	L_R_switch = 1; 
	
	Generic.x = high_byte(BoxGuy1.x); 
	Generic.y = high_byte(BoxGuy1.y);
	Generic.width = HERO_WIDTH;
	Generic.height = HERO_HEIGHT;
	bg_collision();
	if(collision_D && collision_U){ 
		BoxGuy1.y = old_y;
		BoxGuy1.vel_y = 0;
	}
	else if(collision_U) {
		BoxGuy1.vel_y = 0;
		high_byte(BoxGuy1.y) = high_byte(BoxGuy1.y) - eject_U;
		
	}
	else if(collision_D) {
		BoxGuy1.vel_y = 0;
		high_byte(BoxGuy1.y) = high_byte(BoxGuy1.y) - eject_D;
	} 

	
	Generic.y = high_byte(BoxGuy1.y); 
	bg_check_low();
	if(!collision_U) {
		if(pad1_new & PAD_UP) {
			BoxGuy1.vel_y = JUMP_VEL; 
		
		}
	
	}
	
	
	if((scroll_x & 0xff) < 4){
		if(!map_loaded){
			new_cmap();
			map_loaded = 1; 
		}
		
	}
	else{
		map_loaded = 0;
	}
	
	// scroll
	temp5 = BoxGuy1.x;
	if (BoxGuy1.x > MAX_RIGHT){
		temp1 = (BoxGuy1.x - MAX_RIGHT) >> 8;
		scroll_x += temp1;
		high_byte(BoxGuy1.x) = high_byte(BoxGuy1.x) - temp1;
	}

	if(scroll_x >= MAX_SCROLL) {
		scroll_x = MAX_SCROLL; 
		BoxGuy1.x = temp5; 
		if(high_byte(BoxGuy1.x) >= 0xf1) {
			BoxGuy1.x = 0xf100;
		}
	}
}	



void check_spr_objects(void){
	++enemy_frames;
	Generic2.x = high_byte(BoxGuy1.x);
	
	
	for(index = 0; index < MAX_COINS; ++index){
		coin_active[index] = 0; 
		if(coin_y[index] != TURN_OFF){
			high_byte(temp5) = coin_room[index];
			low_byte(temp5) = coin_actual_x[index];
			coin_active[index] = get_position();
			coin_x[index] = temp_x; 

		}

	}
	

	for(index = 0; index < MAX_ENEMY; ++index){
		enemy_active[index] = 0; 
		if(enemy_y[index] != TURN_OFF){
			high_byte(temp5) = enemy_room[index];
			low_byte(temp5) = enemy_actual_x[index];
			temp1 = enemy_active[index] = get_position();
			if(temp1 == 0) continue;
			enemy_x[index] = temp_x; 
			
			enemy_moves(); 
		}

	}

	
}



char get_position(void){
	
	
	temp5 -= scroll_x;
	temp_x = temp5 & 0xff;
	if(high_byte(temp5)) return 0;
	return 1;
}




void enemy_moves(void){
	if(enemy_type[index] == ENEMY_CHASE){
		//for bg collisions
		Generic.x = enemy_x[index];
		Generic.y = enemy_y[index] + 6; 
		Generic.width = 13;
		
		enemy_anim[index] = EnemyChaseSpr;
		if(enemy_frames & 1) return; 
		if(enemy_x[index] > Generic2.x){
			Generic.x -= 1;
			bg_collision_fast();
			if(collision_L) return;
			if(enemy_actual_x[index] == 0) --enemy_room[index];
			--enemy_actual_x[index];
		}
		else if(enemy_x[index] < Generic2.x){ 
			Generic.x += 1;
			bg_collision_fast();
			if(collision_R) return;
			++enemy_actual_x[index];
			if(enemy_actual_x[index] == 0) ++enemy_room[index];
		}
	}
	else if(enemy_type[index] == ENEMY_BOUNCE){
		temp1 = enemy_frames + (index << 3);
		if((temp1 & 0x3f) < 16){
			enemy_anim[index] = EnemyBounceSpr;
		}
		else if((temp1 & 0x3f) < 40){
			--enemy_y[index];
			enemy_anim[index] = EnemyBounceSpr2;
		}
		else {
			enemy_anim[index] = EnemyBounceSpr2;
			temp1 = enemy_y[index];
			Generic.x = enemy_x[index]; 
			Generic.y = enemy_y[index] - 1;
			Generic.width = 15;
			Generic.height = 15;
			bg_check_low();
			if(!collision_D){
				++enemy_y[index];
			}
		}
	}

}




void bg_collision_fast(void){
	
	collision_L = 0;
	collision_R = 0;
	
	if(Generic.y >= 0xf0) return;
	
	temp6 = temp5 = Generic.x + scroll_x; 
	temp1 = temp5 & 0xff; 
	temp2 = temp5 >> 8; 
	
	temp3 = Generic.y; 
	
	bg_collision_sub();
	
	if(collision & COL_ALL){ 
		++collision_L;
	}
	
	
	temp5 += Generic.width;
	temp1 = temp5 & 0xff; 
	temp2 = temp5 >> 8; 
	
	
	bg_collision_sub();
	
	if(collision & COL_ALL){ 
		++collision_R;
	}
}


void bg_collision(void){
	collision_L = 0;
	collision_R = 0;
	collision_U = 0;
	collision_D = 0;
	
	if(Generic.y >= 0xf0) return;
	
	temp6 = temp5 = Generic.x + scroll_x;
	temp1 = temp5 & 0xff;
	temp2 = temp5 >> 8; 
	
	eject_L = temp1 | 0xf0;
	
	temp3 = Generic.y; // y top
	
	eject_U = temp3 | 0xf0;
	
	if(L_R_switch) temp3 += 2; 
	
	bg_collision_sub();
	
	if(collision & COL_ALL){ 
		++collision_L;
		++collision_U;
	}
	
	
	temp5 += Generic.width;
	temp1 = temp5 & 0xff; 
	temp2 = temp5 >> 8;
	
	eject_R = (temp1 + 1) & 0x0f;
	
	
	bg_collision_sub();
	
	if(collision & COL_ALL){ 
		++collision_R;
		++collision_U;
	}
	
	
	
	
	
	
	temp3 = Generic.y + Generic.height; 
	if(L_R_switch) temp3 -= 2; 
	eject_D = (temp3 + 1) & 0x0f;
	if(temp3 >= 0xf0) return;
	
	bg_collision_sub();
	
	if(collision & COL_ALL){ 
		++collision_R;
	}
	if(collision & (COL_DOWN|COL_ALL)){ 
		++collision_D;
	}
	
	
	temp1 = temp6 & 0xff; 
	temp2 = temp6 >> 8; 
	
	

	bg_collision_sub();
	
	if(collision & COL_ALL){ 
		++collision_L;
	}
	if(collision & (COL_DOWN|COL_ALL)){ 
		++collision_D;
	}

	if((temp3 & 0x0f) > 3) collision_D = 0; 

}



void bg_collision_sub(void){
	coordinates = (temp1 >> 4) + (temp3 & 0xf0);
	
	map = temp2&1; // high byte
	if(!map){
		collision = c_map[coordinates];
	}
	else{
		collision = c_map2[coordinates];
	}
	
	collision = is_solid[collision];
}



void draw_screen_R(void){
	pseudo_scroll_x = scroll_x + 0x120;
	
	temp1 = pseudo_scroll_x >> 8;
	
	offset = Level_offsets[level];
	offset += temp1;
	
	set_data_pointer(Levels_list[offset]);
	nt = temp1 & 1;
	x = pseudo_scroll_x & 0xff;
	
	switch(scroll_count){
		case 0:
			address = get_ppu_addr(nt, x, 0);
			index = 0 + (x >> 4);
			buffer_4_mt(address, index); 
			
			address = get_ppu_addr(nt, x, 0x20);
			index = 0x20 + (x >> 4);
			buffer_4_mt(address, index); 
			break;
			
		case 1:
			address = get_ppu_addr(nt, x, 0x40);
			index = 0x40 + (x >> 4);
			buffer_4_mt(address, index); 
			
			address = get_ppu_addr(nt, x, 0x60);
			index = 0x60 + (x >> 4);
			buffer_4_mt(address, index); 
			break;
			
		case 2:
			address = get_ppu_addr(nt, x, 0x80);
			index = 0x80 + (x >> 4);
			buffer_4_mt(address, index); 
			address = get_ppu_addr(nt, x, 0xa0);
			index = 0xa0 + (x >> 4);
			buffer_4_mt(address, index); 
			break;
			
		default:
			address = get_ppu_addr(nt, x, 0xc0);
			index = 0xc0 + (x >> 4);
			buffer_4_mt(address, index);
			address = get_ppu_addr(nt, x, 0xe0);
			index = 0xe0 + (x >> 4);
			buffer_4_mt(address, index); 
	}


	++scroll_count;
	scroll_count &= 3; 
}




void new_cmap(void){
	
	room = ((scroll_x >> 8) +1); 
	offset = Level_offsets[level];
	offset += room;
	
	map = room & 1; 
	if(!map){
		memcpy (c_map, Levels_list[offset], 240);
	}
	else{
		memcpy (c_map2, Levels_list[offset], 240);
	}
}




void bg_check_low(void){

	collision_D = 0;
	
	temp5 = Generic.x + scroll_x;    
	temp1 = temp5 & 0xff;
	temp2 = temp5 >> 8; 
	
	temp3 = Generic.y + Generic.height + 1; 
	
	if(temp3 >= 0xf0) return;
	
	bg_collision_sub();
	
	if(collision & (COL_DOWN|COL_ALL)){ 
		++collision_D;
	}
	

	temp5 += Generic.width; //right
	temp1 = temp5 & 0xff; //low byte
	temp2 = temp5 >> 8; //high byte
	
	//temp3 is unchanged
	bg_collision_sub();
	
	if(collision & (COL_DOWN|COL_ALL)){ 
		++collision_D;
	}
	
	if((temp3 & 0x0f) > 3) collision_D = 0; 

}




void sprite_collisions(void){
	Generic.x = high_byte(BoxGuy1.x);
	Generic.y = high_byte(BoxGuy1.y);
	Generic.width = HERO_WIDTH;
	Generic.height = HERO_HEIGHT;
	for(index = 0; index < MAX_COINS; ++index){
		if(coin_active[index]){
			if(coin_type[index] == COIN_REG){
				Generic2.width = COIN_WIDTH;
				Generic2.height = COIN_HEIGHT;
			}
			else{
				Generic2.width = BIG_COIN;
				Generic2.height = BIG_COIN;
			}
			Generic2.x = coin_x[index];
			Generic2.y = coin_y[index];
			if(check_collision(&Generic, &Generic2)){
				coin_y[index] = TURN_OFF;
				if(index_list[level][lives%10]==index){
					player_order[lives%10]=1;
					sfx_play(SFX_DING,0);
				}
				else{
					player_order[lives%10]=0;
					sfx_play(SFX_DING,0);
				}
				if(special_list[level][lives%10]==index)
					player_special_order[lives%10]=1;
				else
					player_special_order[lives%10]=0;
				++lives;
				if(coin_type[index] == COIN_END) ++level_up;
			}
		}
	}

	Generic2.width = ENEMY_WIDTH;
	Generic2.height = ENEMY_HEIGHT;
	
	for(index = 0; index < MAX_ENEMY; ++index){
		if(enemy_active[index]){
			Generic2.x = enemy_x[index];
			Generic2.y = enemy_y[index];
			if(check_collision(&Generic, &Generic2)){
				enemy_y[index] = TURN_OFF;
				enemy_active[index] = 0;
				sfx_play(SFX_NOISE, 0);
				
				if(lives&&!(pad1&PAD_A)) {
					lives -= 1;
					if(lives > 0x80) lives = 0;
				}
				else if(pad1&PAD_A)
				{
					lives+=1;
				}
				else { // die
					++death;
				} 
			}
		}
	}
}



void sprite_obj_init(void){

	pointer = Coins_list[level];
	for(index = 0,index2 = 0;index < MAX_COINS; ++index){
		
		coin_x[index] = 0;

		temp1 = pointer[index2]; 
		coin_y[index] = temp1;
		
		if(temp1 == TURN_OFF) break;

		++index2;
		
		coin_active[index] = 0;

		
		temp1 = pointer[index2]; 
		coin_room[index] = temp1;
		
		++index2;
		
		temp1 = pointer[index2]; 
		coin_actual_x[index] = temp1;
		
		++index2;
		
		temp1 = pointer[index2]; 
		coin_type[index] = temp1;
		
		++index2;
	}
	
	for(++index;index < MAX_COINS; ++index){
		coin_y[index] = TURN_OFF;
	}
	
	
	

	pointer = Enemy_list[level];
	for(index = 0,index2 = 0;index < MAX_ENEMY; ++index){
		
		enemy_x[index] = 0;

		temp1 = pointer[index2]; 
		enemy_y[index] = temp1;
		
		if(temp1 == TURN_OFF) break;

		++index2;
		
		enemy_active[index] = 0;
		
		temp1 = pointer[index2]; 
		enemy_room[index] = temp1;
		
		++index2;
		
		temp1 = pointer[index2]; 
		enemy_actual_x[index] = temp1;
		
		++index2;
		
		temp1 = pointer[index2]; 
		enemy_type[index] = temp1;
		
		++index2;
	}
	
	for(++index;index < MAX_ENEMY; ++index){
		enemy_y[index] = TURN_OFF;
	}
}







