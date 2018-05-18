//Header.h:
//#pragma once
//globals
const float FPS = 60;
const int SCREEN_W = 640;
const int SCREEN_H = 640;
const int BOUNCER_SIZE = 32;
const int NUM_BULLETS = 1000;
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
