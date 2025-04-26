/* src/game.h
 * game struct and entity limiters
 * by: thomas bruce
 * date: 26/04/2025
 */

#ifndef GAME_H
#define GAME_H

#include <stdbool.h>
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
	bool won;
	bool lost;
	bool immortal;
} Game;

void danmaku_Init(Game *g, bool immortal);
void danmaku_Update(Game *g, float dt);
void danmaku_Draw(Game *g);
void danmaku_Shutdown(Game *g);

#endif
