//#include "stdafx.h"
#include <stdio.h>
#include <allegro5/allegro.h> // Include the allegro header file.
#include <allegro5/allegro_font.h>
#include <allegro5/allegro_ttf.h>
#include <allegro5/allegro_image.h>
#include <allegro5/allegro_native_dialog.h>
#include <allegro5/allegro_primitives.h>
#include "header.h"

int initAllegro(ALLEGRO_DISPLAY **display, ALLEGRO_TIMER **timer, ALLEGRO_BITMAP **imageCrosshair, ALLEGRO_BITMAP **imageEnemy, ALLEGRO_EVENT_QUEUE **event_queue) {

	if (!al_init()) {
		fprintf(stderr, "failed to initialize allegro!\n");
		return -1;
	}

	//create display
	*display = al_create_display(SCREEN_W, SCREEN_H);
	if (!(*display)) {
		fprintf(stderr, "failed to create display!\n");
		al_destroy_timer(*timer);
		return -1;
	}

	//create timer
	*timer = al_create_timer(1.0 / FPS);   //1/60 seconds per frame, i.e. 60 fps
	if (!(*timer)) {
		fprintf(stderr, "failed to create timer!\n");
		return -1;
	}

	//create event queue
	*event_queue = al_create_event_queue();
	if (!(*event_queue)) {
		fprintf(stderr, "failed to create event_queue!\n");
		al_destroy_bitmap(*imageCrosshair);
		al_destroy_display(*display);
		al_destroy_timer(*timer);
		return -1;
	}

	//install keyboard
	if (!al_install_keyboard()) {
		fprintf(stderr, "failed to initialize the keyboard!\n");
		return -1;
	}

	//install mouse
	if (!al_install_mouse()) {
		fprintf(stderr, "failed to initialize the mouse!\n");
		return -1;
	}

	if (!al_init_primitives_addon()) {
		al_show_native_message_box(*display, "Error", "Error", "Failed to initialize image addon!",
			nullptr, ALLEGRO_MESSAGEBOX_ERROR);
		return -1;
	}

	//initialize image addon
	if (!al_init_image_addon()) {
		al_show_native_message_box(*display, "Error", "Error", "Failed to initialize image addon!",
			nullptr, ALLEGRO_MESSAGEBOX_ERROR);
		return -1;
	}

	//create ship image
	*imageCrosshair = al_load_bitmap("crosshair.png");
	if (!imageCrosshair) {
		al_show_native_message_box(*display, "Error", "Error", "Failed to load image!",
			NULL, ALLEGRO_MESSAGEBOX_ERROR);
		al_destroy_display(*display);
		return 0;
	}

	//create enemy image
	*imageEnemy = al_load_bitmap("enemy.png");
	if (!imageEnemy) {
		al_show_native_message_box(*display, "Error", "Error", "Failed to load image!",
			NULL, ALLEGRO_MESSAGEBOX_ERROR);
		al_destroy_display(*display);
		return 0;
	}

	//register
	al_register_event_source(*event_queue, al_get_display_event_source(*display));
	al_register_event_source(*event_queue, al_get_timer_event_source(*timer));
	al_register_event_source(*event_queue, al_get_keyboard_event_source());
	al_register_event_source(*event_queue, al_get_mouse_event_source());

	al_clear_to_color(al_map_rgb(0, 0, 0));
	al_flip_display();
	al_start_timer(*timer);
}

void initPlayer(struct playerData * player) {
	player->lives = 3;
	player->x = 20;
	player->y = 20;
	player->score = 0;
}

void initAbm(struct brigade * abm, struct siloPos * silo) {
	int i;

	//init speed
	for (i = 0; i < 10; i++) {
		abm->left[i].speed = 5;
		abm->center[i].speed = 10;
		abm->right[i].speed = 5;
	}

	//init launch point of missile batteries
	for (i = 0; i < 10; i++) {
		abm->left[i].x = 267;
		abm->left[i].y = 100;
		abm->center[i].x = 534;
		abm->center[i].y = 100;
		abm->right[i].x = 800;
		abm->right[i].y = 100;
	}

}
void initBullet(struct bulletData * bullet, int size) {
	for (int i = 0; i < size; i++) {
		bullet[i].ID = BULLET;
		bullet[i].speed = 10;
		bullet[i].fired = false;
		bullet[i].x = 0;
		bullet[i].y = 0;
	}
}

void initEnemy(struct enemyData enemy[][COLS]) {
	int i, j, x, y;

	for (i = 0, x = 0; i < ROWS; i++, x+=50) {
		for (j = 0, y=0; j < COLS; j++, y+=50) {
			enemy[i][j].speed = 5;
			enemy[i][j].alive = true;
			enemy[i][j].x = x;
			enemy[i][j].y = y;
		}
	}
}



	/*
	int i, j, x, y;
	int count = 0; //0 to 8

	for (i = 0, x = 0; i < NUM_ENEMIES_X; i++, x += 50) {
		enemy[i].ID = ENEMY;
		enemy[i].speed = 5;
		enemy[i].alive = true;
		enemy[i].x = x;
	}

	for (i = 0, y = 0; i < NUM_ENEMIES_Y; i++, y += 50) {
		enemy[i].y = y;
	}
}

*/

