//fire.cpp
//#include "stdafx.h"
#include <stdio.h>
#include <math.h>
#include <allegro5/allegro.h> // Include the allegro header file.
#include <allegro5/allegro_font.h>
#include <allegro5/allegro_ttf.h>
#include <allegro5/allegro_image.h>
#include <allegro5/allegro_native_dialog.h>
#include <allegro5/allegro_primitives.h>
#include "header.h"
#include <time.h>
#include <stdlib.h>

/*void fire(Crosshair crosshair, struct abmData * abm) {

	for (int i = 0; i < 30; i++) {
		if (!abm[i].used) {  //only fire unused abm
			abm[i].dest_x = crosshair.target_x;
			abm[i].dest_y = crosshair.target_y;
			abm[i].launch_x = 100;
			abm[i].launch_y = 700;
			abm[i].launched = true;
			abm[i].used = false;
			break;
		}
	}

	drawAbm(abm, crosshair);
}*/


void fire(Abm * abm, Crosshair crosshair) {
	int i;
	bool closestLaunchSuccess = false;
	bool launchSuccess = false; //if any 1 abm is fired upon mouseclick, only for diagnosis

	if(crosshair.target_x <= 300) {
		for (i = 0; i < 10; i++) {
			if (!abm[i].launched && !abm[i].arrived) {
				abm[i].x_pos = abm[i].launch_x;
				abm[i].y_pos = abm[i].launch_y;
				abm[i].dest_x = crosshair.target_x;
				abm[i].dest_y = crosshair.target_y;
				abm[i].launched = true;
				closestLaunchSuccess = true;
				launchSuccess = true;
				calcIncrement(&(abm[i]));
				printf("Dest: (%d, %d) ", abm[i].dest_x, abm[i].dest_y);
				break;
			}
		}
	}

	else if(crosshair.target_y > 300 && crosshair.x <= 600) {
		for (i = 10; i < 20; i++) {
			if (!abm[i].launched && !abm[i].arrived) {
				abm[i].x_pos = abm[i].launch_x;
				abm[i].y_pos = abm[i].launch_y;
				abm[i].dest_x = crosshair.target_x;
				abm[i].dest_y = crosshair.target_y;
				abm[i].launched = true;
				closestLaunchSuccess = true;
				launchSuccess = true;
				calcIncrement(&(abm[i]));
				printf("Dest: (%d, %d) ", abm[i].dest_x, abm[i].dest_y);
				break;
			}
		}
	}

	else if (crosshair.target_x > 600) {
		for (i = 20; i < 30; i++) {
			if (!abm[i].launched && !abm[i].arrived) {
				abm[i].x_pos = abm[i].launch_x;
				abm[i].y_pos = abm[i].launch_y;
				abm[i].dest_x = crosshair.target_x;
				abm[i].dest_y = crosshair.target_y;
				abm[i].launched = true;
				closestLaunchSuccess = true;
				launchSuccess = true;
				calcIncrement(&(abm[i]));
				printf("Dest: (%d, %d) ", abm[i].dest_x, abm[i].dest_y);
				break;
			}
		}
	}


	//if cannot fire from nearest battery
	if (!closestLaunchSuccess) {
		for (i = 0; i < ABM_COUNT; i++) {
			if (!abm[i].launched && !abm[i].arrived) {
				abm[i].x_pos = abm[i].launch_x;
				abm[i].y_pos = abm[i].launch_y;
				abm[i].dest_x = crosshair.target_x;
				abm[i].dest_y = crosshair.target_y;
				abm[i].launched = true;
				launchSuccess = true;
				calcIncrement(&(abm[i]));
				printf("Dest: (%d, %d) ", abm[i].dest_x, abm[i].dest_y);
				break;
			}
		}
	}

	if (!launchSuccess) {
		printf("Out of ABMs!");
	}
}


void calcIncrement(Abm * abm) {
		abm->dx = fabs(abm->dest_x - abm->launch_x);
		abm->dy = fabs(abm->dest_y - abm->launch_y);

		if (abm->dx >= abm->dy) {
			abm->step = abm->dx;
		}
		else {
			abm->step = abm->dy;
		}

		abm->x_inc = abm->dx / abm->step;
		abm->y_inc = abm->dy / abm->step;
}

void drawAbm(struct abmData * abm) {
	al_draw_filled_rectangle(10, 830, 100, 900, al_map_rgb(255, 255, 255));   //(55, 830)
	al_draw_filled_rectangle(400, 830, 490, 900, al_map_rgb(255, 255, 255));  //(445, 830)
	al_draw_filled_rectangle(800, 830, 890, 900, al_map_rgb(255, 255, 255));  //(845, 830)

	for (int i = 0; i < ABM_COUNT; i++) {
		if (abm[i].launched) {
			al_draw_filled_rectangle(abm[i].x_pos-3, abm[i].y_pos-3, abm[i].x_pos+3, abm[i].y_pos+3, al_map_rgb(255, 255, 255));
			al_draw_line(abm[i].x_pos, abm[i].y_pos+3, abm[i].launch_x, abm[i].launch_y, al_map_rgb(0, 0, 255), 4);
		}
	}
}


//update in buffer
void updateAbm(struct abmData * abm) {
	int i;

	for (i = 0; i < ABM_COUNT; i++) {

		if (abm[i].launched) {  //only update launched & alive abm's

			abm[i].y_pos -= 5 * abm[i].y_inc;

			if (abm[i].dest_x > abm[i].launch_x) {
				abm[i].x_pos += 5 *abm[i].x_inc;
				abm[i].num_increment += 5;
			}
			else if (abm[i].dest_x < abm[i].launch_x) {
				abm[i].x_pos -= 5 * abm[i].x_inc;
				abm[i].num_increment += 5;
			}
		}
	}
}


void print_arrive(Abm * abm, int *count) {
	for (int i = 0; i < ABM_COUNT; i++) {
		if (abm[i].arrived) {
			printf("i: %d, Count: %d, step %f, incr %d, launch %d\n", i, *count, abm[i].step, abm[i].num_increment, abm[i].launched);
		}

	}

	(*count)++;
}
