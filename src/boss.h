/* src/boss.h
 * boss headers
 * by: thomas bruce
 * date: 26/04/2025
 */

#ifndef BOSS_H
#define BOSS_H

#include <raylib.h>
#include "game.h"

typedef struct Boss {
	Vector2 pos;
	int hp;
	float shootTimer;
} Boss;

Boss *boss_Create(Vector2);
void boss_Update(Boss *, Game *, float dt);
void boss_Draw(Boss *);
void boss_Destroy(Boss *);

#endif
