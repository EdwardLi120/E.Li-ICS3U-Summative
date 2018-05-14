//Main.cpp:
// SPACE INVADERS.cpp : Defines the entry point for the console application.
//
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
 ALLEGRO_BITMAP *imageShip = NULL;
 ALLEGRO_BITMAP *imageEnemy = NULL;
 ALLEGRO_EVENT_QUEUE *event_queue = NULL;
 //object variable
 struct shipData ship;
 struct bulletData bullet[NUM_BULLETS];
 struct enemyData enemy[ROWS][COLS];
 initAllegro(&display, &timer, &imageShip, &imageEnemy, &event_queue);
 initShip(&ship);
 initBullet(bullet, NUM_BULLETS); //pass entire array of structs (don't need &)
 initEnemy(enemy);
 playerMovement(display, timer, imageShip, imageEnemy, event_queue, ship, bullet, enemy);


 //al_set_target_bitmap(image);
 //al_set_target_bitmap(al_get_backbuffer(display));

 return 0;
}
