/* src/game.h
 * game struct and entity limiters
 * by: thomas bruce
 * date: 26/04/2025
 */

#ifndef GAME_H
#define GAME_H

#include "entity.h"

#define MAX_BULLETS	4096
#define MAX_ENEMIES	16
#define MAX_TOKENS	64

typedef struct Game {
	struct Player *player;
	struct Boss *boss;
	struct Enemy *enemies[MAX_ENEMIES];
	struct Bullet *bullets[MAX_BULLETS];
	struct Token *tokens[MAX_TOKENS];
	int enemyCount, bulletCount, tokenCount;
} Game;

void danmaku_Init(Game *g);
void danmaku_Update(Game *g, float dt);
void danmaku_Draw(Game *g);
void danmaku_Shutdown(Game *g);

#endif
