/* src/enemy.c
 * enemy handling
 * by: thomas bruce
 * date: 26/04/2025
 */

#include "enemy.h"

#include <raymath.h>
#include <stdlib.h>

#include "assets.h"
#include "bullet.h"
#include "player.h"

#define ENEMY_HP 5

static void fire(Enemy *e, Game *g) {
	switch (e->pat) {
	case EPAT_CIRCLE:
		for (int i = 0; i < 16 && g->bulletCount < MAX_BULLETS; ++i) {
			float a = (2 * PI / 16) * i;
			Vector2 v = {cosf(a) * 160, sinf(a) * 160};
			g->bullets[g->bulletCount++] =
			    bullet_Create(e->pos, v, BT_ENEMY);
		}
		break;
	case EPAT_STAR:
		for (int i = 0; i < 5 && g->bulletCount < MAX_BULLETS; ++i) {
			float a = (2 * PI / 5) * i;
			Vector2 v = {cosf(a) * 240, sinf(a) * 240};
			g->bullets[g->bulletCount++] =
			    bullet_Create(e->pos, v, BT_ENEMY);
		}
		break;
	case EPAT_TRACKER: {
		Vector2 dir =
		    Vector2Normalize(Vector2Subtract(g->player->pos, e->pos));
		g->bullets[g->bulletCount++] =
		    bullet_Create(e->pos, Vector2Scale(dir, 180), BT_TRACKER);
	} break;
	}
}

Enemy *enemy_Create(Vector2 p, EnemyPattern pat, Vector2 vel) {
	Enemy *e = malloc(sizeof *e);
	*e = (Enemy){.pos = p, .vel = vel, .hp = ENEMY_HP, .pat = pat};
	return e;
}

void enemy_Update(Enemy *e, Game *g, float dt) {
	e->pos.x += e->vel.x * dt;
	e->pos.y += e->vel.y * dt;

	if (e->pos.y > 740 || e->pos.x < -20 || e->pos.x > 500) {
		e->hp = 0;
		return;
	}

	e->shootTimer -= dt;
	if (e->shootTimer <= 0) {
		fire(e, g);
		e->shootTimer = 2.0f;
	}
}

void enemy_Draw(Enemy *e) {
	const float SCALE = 1.0f;
	DrawTextureEx(TEX_ENEMY,
	              (Vector2){e->pos.x - TEX_ENEMY.width * SCALE / 2.0f,
	                        e->pos.y - TEX_ENEMY.height * SCALE / 2.0f},
	              0.0f, SCALE, WHITE);
}

void enemy_Destroy(Enemy *e) { free(e); }
