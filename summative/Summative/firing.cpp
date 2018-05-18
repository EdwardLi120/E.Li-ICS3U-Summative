//#include "stdafx.h"
#include <stdio.h>
#include <allegro5/allegro.h>
#include <allegro5/allegro_font.h>
#include <allegro5/allegro_ttf.h>
#include <allegro5/allegro_image.h>
#include <allegro5/allegro_native_dialog.h>
#include <allegro5/allegro_primitives.h>
#include "header.h"

void fire(struct playerData player, ALLEGRO_BITMAP *imageEnemy) {
	//if (missileFired) {  //missileFired function checks if is missile fired
	//al_clear_to_color(al_map_rgb(0, 0, 0));
	al_draw_filled_rectangle(50, 10, 10, 50, al_map_rgb(551, 255, 44));
	al_draw_bitmap(imageEnemy, 10, 100, 100);


		/*if (player.x < 300) {
			al_draw_filled_rectangle(100, 100, 100, 100, al_map_rgb(551, 255, 44));   //each enemy will have a pos; fire from enemy's pos
		}
		else if (player.x > 300 && player.x < 600) {
			al_draw_filled_rectangle(1, 100, 1, 100, al_map_rgb(551, 255, 44));
		}

		else if (player.x > 600) {
			al_draw_filled_rectangle(1, 100, 1, 100, al_map_rgb(551, 255, 44));
		}
	//}
	printf("Fired");  */
}

