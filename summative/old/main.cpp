
// SPACE INVADERS.cpp : Defines the entry point for the console application.

//#include "stdafx.h"
#include <stdio.h>
#include <allegro5/allegro.h>
#include <allegro5/allegro_font.h>
#include <allegro5/allegro_ttf.h>
#include <allegro5/allegro_image.h>
#include <allegro5/allegro_native_dialog.h>
#include <allegro5/allegro_primitives.h>
#include "header.h"



int main(int argc, char **argv)
{
	//allegro variables
	ALLEGRO_DISPLAY *display = NULL;
	ALLEGRO_TIMER *timer = NULL;
	ALLEGRO_BITMAP *imageCrosshair= NULL;
	ALLEGRO_BITMAP *imageEnemy = NULL;
	ALLEGRO_EVENT_QUEUE *event_queue = NULL;

	//object variable
	struct playerData player;
	struct bulletData bullet[NUM_BULLETS];
	struct enemyData enemy[ROWS][COLS];
	struct brigade abm; //anti-ballstic missiles

	//silos 1-10 = brigade 1, 10-20 = brigade 2, 20-30 = brigade 3
	struct siloPos silo[30]; //1 silo for each missile



	initAllegro(&display, &timer, &imageCrosshair, &imageEnemy, &event_queue);

	initPlayer(&player);

	initAbm(&abm, silo);

	initEnemy(enemy);

	playerMovement(display, timer, imageCrosshair, imageEnemy, event_queue, &player, bullet, enemy, abm);





	//al_set_target_bitmap(image);

	//al_set_target_bitmap(al_get_backbuffer(display));


	return 0;
}

