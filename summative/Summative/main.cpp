//#include "stdafx.h"
#include <stdio.h>
#include <allegro5/allegro.h>
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

int main(int argc, char **argv) {

	ALLEGRO_DISPLAY * display = NULL;
	ALLEGRO_TIMER * timer = NULL;
	ALLEGRO_BITMAP * imageCrosshair = NULL;  //reticle
	ALLEGRO_EVENT_QUEUE * event_queue = NULL;
	ALLEGRO_FONT * font;
	ALLEGRO_FONT * titleFont;
	ALLEGRO_BITMAP * background = NULL;
	ALLEGRO_BITMAP * imageUfo = NULL;
	ALLEGRO_BITMAP * imageBomb[5] = { NULL }; //alternates between 5 different bombs of different colours
	ALLEGRO_BITMAP * imageMissile = NULL;  //images of player missiles which dissapear upon being fired
	ALLEGRO_BITMAP * ground = NULL;  //planet surface texture
	ALLEGRO_BITMAP * imageBase = NULL;  //space bases player must defend
	FILE * fptr = NULL;

	//structs
	Level level; //stores miscellaneous data
	Crosshair crosshair;
	Abm abm[ABM_COUNT];  //player's anti-ballistic missiles used to shoot down enemies
	Explosion explosion[ABM_COUNT]; //explosion of abm
	Base base[6];  //player's bases
	Audio audio;

	//arrays to be dynamically allocated
	Enemy ** enemy = NULL;  //enemy missiles
	Ufo * ufo = NULL;  //enemy ufos
	Bomb * bomb = NULL; //enemy bombs

	int colorMap[NUM_COLORS][3];
	int theme[COLORS_PER_THEME]; //3 colours per theme, e.g. [0] = blue, [1] = yellow, [2] = pink

	oneTimeInit(&level);  //initial initialization

	//malloc arrays
	enemy = (Enemy **)malloc(level.maxEnemyOnScreen * sizeof(Enemy *));
	for (int i = 0; i < level.maxEnemyOnScreen; i++) {
		enemy[i] = (Enemy *)malloc(SPLIT_COUNT * sizeof(Enemy));
	}

	ufo = (Ufo *)malloc(level.maxUfoOnScreen * sizeof(Ufo));
	bomb = (Bomb *)malloc(level.maxBombOnScreen * sizeof(Bomb));


	srand(time(0));

	initAllegro(&display, &timer, &imageCrosshair, &event_queue, &font, &background, &imageUfo, &level, imageBomb, &imageMissile, &ground, &imageBase, &titleFont, &audio);

	initCrosshair(&crosshair, imageCrosshair);

	initLevel(&level);

	initAbm(abm, explosion);

	initEnemy(enemy, &level, ufo, bomb);

	initBase(base, 6, level);

	initColorMap(colorMap);

	generateTheme(theme);

	readScore(fptr, &level);
	sortScore(fptr, &level);

	titleScreen(imageBase, background, imageMissile, ground, event_queue, titleFont, font, audio, level);

	playerMovement(display, timer, imageCrosshair, event_queue, crosshair, abm, enemy, font, base, explosion, theme, colorMap, &level, background,
		imageUfo, ufo, imageBomb, bomb, imageMissile, ground, imageBase, titleFont, fptr, &audio);

	return 0;
}
