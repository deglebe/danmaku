/* src/boss.h
 * boss headers
 * by: thomas bruce
 * date: 26/04/2025
 */

#ifndef BOSS_H
#define BOSS_H

#include <raylib.h>
#include "game.h"

#define BOSS_RADIUS 24.0f

typedef struct Boss {
	Vector2 pos;
	int hp;
	float shootTimer;
	int nextShiftHP; /* hp threshold for sidestepping */
} Boss;

Boss *boss_Create(Vector2);
void boss_Update(Boss *, Game *, float dt);
void boss_Draw(Boss *);
void boss_Destroy(Boss *);

#endif
