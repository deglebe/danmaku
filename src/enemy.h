/* src/enemy.h
 * enemy header and enemy hitbox radius
 * by: thomas bruce
 * date: 26/04/2025
 */

#ifndef ENEMY_H
#define ENEMY_H

#include <raylib.h>

#include "game.h"

#define ENEMY_RADIUS 24.0f

typedef enum {
	EPAT_CIRCLE,
	EPAT_STAR,
	EPAT_TRACKER
} EnemyPattern;

typedef struct Enemy {
	Vector2 pos, vel;
	int hp;
	EnemyPattern pat;
	float shootTimer;
} Enemy;

Enemy *enemy_Create(Vector2 p, EnemyPattern pat, Vector2 vel);
void enemy_Update(Enemy *e, Game *g, float dt);
void enemy_Draw(Enemy *e);
void enemy_Destroy(Enemy *e);

#endif
