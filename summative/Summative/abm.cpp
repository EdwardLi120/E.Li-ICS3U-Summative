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
#include <allegro5/allegro_audio.h>
#include <allegro5/allegro_acodec.h>


void fire(Abm * abm, Crosshair crosshair, Level * level, Audio * audio) {
	int i;
	bool closestLaunchSuccess = false;

	if (crosshair.target.x <= 300) {
		for (i = 0; i < 10; i++) {
			if (!abm[i].launched && !abm[i].arrived) {
				abm[i].pos.x = abm[i].launch.x;
				abm[i].pos.y = abm[i].launch.y;
				abm[i].dest.x = crosshair.target.x;
				abm[i].dest.y = crosshair.target.y;
				abm[i].launched = true;
				closestLaunchSuccess = true;
				(level->abmLeft)--;
				(level->batteryAbmLeft[0])--;
				calcAbmInc(&(abm[i]));
				al_play_sample(audio->missileLaunch, 0.5, 0.0, 1.0, ALLEGRO_PLAYMODE_ONCE, NULL);
				break;
			}
		}
	}

	else if (crosshair.target.x > 300 && crosshair.pos.x <= 600) {
		for (i = 10; i < 20; i++) {
			if (!abm[i].launched && !abm[i].arrived) {
				abm[i].pos.x = abm[i].launch.x;
				abm[i].pos.y = abm[i].launch.y;
				abm[i].dest.x = crosshair.target.x;
				abm[i].dest.y = crosshair.target.y;
				abm[i].launched = true;
				closestLaunchSuccess = true;
				(level->abmLeft)--;
				(level->batteryAbmLeft[1])--;
				calcAbmInc(&(abm[i]));
				al_play_sample(audio->missileLaunch, 0.5, 0.0, 1.0, ALLEGRO_PLAYMODE_ONCE, NULL);
				break;
			}
		}
	}

	else if (crosshair.target.x > 600) {
		for (i = 20; i < 30; i++) {
			if (!abm[i].launched && !abm[i].arrived) {
				abm[i].pos.x = abm[i].launch.x;
				abm[i].pos.y = abm[i].launch.y;
				abm[i].dest.x = crosshair.target.x;
				abm[i].dest.y = crosshair.target.y;
				abm[i].launched = true;
				closestLaunchSuccess = true;
				(level->abmLeft)--;
				(level->batteryAbmLeft[2])--;
				calcAbmInc(&(abm[i]));
				al_play_sample(audio->missileLaunch, 0.5, 0.0, 1.0, ALLEGRO_PLAYMODE_ONCE, NULL);
				break;
			}
		}
	}


	//if cannot fire from nearest battery
	if (!closestLaunchSuccess) {
		for (i = 0; i < ABM_COUNT; i++) {
			if (!abm[i].launched && !abm[i].arrived) {
				abm[i].pos.x = abm[i].launch.x;
				abm[i].pos.y = abm[i].launch.y;
				abm[i].dest.x = crosshair.target.x;
				abm[i].dest.y = crosshair.target.y;
				abm[i].launched = true;
				(level->abmLeft)--;

				if (i < 10)
					(level->batteryAbmLeft[0])--;

				else if (i >= 10 && i < 20)
					(level->batteryAbmLeft[1])--;

				else if (i >= 20)
					(level->batteryAbmLeft[2])--;

				calcAbmInc(&(abm[i]));
				al_play_sample(audio->missileLaunch, 0.5, 0.0, 1.0, ALLEGRO_PLAYMODE_ONCE, NULL);
				break;
			}
		}
	}
}


void calcAbmInc(Abm * abm) {
	abm->dx = fabs(abm->dest.x - abm->launch.x);
	abm->dy = fabs(abm->dest.y - abm->launch.y);

	if (abm->dx >= abm->dy)
		abm->step = abm->dx;

	else
		abm->step = abm->dy;

	abm->inc.x = abm->dx / abm->step;
	abm->inc.y = abm->dy / abm->step;
}

void drawAbm(struct abmData * abm, int abmColour, int colorMap[][3]) {
	int r, g, b;

	r = rand() % 255 + 1;
	g = rand() % 255 + 1;
	b = rand() % 255 + 1;

	for (int i = 0; i < ABM_COUNT; i++) {
		if (abm[i].launched) {

			al_draw_filled_rectangle(abm[i].pos.x - 3, abm[i].pos.y - 3, abm[i].pos.x + 3, abm[i].pos.y + 3, al_map_rgb(colorMap[abmColour][R], colorMap[abmColour][G], colorMap[abmColour][B]));
			al_draw_line(abm[i].pos.x, abm[i].pos.y + 3, abm[i].launch.x, abm[i].launch.y, al_map_rgb(colorMap[abmColour][R], colorMap[abmColour][G], colorMap[abmColour][B]), 4);

			//hitmarkers
			al_draw_line(abm[i].dest.x - 7, abm[i].dest.y + 7, abm[i].dest.x + 7, abm[i].dest.y - 7, al_map_rgb(r, g, b), 3);
			al_draw_line(abm[i].dest.x - 7, abm[i].dest.y - 7, abm[i].dest.x + 7, abm[i].dest.y + 7, al_map_rgb(r, g, b), 3);
		}
	}
}


//update in buffer
void updateAbm(struct abmData * abm) {
	int i;

	for (i = 0; i < ABM_COUNT; i++) {

		if (abm[i].launched) {  //only update launched & alive abm's

			if (abm[i].dest.x > abm[i].launch.x) {
				abm[i].pos.x += abm[i].speed * abm[i].inc.x;
				//abm[i].num_increment += 10;
			}
			else if (abm[i].dest.x < abm[i].launch.x) {
				abm[i].pos.x -= abm[i].speed * abm[i].inc.x;
				//abm[i].num_increment += 10;
			}

			abm[i].pos.y -= abm[i].speed * abm[i].inc.y;
			abm[i].num_increment += abm[i].speed;
		}
	}
}


void abmArrival(Abm * abm, Explosion * explosion) {
	for (int i = 0; i < ABM_COUNT; i++) {
		if (abm[i].launched) {
			if (abm[i].num_increment > abm[i].step) {
				abm[i].launched = false;
				abm[i].arrived = true;
				explosion[i].ongoing = true;
				explosion[i].center.x = abm[i].dest.x;
				explosion[i].center.y = abm[i].dest.y;
			}
		}
	}
}


void drawExplosion(Abm * abm, Explosion * explosion, int colorMap[][3]) {

	int palette[7][3] = { { 255, 0, 0 },{ 0, 255, 0 },{ 0, 0, 255 },{ 128, 128, 128 },{ 248, 6, 248 },{ 0, 255, 255 } };

	int color = rand() % NUM_COLORS;

	for (int i = 0; i < ABM_COUNT; i++) {
		if (explosion[i].ongoing) {

			//printf("Destination: (%d, %d): arrive: %d\n", abm[i].dest.x, abm[i].dest.y, abm[i].arrived);
			if (explosion[i].radius >= 40 && !explosion[i].expandedRadius)
				explosion[i].increaseRadius = false;

			else if (explosion[i].radius >= 80 && explosion[i].expandedRadius)
				explosion[i].increaseRadius = false;


			if (explosion[i].increaseRadius)
				explosion[i].radius += 1;


			else if (!explosion[i].increaseRadius)
				explosion[i].radius -= 1;


			al_draw_filled_circle(explosion[i].center.x, explosion[i].center.y, explosion[i].radius, al_map_rgb(palette[color][0], palette[color][1], palette[color][2]));

			//calculate bounds of explosion
			explosion[i].topLeft.x = explosion[i].center.x - explosion[i].radius;
			explosion[i].topLeft.y = explosion[i].center.y - explosion[i].radius;
			explosion[i].topRight.x = explosion[i].center.x + explosion[i].radius;
			explosion[i].topRight.y = explosion[i].center.y - explosion[i].radius;
			explosion[i].bottomLeft.x = explosion[i].center.x - explosion[i].radius;
			explosion[i].bottomLeft.y = explosion[i].center.y + explosion[i].radius;

			if (explosion[i].radius < 0) {
				explosion[i].ongoing = false;
			}
		}
	}
}
