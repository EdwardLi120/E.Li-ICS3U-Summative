//main.cpp
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
	//allegro variables
	ALLEGRO_DISPLAY *display = NULL;
	ALLEGRO_TIMER *timer = NULL;
	ALLEGRO_BITMAP *imageCrosshair = NULL;
	ALLEGRO_EVENT_QUEUE *event_queue = NULL;

	//object variable
	Crosshair crosshair;
	Abm abm[ABM_COUNT]; //30 anti-ballstic missiles
	Enemy enemy[ENEMY_COUNT]; //20 enemies
	Mirv mirv[ENEMY_COUNT];

	int lives = 3;
	int curr_num_enemy = 0;  //num of enemies on screen
	int num_spawned = 0;

	srand(time(0));

	initAllegro(&display, &timer, &imageCrosshair, &event_queue);

	initCrosshair(&crosshair, imageCrosshair);

	initAbm(abm);

	initEnemy(enemy, mirv);
											    //or &crosshair?
	playerMovement(display, timer, imageCrosshair, event_queue, crosshair, abm, enemy, &curr_num_enemy, &num_spawned, mirv);


	//al_set_target_bitmap(image);

	//al_set_target_bitmap(al_get_backbuffer(display));


	return 0;
}

