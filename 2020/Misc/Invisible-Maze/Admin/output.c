#include <gb/gb.h>
#include <gb/drawing.h>
#include <gb/font.h>
#include <stdio.h>
#include <time.h>
#include <stdlib.h>
#include "image_data.c"
#include "image_map.c"
#define key "KRUHZ=\x03\t\x07!R\x04!0\x05\n\x05RX!\x04:!>\x05PX\x08?"

char fakeflag[49] = "flag{https://www.youtube.com/watch?v=dQw4w9WgXcQ}";

char k[30];

unsigned char backgroundcharacters[] = { 0xFF, 0x00, 0x80, 0x7F, 0x80, 0x7F, 0x80, 0x7F, 0x80, 0x7F, 0x80, 0x7F, 0x80, 0x7F, 0x80, 0x7F,
	0xFF, 0x00, 0x01, 0xFE, 0x03, 0xFC, 0x07, 0xF8, 0x0F, 0xF0, 0x1F, 0xE0, 0x3F, 0xC0, 0x7F, 0x80,
	0xFF, 0x00, 0xFE, 0x01, 0xFC, 0x03, 0xF8, 0x07, 0xF0, 0x0F, 0xE0, 0x1F, 0xC0, 0x3F, 0x80, 0x7F,
	0xFF, 0x00, 0x00, 0xFF, 0x00, 0xFF, 0x00, 0xFF, 0x00, 0xFF, 0x00, 0xFF, 0x00, 0xFF, 0x00, 0xFF,
	0xFF, 0x00, 0xFF, 0x01, 0xFD, 0x03, 0xF9, 0x07, 0xF1, 0x0F, 0xE1, 0x1F, 0xC1, 0x3F, 0x81, 0x7F,
	0x80, 0x7F, 0x81, 0x7E, 0x83, 0x7C, 0x87, 0x78, 0x8F, 0x70, 0x9F, 0x60, 0xBF, 0x40, 0xFF, 0x00,
	0xFF, 0x70, 0xFF, 0x98, 0xEF, 0xB8, 0xCF, 0xF8, 0xFF, 0x70, 0xFF, 0x00, 0xFF, 0x00, 0xFF, 0x01,
	0xFF, 0x00, 0xFE, 0x01, 0xFC, 0x03, 0xF8, 0x07, 0xF0, 0x0F, 0xE0, 0x1F, 0xC0, 0x3F, 0xFF, 0xFF
};

unsigned char spritetiles[] = { 255, 0, 255, 0, 255, 0, 255, 0 };

unsigned char bgmap[] = { 0, 2, 0, 2, 0, 2, 0, 2, 0, 2, 0, 2, 0, 2, 0, 2, 0, 2, 0, 2,
	1, 3, 1, 3, 1, 3, 1, 3, 1, 3, 1, 3, 1, 3, 1, 3, 1, 3, 1, 3
};

void printflag(UBYTE k1, UBYTE k2, int i)
{
	for (i = 0; i < 29; i++)
	{
		k[i] = (((key[i] + k1) ^ k2));
	}
	k[i] = 0;
	printf("Way to go! \n flg if u not noob: %s\n", k);

}

void beep(UBYTE counter)
{
	NR50_REG = 0xFF;
	NR51_REG = 0xFF;
	NR52_REG = 0x80;
	if (counter)
	{
		NR10_REG = 0x38 U;
		NR11_REG = 0x70 U;
		NR12_REG = 0xE0 U;
		NR13_REG = 0x0A U;
		NR14_REG = 0xC6 U;
		NR51_REG |= 0x11;
		delay(20);
	}
}

void milestone_beep(UBYTE counter)
{
	NR50_REG = 0xFF;
	NR51_REG = 0xFF;
	NR52_REG = 0x80;
	if (counter)
	{
		NR10_REG = 0x15;
		NR11_REG = 0x96;
		NR12_REG = 0x73;
		NR13_REG = 0xBB;
		NR14_REG = 0x85;
		delay(20);
	}
}

void main()
{
	UBYTE counter, x, y, i, k1, k2;
	x = 75;
	y = 50;
	k1 = 0;
	k2 = 0;
	font_init();

	set_bkg_data(0, 112, image_data);
	set_bkg_tiles(0, 0, 20, 18, image_map);
	SHOW_BKG;
	DISPLAY_ON;
	waitpad(J_START);

	gotogxy(7, 88);
	printf("Weclome! \n\n\n to the invisible maze \n Press Start to \n play. \n\n Place the flag \n on the right \n position to get the\n flag!");
	waitpad(J_START);

	disable_interrupts();
	DISPLAY_OFF;

	// load background
	set_bkg_data(0, 4, backgroundcharacters);
	for (counter = 0; counter <= 16; counter += 2)
		set_bkg_tiles(0, counter, 20, 2, bgmap);

	// load sprite
	SPRITES_8x8;
	set_sprite_data(0, 1, spritetiles);
	set_sprite_tile(0, 0);
	move_sprite(0, x, y);

	SHOW_BKG;
	SHOW_SPRITES;
	DISPLAY_ON;
	enable_interrupts();

	while (1)
	{
		for (counter = 0; counter < 9; counter++)
		{
			wait_vbl_done();
		}
		counter = joypad();

		if (counter & J_UP)
		{
			y--;
			beep(counter);
		}
		if (counter & J_DOWN)
		{
			y++;
			beep(counter);
		}
		if (counter & J_LEFT)
		{
			x--;
			beep(counter);
		}
		if (counter & J_RIGHT)
		{
			x++;
			beep(counter);
		}

		if (x == 6 && y == 8)
		{
			k1 = k1 + x;
			k2 = k2 + y;
			milestone_beep(counter);
		}

		if (x == 5 && y == 3)
		{
			k1 = k1 / x;
			k2 = k2 / y;
			milestone_beep(counter);
		}

		if (x == 12 && y == 5)
		{
			k1 = k1 + x;
			k2 = k2 + y;
			milestone_beep(counter);
		}

		if (x == 4 && y == 5)
		{
			k1 = k1 * x;
			k2 = k2 * y;
			milestone_beep(counter);
		}

		if (x == 15 && y == 10)
		{
			k1 = k1 - x;
			k2 = k2 - y;
			milestone_beep(counter);
		}

		if (k1 == 37 && k2 == 25)
		{
			printflag(k1, k2, i);
			set_sprite_tile(0, 0);
			break;
		}

		move_sprite(0, x, y);
	}
}

