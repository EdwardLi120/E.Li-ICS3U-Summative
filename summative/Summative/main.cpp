//#include "stdafx.h"
#include <stdio.h>
#include <allegro5/allegro.h>
#include <allegro5/allegro_font.h>
#include <allegro5/allegro_ttf.h>
#include <allegro5/allegro_image.h>
#include <allegro5/allegro_native_dialog.h>
#include <allegro5/allegro_primitives.h>
#include "header.h"
#include <time.h>
#include <stdlib.h>

int main(int argc, char **argv)
{

	ALLEGRO_DISPLAY *display = NULL;
	ALLEGRO_TIMER *timer = NULL;
	ALLEGRO_BITMAP *imageCrosshair = NULL;
	ALLEGRO_EVENT_QUEUE *event_queue = NULL;
	ALLEGRO_FONT * font;
	ALLEGRO_BITMAP *background = NULL;
	ALLEGRO_BITMAP *imageUfo = NULL;
	ALLEGRO_BITMAP *imageBomb[5] = { NULL };
	ALLEGRO_BITMAP *imageLauncher = NULL;
	ALLEGRO_BITMAP *ground = NULL;
	ALLEGRO_BITMAP *imageBase = NULL;

	Level level;
	Crosshair crosshair;
	Abm abm[ABM_COUNT];
	Explosion explosion[ABM_COUNT];
	Base base[6];

	//variables to be malloc'd
	Enemy ** enemy = NULL;
	Ufo * ufo = NULL;
	Bomb * bomb = NULL;

	int  colorMap[NUM_COLORS][3];
	int theme[COLORS_PER_THEME];

	oneTimeInit(&level);

	//malloc arrays
	enemy = (Enemy **)malloc(level.spawnLimit * sizeof(Enemy *));
	for (int i = 0; i < level.spawnLimit; i++) {
		enemy[i] = (Enemy *)malloc(SPLIT_COUNT * sizeof(Enemy));
	}

	ufo = (Ufo *)malloc(level.ufoSpawnLimit * sizeof(Ufo));
	bomb = (Bomb *)malloc(level.bombSpawnLimit * sizeof(Bomb));


	srand(time(0));

	initAllegro(&display, &timer, &imageCrosshair, &event_queue, &font, &background, &imageUfo, &level, imageBomb, &imageLauncher, &ground, &imageBase);

	initCrosshair(&crosshair, imageCrosshair);

	initLevel(&level);

	initAbm(abm, explosion);

	initEnemy(enemy, &level, ufo, bomb);

	initBase(base, 6);

	initColorMap(colorMap);

	generateTheme(theme);

	playerMovement(display, timer, imageCrosshair, event_queue, crosshair, abm, enemy, font, base, explosion, theme, colorMap, &level, background,
		imageUfo, ufo, imageBomb, bomb, imageLauncher, ground, imageBase);


	//al_set_target_bitmap(image);

	//al_set_target_bitmap(al_get_backbuffer(display));


	return 0;
}
