/* src/game.c
 * main game functions
 * by: thomas bruce
 * date: 26/04/2025
 */

#include "game.h"

#include <stdio.h>
#include <stdlib.h>

#include "assets.h"
#include "boss.h"
#include "bullet.h"
#include "enemy.h"
#include "player.h"
#include "token.h"

static EnemyPattern randPattern(void) {
	/* weighted: 0-3 circle, 4-7 star, 8-9 tracker */
	int r = GetRandomValue(0, 9);
	if (r < 4)
		return EPAT_CIRCLE;
	else if (r < 8)
		return EPAT_STAR;
	else
		return EPAT_TRACKER;
}

static void spawnSideEnemy(Game *g) {
	if (g->enemyCount >= MAX_ENEMIES) return;

	const bool fromLeft = GetRandomValue(0, 1);
	const float y = (float)GetRandomValue(80, 240); /* mid-screen band */
	const float speedX = 80.0f;
	const float speedY = 40.0f;

	Vector2 pos = {fromLeft ? -12.0f : 492.0f, y};
	Vector2 vel = {fromLeft ? speedX : -speedX, speedY};

	g->enemies[g->enemyCount++] = enemy_Create(pos, randPattern(), vel);
}

void danmaku_Init(Game *g, bool immortal) {
	*g = (Game){0};
	g->player = player_Create((Vector2){240, 680});
	g->boss = NULL;
	g->won = false;
	g->lost = false;
	g->immortal = immortal;
}

static void updateArrays(Game *g, float dt) {
	player_Update(g->player, g, dt);

	for (int i = 0; i < g->enemyCount;) {
		Enemy *e = g->enemies[i];
		enemy_Update(e, g, dt);
		if (e->hp <= 0) {
			enemy_Destroy(e);
			g->enemies[i] = g->enemies[--g->enemyCount];
			continue;
		}
		++i;
	}

	for (int i = 0; i < g->bulletCount; ++i) {
		if (bullet_Update(g->bullets[i], g, dt)) {
			bullet_Destroy(g->bullets[i]);
			g->bullets[i] = g->bullets[--g->bulletCount];
		}
	}

	for (int i = 0; i < g->tokenCount; ++i) {
		if (token_Update(g->tokens[i], g, dt)) {
			token_Destroy(g->tokens[i]);
			g->tokens[i] = g->tokens[--g->tokenCount];
		}
	}

	if (g->boss)
		boss_Update(g->boss, g, dt);
	else if (!g->won && g->player->power >= 300) {
	} else if (!g->boss && !g->won && g->player->power >= 300) {
		g->won = true;
	}
}

static void drawArrays(Game *g) {
	player_Draw(g->player);

	for (int i = 0; i < g->enemyCount; ++i) enemy_Draw(g->enemies[i]);
	for (int i = 0; i < g->bulletCount; ++i) bullet_Draw(g->bullets[i]);
	for (int i = 0; i < g->tokenCount; ++i) token_Draw(g->tokens[i]);

	if (g->boss) boss_Draw(g->boss);
}

static void drawHUD(Game *g) {
	const int margin = 8;
	char buf[64];

	sprintf(buf, "SCORE %d", g->player->score);
	DrawText(buf, 480 - margin - MeasureText(buf, 16), margin, 16,
	         DARKGRAY);

	sprintf(buf, "POWER %d", g->player->power);
	DrawText(buf, 480 - margin - MeasureText(buf, 16), margin + 20, 16,
	         DARKBLUE);

	sprintf(buf, "LIVES %d", g->player->lives);
	DrawText(buf, 480 - margin - MeasureText(buf, 16), margin + 40, 16,
	         MAROON);

	if (g->won) {
		const char *msg = "YOU WIN!";
		int w = MeasureText(msg, 40);
		DrawText(msg, (480 - w) / 2, 320, 40, DARKGREEN);
	}

	if (g->lost) {
		const char *msg = "YOU LOSE!";
		int w = MeasureText(msg, 40);
		DrawText(msg, (480 - w) / 2, 320, 40, MAROON);
	}
}

void danmaku_Update(Game *g, float dt) {
	if (g->won || g->lost) return;

	static float enemyTimer = 0.0f;
	enemyTimer -= dt;
	if (enemyTimer <= 0.0f) {
		spawnSideEnemy(g);
		enemyTimer = 1.5f;
	}

	if (!g->boss && !g->won && g->player->power >= 300) {
		g->boss = boss_Create((Vector2){240, 80});
	}

	updateArrays(g, dt);
}

void danmaku_Draw(Game *g) {
	drawArrays(g);
	drawHUD(g);
}

void danmaku_Shutdown(Game *g) {
	player_Destroy(g->player);
	boss_Destroy(g->boss);
}
