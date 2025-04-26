/* src/bullet.c
 * bullet creation/handling
 * by: thomas bruce
 * date: 26/04/2025
 */

#include "bullet.h"

#include <raymath.h>
#include <stdlib.h>

#include "assets.h"
#include "boss.h"
#include "enemy.h"
#include "player.h"
#include "token.h"

Bullet *bullet_Create(Vector2 pos, Vector2 vel, BulletType t) {
	Bullet *b = malloc(sizeof *b);
	*b = (Bullet){.pos = pos, .vel = vel, .type = t};
	return b;
}

bool bullet_Update(Bullet *b, Game *g, float dt) {
	b->pos = Vector2Add(b->pos, Vector2Scale(b->vel, dt));

	switch (b->type) {
	case BT_PLAYER: {
		for (int i = 0; i < g->enemyCount; ++i) {
			Enemy *e = g->enemies[i];
			if (Vector2Distance(b->pos, e->pos) < ENEMY_RADIUS) {
				e->hp--;
				if (e->hp <= 0) {
					if (g->tokenCount < MAX_TOKENS) {
						TokenType tt =
						    GetRandomValue(0, 1)
						        ? TT_SCORE
						        : TT_POWER;
						g->tokens[g->tokenCount++] =
						    token_Create(e->pos, tt);
					}
					enemy_Destroy(e);
					g->enemies[i] =
					    g->enemies[--g->enemyCount];
				}
				return true;
			}
		}
		if (g->boss && Vector2Distance(b->pos, g->boss->pos) < 14.0f) {
			g->boss->hp--;
			if (g->boss->hp <= 0) {
				boss_Destroy(g->boss);
				g->boss = NULL;
			}
			return true;
		}
	} break;

	case BT_ENEMY:
	case BT_TRACKER:
		if (Vector2Distance(b->pos, g->player->pos) < PLAYER_RADIUS) {
			if (g->player->lives > 0) {
				g->player->lives--;
				g->player->power =
				    (int)(g->player->power * 0.3f);
			}
			return true;
		}
		break;
	}

	if (b->pos.x < -8 || b->pos.x > 488 || b->pos.y < -8 || b->pos.y > 728)
		return true;

	return false;
}

void bullet_Draw(Bullet *b) {
	Texture2D tex = (b->type == BT_PLAYER)    ? TEX_BULLET_BLUE
	                : (b->type == BT_TRACKER) ? TEX_BULLET_RED
	                                          : TEX_BULLET_GREEN;

	const float scale = 0.5f;
	Vector2 size = {tex.width * scale, tex.height * scale};

	DrawTextureEx(
	    tex, (Vector2){b->pos.x - size.x / 2.0f, b->pos.y - size.y / 2.0f},
	    0.0f, scale, WHITE);
}

void bullet_Destroy(Bullet *b) { free(b); }
