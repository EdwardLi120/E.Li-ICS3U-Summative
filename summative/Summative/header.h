
//#pragma once

//globals

const float FPS = 60;
const int SCREEN_W = 900;
const int SCREEN_H = 900;
const int BOUNCER_SIZE = 32;
const int NUM_BULLETS = 100;
const int ROWS = 5;   //rows of enemies
const int COLS = 3;  //columns of enemies
const int NUM_ENEMIES_TOTAL = 8;

enum KEYS {
	KEY_UP, KEY_DOWN, KEY_LEFT, KEY_RIGHT, KEY_SPACE  //by default member 1 = 0, member 2 = 1, member 3 = 2, member 4 = 3...
};

enum ID {PLAYER, BULLET, ENEMY};

//crosshair
struct playerData {
	float x;  //x-coordinate
	float y;  //y-coordinate
	int lives;
	int score;
};

//each individual ABM has these properties
struct abmData {
	float x;
	float y;
	float speed;
};

//struct of 3 batteries of ABM (a brigade consists of 3 batteries; each battery consists of 10 ABM);
struct brigade {
	struct abmData left[10];   //left battery
	struct abmData center[10]; //center battery (fastest missiles)
	struct abmData right[10];  //right battery
};

struct siloPos {
	float x;
	float y;
	bool used;
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

struct antiMissileData {  //player-launched anti-ballistic missile
	int launchpoint_x;
	int launchpoint_y;
};


//prototypes
int initAllegro(ALLEGRO_DISPLAY **display, ALLEGRO_TIMER **timer, ALLEGRO_BITMAP **imageShip, ALLEGRO_BITMAP **imageEnemy, ALLEGRO_EVENT_QUEUE **event_queue);
void initPlayer(struct playerData * player);
void initAbm(struct brigade * abm);
void initBullet(struct bulletData * bullet, int size);
void initEnemy(struct enemyData enemy[][COLS]);

void playerMovement(ALLEGRO_DISPLAY *display, ALLEGRO_TIMER *timer, ALLEGRO_BITMAP *imageCrosshair, ALLEGRO_BITMAP *imageEnemy, ALLEGRO_EVENT_QUEUE *event_queue, struct playerData * player, struct bulletData * bullet, struct enemyData enemy[][COLS], struct antiMissileData antiMissile);

void drawCrosshair(ALLEGRO_BITMAP *imageCrosshair, struct playerData player);
void drawEnemy(ALLEGRO_BITMAP *imageEnemy, struct enemyData enemy[][COLS]);

void fire(struct playerData player, ALLEGRO_BITMAP *imageEnemy);

