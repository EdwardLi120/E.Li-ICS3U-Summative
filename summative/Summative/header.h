//header.h
//#pragma once

//globals
const float FPS = 60;
const int SCREEN_W = 900;
const int SCREEN_H = 900;
const int BOUNCER_SIZE = 32;
const int NUM_BULLETS = 100;
const int ROWS = 5;   //rows of enemies
const int COLS = 3;  //columns of enemies
const int frameCount = 33;
const int MAX_ENEMY = 5; //max enemies on screen at one time
const int MAX_SPLIT = 10;
const int ENEMY_COUNT = 50;
const int SPLIT_COUNT = 4;
const int SIZE = 1.5;  //3x3 square
const int ABM_COUNT = 30;

enum KEYS {
	KEY_UP, KEY_DOWN, KEY_LEFT, KEY_RIGHT, KEY_SPACE  //by default member 1 = 0, member 2 = 1, member 3 = 2, member 4 = 3...
};



//crosshair
typedef struct crosshairData {
	float x;
	float y;
	float height;
	float width;
	float target_x;
	float target_y;
} Crosshair;

typedef struct coordinates {
	int x;
	int y;
} Vector;

//each individual ABM has these properties
typedef struct abmData {
	int dest_x;
	int dest_y;
	int launch_x;
	int launch_y;
	float dx;
	float dy;
	float x_inc;
	float y_inc;
	float x_pos;
	float y_pos;
	float step;
	int speed;
	bool launched;
	bool arrived;
	bool doneExploding;
	float explosionRadius;
	bool increaseRadius;
	int num_increment;
	Vector topRight;
	Vector topLeft;
	Vector bottomLeft;
}Abm;

typedef struct enemyData {
	int dest_x;
	int dest_y;
	int launch_x;
	int launch_y;
	float dx;
	float dy;
	float x_inc;
	float y_inc;
	float x_pos;
	float y_pos;
	float step;
	int speed;
	bool launched;
	bool arrived;
	int relativeX;
	int relativeY;
	int distX;
	int distY;
	int distTotal;
	Vector topRight;
	Vector topLeft;
	Vector bottomLeft;
} Enemy;

//prototypes
int initAllegro(ALLEGRO_DISPLAY **display, ALLEGRO_TIMER **timer, ALLEGRO_BITMAP **imageCrosshair, ALLEGRO_BITMAP **imageBase, ALLEGRO_EVENT_QUEUE **event_queue);
void initCrosshair(Crosshair * crosshair, ALLEGRO_BITMAP * imageCrosshair);
void initAbm(struct abmData * abm);

void playerMovement(ALLEGRO_DISPLAY *display, ALLEGRO_TIMER *timer, ALLEGRO_BITMAP *imageCrosshair, ALLEGRO_EVENT_QUEUE *event_queue, Crosshair crosshair, struct abmData * abm, Enemy enemy[ENEMY_COUNT][SPLIT_COUNT], int * curr_enemy_count, int * num_spawned);

void drawCrosshair(ALLEGRO_BITMAP *imageCrosshair, Crosshair * crosshair);
void drawBase(ALLEGRO_BITMAP *imageBase);

void fire(Abm * abm, Crosshair crosshair);
void calcAbmInc(Abm * abm);
void updateAbm(struct abmData * abm);
void drawAbm(struct abmData * abm);
void abmArrival(Abm * abm);  //check if abm arrived
void drawExplosion(Abm * abm);

void initEnemy(Enemy enemy[ENEMY_COUNT][SPLIT_COUNT]);
void spawnEnemy(Enemy enemy[ENEMY_COUNT][SPLIT_COUNT], int * curr_enemy_count, int * num_spawned);
void calcEnemyInc(Enemy * enemy);
void drawEnemy(Enemy enemy[ENEMY_COUNT][SPLIT_COUNT]);
void updateEnemy(Enemy enemy[ENEMY_COUNT][SPLIT_COUNT]);
void enemyArrival(Enemy enemy[ENEMY_COUNT][SPLIT_COUNT], int *curr_enemy_count);

void hitDetection(struct abmData * abm, Enemy enemy[ENEMY_COUNT][SPLIT_COUNT], int *curr_enemy_count);

