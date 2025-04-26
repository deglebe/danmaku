/* src/player.c
 * player handler
 * by: thomas bruce
 * date: 26/04/2025
 */

#include "player.h"

#include <raymath.h>
#include <stdlib.h>

#include "assets.h"
#include "bullet.h"

#define SPEED 240.0f
#define FIRE_BASE_RATE 0.5f /* 2 bullets per second */
#define FIRE_RATE_STEP 0.1f /* after 500 power every 100 -> +1/s */

static const float PLAYER_SCALE = 1.0f;
// static const float PLAYER_RADIUS = 10.0f;

static float calcCooldown(const Player *p) {
	if (p->power < 500) return FIRE_BASE_RATE;
	int extra = (p->power - 500) / 100;
	return FIRE_BASE_RATE / (1.0f + extra);
}

/* player base functionality */
Player *player_Create(Vector2 spawn) {
	Player *p = malloc(sizeof *p);
	*p = (Player){.pos = spawn, .lives = 3};
	return p;
}

static void handleMovement(Player *p, float dt) {
	Vector2 v = {0};
	if (IsKeyDown(KEY_LEFT)) v.x -= 1;
	if (IsKeyDown(KEY_RIGHT)) v.x += 1;
	if (IsKeyDown(KEY_UP)) v.y -= 1;
	if (IsKeyDown(KEY_DOWN)) v.y += 1;
	if (Vector2Length(v) > 0)
		v = Vector2Scale(Vector2Normalize(v), SPEED * dt);

	p->pos = Vector2Clamp(Vector2Add(p->pos, v), (Vector2){16, 16},
	                      (Vector2){480 - 16, 720 - 16});
}

static void shoot(Player *p, Game *g) {
	if (g->bulletCount + p->guns >= MAX_BULLETS) return;
	float offsets[3] = {0, -8, 8};
	for (int i = 0; i < p->guns; ++i)
		g->bullets[g->bulletCount++] =
		    bullet_Create((Vector2){p->pos.x + offsets[i], p->pos.y},
		                  (Vector2){0, -480}, BT_PLAYER);
}

void player_Update(Player *p, Game *g, float dt) {
	handleMovement(p, dt);

	p->shootCooldown -= dt;
	if (IsKeyDown(KEY_Z) && p->shootCooldown <= 0) {
		shoot(p, g);
		p->shootCooldown = calcCooldown(p);
	}
	if (IsKeyPressed(KEY_Z)) shoot(p, g);

	if (p->power >= 500)
		p->guns = 3;
	else if (p->power >= 200)
		p->guns = 2;
	else
		p->guns = 1;
}

void player_Draw(Player *p) {
	DrawTextureEx(
	    TEX_PLAYER,
	    (Vector2){p->pos.x - TEX_PLAYER.width * PLAYER_SCALE / 2.0f,
	              p->pos.y - TEX_PLAYER.height * PLAYER_SCALE / 2.0f},
	    0.0f, PLAYER_SCALE, WHITE);
}

void player_Destroy(Player *p) { free(p); }
