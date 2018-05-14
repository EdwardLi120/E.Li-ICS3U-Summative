//globals
const float FPS = 60;
const int SCREEN_W = 640;
const int SCREEN_H = 480;
const int BOUNCER_SIZE = 32;
const int NUM_BULLETS = 100;
const int ROWS = 5;   //rows of enemies
const int COLS = 3;  //columns of enemies
const int NUM_ENEMIES_TOTAL = 8;
enum KEYS {
 KEY_UP, KEY_DOWN, KEY_LEFT, KEY_RIGHT, KEY_SPACE  //by default member 1 = 0, member 2 = 1, member 3 = 2, member 4 = 3...
};
enum ID {PLAYER, BULLET, ENEMY};
struct shipData {
 int ID;
 float x;  //x-coordinate
 float y;  //y-coordinate
 int lives;
 int speed;
 int boundx;
 int boundy;
 int score;
};
struct bulletData {
 int ID;
 float x;
 float y;
 bool fired;  //only bullets fired will move
 int speed;
};
struct enemyData {
 int ID;
 float x;
 float y;
 bool alive;
 int speed;
 int boundx;
 int boundy;
};

//prototypes
int initAllegro(ALLEGRO_DISPLAY **display, ALLEGRO_TIMER **timer, ALLEGRO_BITMAP **imageShip, ALLEGRO_BITMAP **imageEnemy, ALLEGRO_EVENT_QUEUE **event_queue);
void initShip(struct shipData * ship);
void initBullet(struct bulletData * bullet, int size);
void initEnemy(struct enemyData enemy[][COLS]);
void playerMovement(ALLEGRO_DISPLAY *display, ALLEGRO_TIMER *timer, ALLEGRO_BITMAP *imageShip, ALLEGRO_BITMAP *imageEnemy, ALLEGRO_EVENT_QUEUE *event_queue, struct shipData ship, struct bulletData * bullet, struct enemyData enemy[][COLS]);
void drawShip(ALLEGRO_BITMAP *imageShip, struct shipData ship);
void drawBullet(struct bulletData * bullet, int size);
void drawEnemy(ALLEGRO_BITMAP *imageEnemy, struct enemyData enemy[][COLS]);
void startEnemy(struct bulletData * bullet, int size);
void updateEnemy(struct bulletData * bullet, int size);
void fireBullet(struct bulletData * bullet, int size, struct shipData ship, int shipWidth);
void updateBullet(struct bulletData * bullet, int size);



Main.cpp:
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


Movement.cpp:
#include "stdafx.h"
#include <stdio.h>
#include <allegro5/allegro.h> // Include the allegro header file.
#include <allegro5/allegro_font.h>
#include <allegro5/allegro_ttf.h>
#include <allegro5/allegro_image.h>
#include <allegro5/allegro_native_dialog.h>
#include <allegro5/allegro_primitives.h>
#include "header.h"

void playerMovement(ALLEGRO_DISPLAY *display, ALLEGRO_TIMER *timer, ALLEGRO_BITMAP *imageShip, ALLEGRO_BITMAP *imageEnemy, ALLEGRO_EVENT_QUEUE *event_queue, struct shipData ship, struct bulletData * bullet, struct enemyData enemy[][COLS]) {
 //ship.x = SCREEN_W / 2.0 - BOUNCER_SIZE / 2.0;
 //ship.y = SCREEN_H / 2.0 - BOUNCER_SIZE / 2.0;
 bool done = false;
 bool draw = true;
 //move key[5] to global variable?
 bool key[5] = { false, false, false, false, false };  //array with members KEY_UP, KEY_DOWN, KEY_LEFT, KEY_RIGHT; each member is true or false
 int shipHeight = al_get_bitmap_height(imageShip);
 int shipWidth = al_get_bitmap_width(imageShip);

 while (!done) {
  ALLEGRO_EVENT ev;
  al_wait_for_event(event_queue, &ev);
  if (ev.type == ALLEGRO_EVENT_TIMER) {  //update every 1/60 of a second
   if (key[KEY_UP] && ship.y >= 4.0) {  //same as if key[0] == true; ALLEGRO_KEY_UP
    ship.y -= 4.0;  //substraction to move up
   }
   if (key[KEY_DOWN] && ship.y <= SCREEN_H - shipHeight - 4.0) { //same as key[1]
    ship.y += 4.0;   //addition to move down
   }
   if (key[KEY_LEFT] && ship.x >= 4.0) { //same as key[2]
    ship.x -= 4.0;  //substraction to move left
   }
   if (key[KEY_RIGHT] && ship.x <= SCREEN_W - shipWidth - 4.0) { //same as key[3]
    ship.x += 4.0;  //addition to move right
   }
   updateBullet(bullet, NUM_BULLETS);
   draw = true;  //update image position every 1/60 of a second (when timer goes off)
  }
  else if (ev.type == ALLEGRO_EVENT_DISPLAY_CLOSE) {
   break;
  }
  //if key is being pressed
  else if (ev.type == ALLEGRO_EVENT_KEY_DOWN) {
   switch (ev.keyboard.keycode) {
   case ALLEGRO_KEY_UP:
    key[KEY_UP] = true;
    break;
   case ALLEGRO_KEY_DOWN:
    key[KEY_DOWN] = true;
    break;
   case ALLEGRO_KEY_LEFT:
    key[KEY_LEFT] = true;
    break;
   case ALLEGRO_KEY_RIGHT:
    key[KEY_RIGHT] = true;
    break;
   case ALLEGRO_KEY_SPACE:
    key[KEY_SPACE] = true;
     fireBullet(bullet, NUM_BULLETS, ship, shipWidth);
    break;
   }
  }
  //if key is released
  else if (ev.type == ALLEGRO_EVENT_KEY_UP) {
   switch (ev.keyboard.keycode) {
   case ALLEGRO_KEY_UP:
    key[KEY_UP] = false;
    break;
   case ALLEGRO_KEY_DOWN:
    key[KEY_DOWN] = false;
    break;
   case ALLEGRO_KEY_LEFT:
    key[KEY_LEFT] = false;
    break;
   case ALLEGRO_KEY_RIGHT:
    key[KEY_RIGHT] = false;
    break;
   case ALLEGRO_KEY_SPACE:
    key[KEY_SPACE] = false;
    break;
   case ALLEGRO_KEY_ESCAPE:
    done = true;
    break;
   }
  }
  if (draw && al_is_event_queue_empty(event_queue)) {
   draw = false;
   al_clear_to_color(al_map_rgb(0, 0, 0));  //clear screen to black to create illusion of animation; draw & clear screen, draw & clear screen...
   drawShip(imageShip, ship);
   drawBullet(bullet, NUM_BULLETS);
   drawEnemy(imageEnemy, enemy);

   al_flip_display();
  }
 }
 al_destroy_bitmap(imageShip);
 al_destroy_timer(timer);
 al_destroy_display(display);
 al_destroy_event_queue(event_queue);
}
void drawShip(ALLEGRO_BITMAP *imageShip, struct shipData ship) {
 al_draw_bitmap(imageShip, ship.x, ship.y, 0);
}


Initialization.h:
#include "stdafx.h"
#include <stdio.h>
#include <allegro5/allegro.h> // Include the allegro header file.
#include <allegro5/allegro_font.h>
#include <allegro5/allegro_ttf.h>
#include <allegro5/allegro_image.h>
#include <allegro5/allegro_native_dialog.h>
#include <allegro5/allegro_primitives.h>
#include "header.h"
int initAllegro(ALLEGRO_DISPLAY **display, ALLEGRO_TIMER **timer, ALLEGRO_BITMAP **imageShip, ALLEGRO_BITMAP **imageEnemy, ALLEGRO_EVENT_QUEUE **event_queue) {
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
  al_destroy_bitmap(*imageShip);
  al_destroy_display(*display);
  al_destroy_timer(*timer);
  return -1;
 }
 //install keyboard
 if (!al_install_keyboard()) {
  fprintf(stderr, "failed to initialize the keyboard!\n");
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
 *imageShip = al_load_bitmap("ship.png");
 if (!imageShip) {
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
 al_clear_to_color(al_map_rgb(0, 0, 0));
 al_flip_display();
 al_start_timer(*timer);
}
void initShip(struct shipData * ship) {
 ship->ID = PLAYER;
 ship->lives = 3;
 ship->x = 20;
 ship->y = 20;
 ship->speed = 7;
 ship->boundx = 6;
 ship->boundy = 7;
 ship->score = 0;
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



Shooting.cpp:
#include "stdafx.h"
#include <stdio.h>
#include <allegro5/allegro.h> // Include the allegro header file.
#include <allegro5/allegro_font.h>
#include <allegro5/allegro_ttf.h>
#include <allegro5/allegro_image.h>
#include <allegro5/allegro_native_dialog.h>
#include <allegro5/allegro_primitives.h>
#include "header.h"
void drawBullet(struct bulletData * bullet, int size) {
 for (int i = 0; i < size; i++) {
  if (bullet[i].fired)
   al_draw_filled_rectangle(bullet[i].x + 3, bullet[i].y + 6, bullet[i].x - 3, bullet[i].y - 6, al_map_rgb(551, 255, 44));
 }
}
void fireBullet(struct bulletData * bullet, int size, struct shipData ship, int shipWidth) {
 for (int i = 0; i < size; i++) {
  if (!bullet[i].fired) {
   bullet[i].x = ship.x + shipWidth / 2;
   bullet[i].y = ship.y - 5;
   bullet[i].fired = true; //won't be fired again until bullet dead ;
   break; //only fire 1 bullet at a time
  }
 }
}
void updateBullet(struct bulletData * bullet, int size) {
 for (int i = 0; i < size; i++) {
  if (bullet[i].fired) {
   bullet[i].y -= bullet[i].speed;
   if (bullet[i].x > SCREEN_H) {
    bullet[i].fired = false;
   }
  }
 }
}


Enemies.h:
#include "stdafx.h"
#include <stdio.h>
#include <allegro5/allegro.h> // Include the allegro header file.
#include <allegro5/allegro_font.h>
#include <allegro5/allegro_ttf.h>
#include <allegro5/allegro_image.h>
#include <allegro5/allegro_native_dialog.h>
#include <allegro5/allegro_primitives.h>
#include "header.h"
void drawEnemy(ALLEGRO_BITMAP *imageEnemy, struct enemyData enemy[][COLS]) {
 for (int i = 0; i < ROWS; i++) {
  for (int j = 0; j < COLS; j++) {
   if (enemy[i][j].alive) {
    al_draw_bitmap(imageEnemy, enemy[i][j].x, enemy[i][j].y, 0);
   }
  }
 }
}
