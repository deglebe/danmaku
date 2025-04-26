/* src/boss.c
 * very incomplete boss implementation
 * by: thomas bruce
 * date: 26/04/2025
 */

#include "boss.h"

#include <raymath.h>
#include <stdlib.h>

#include "bullet.h"
#include "player.h"

#define BOSS_HP 200
#define RELOAD_TIME 1.2f /* seconds between bursts */

/* boss-specific implementation of firing patterns */
static void firePattern(struct Boss *b, int pattern, struct Game *g) {
	switch (pattern) {
	/* circle */
	case 0: {
		for (int i = 0; i < 16 && g->bulletCount < MAX_BULLETS; ++i) {
			float a = (2 * PI / 16) * i;
			Vector2 v = {cosf(a) * 200, sinf(a) * 200};
			g->bullets[g->bulletCount++] =
			    bullet_Create(b->pos, v, BT_ENEMY);
		}
	} break;

	/* star */
	case 1: {
		for (int i = 0; i < 5 && g->bulletCount < MAX_BULLETS; ++i) {
			float a = (2 * PI / 5) * i;
			Vector2 v = {cosf(a) * 240, sinf(a) * 240};
			g->bullets[g->bulletCount++] =
			    bullet_Create(b->pos, v, BT_ENEMY);
		}
	} break;

	/* single initial-direction tracker */
	default: {
		Vector2 dir =
		    Vector2Normalize(Vector2Subtract(g->player->pos, b->pos));
		g->bullets[g->bulletCount++] =
		    bullet_Create(b->pos, Vector2Scale(dir, 220), BT_TRACKER);
	} break;
	}
}

Boss *boss_Create(Vector2 p) {
	Boss *b = malloc(sizeof *b);
	*b = (Boss){.pos = p, .hp = BOSS_HP, .shootTimer = RELOAD_TIME};
	return b;
}

void boss_Update(Boss *b, Game *g, float dt) {
	b->shootTimer -= dt;
	if (b->shootTimer <= 0) {
		firePattern(b, GetRandomValue(0, 2), g);
		b->shootTimer = RELOAD_TIME;
	}
	/* TODO: take damage, die, win-state */
}

void boss_Draw(Boss *b) {
	DrawCircleV(b->pos, 14, RED);
	DrawText(TextFormat("HP:%d", b->hp), (int)(b->pos.x - 20),
	         (int)(b->pos.y - 28), 10, RED);
}

void boss_Destroy(Boss *b) { free(b); }
