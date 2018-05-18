//Shooting.cpp:
//#include "stdafx.h"
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
