//Movement.cpp:
//#include "stdafx.h"
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
