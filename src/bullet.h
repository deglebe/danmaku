/* src/bullet.h
 * bullet header and types
 * by: thomas bruce
 * date: 26/04/2025
 */

#ifndef BULLET_H
#define BULLET_H

#include <raylib.h>
#include <stdbool.h>

#include "game.h"

typedef enum {
	BT_ENEMY,
	BT_TRACKER,
	BT_PLAYER
} BulletType;

typedef struct Bullet {
	Vector2 pos, vel;
	BulletType type;
} Bullet;

bool bullet_Update(struct Bullet *b, struct Game *g, float dt);
void bullet_Draw(struct Bullet *b);
Bullet *bullet_Create(Vector2 pos, Vector2 vel, BulletType);
void bullet_Destroy(Bullet *b);

#endif

