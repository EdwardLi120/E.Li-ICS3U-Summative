//Enemies.h:
//#include "stdafx.h"
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
