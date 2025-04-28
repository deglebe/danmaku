/* src/boss.c
 * very incomplete boss implementation
 * by: thomas bruce
 * date: 26/04/2025
 */

#include "boss.h"

#include <raymath.h>
#include <stdlib.h>

#include "assets.h"
#include "bullet.h"
#include "player.h"

#define BOSS_HP 200
#define RELOAD_TIME 1.2f /* seconds between bursts */
#define SHIFT_STEP 40.0f /* pixels to move by when sidestepping */

/* boss-specific implementation of firing patterns */
static void firePattern(struct Boss *b, int pattern, struct Game *g) {
	switch (pattern) {
	/* circle */
	case 0: {
		for (int i = 0; i < 32 && g->bulletCount < MAX_BULLETS; ++i) {
			float a = (2 * PI / 32) * i;
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
	*b = (Boss){.pos = p,
	            .hp = BOSS_HP,
	            .shootTimer = RELOAD_TIME,
	            .nextShiftHP = BOSS_HP - 30};
	return b;
}

void boss_Update(Boss *b, Game *g, float dt) {
	b->shootTimer -= dt;
	if (b->shootTimer <= 0) {
		int pattern = GetRandomValue(0, 2);
		int times = GetRandomValue(1, 5);
		if (pattern == 0) {
			for (int i = 0; i < times; i++) {
				firePattern(b, pattern, g);
				b->shootTimer = RELOAD_TIME;
			}
		} else {
			firePattern(b, pattern, g);
			b->shootTimer = RELOAD_TIME;
		}
	}

	/* sidestep */
	if (b->hp <= b->nextShiftHP) {
		float dir = GetRandomValue(0, 1) ? 1.0f : -1.0f;
		b->pos.x = Clamp(b->pos.x + dir * SHIFT_STEP, 70.0f, 440.0f);
		b->nextShiftHP -= 30;
	}
}

void boss_Draw(Boss *b) {
	const float SCALE = 1.0f;
	DrawTextureEx(TEX_BOSS,
	              (Vector2){b->pos.x - TEX_BOSS.width * SCALE / 2.0f,
	                        b->pos.y - TEX_BOSS.height * SCALE / 2.0f},
	              0.0f, SCALE, WHITE);

	DrawText(TextFormat("HP:%d", b->hp), (int)(b->pos.x - 20),
	         (int)(b->pos.y - 50), 15, RED);
}

void boss_Destroy(Boss *b) { free(b); }
