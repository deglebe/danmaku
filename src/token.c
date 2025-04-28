/* src/token.c
 * power and score tokens
 * by: thomas bruce
 * date: 26/04/2025
 */

#include "token.h"

#include <raymath.h>
#include <stdlib.h>

#include "assets.h"
#include "game.h"
#include "player.h"

#define TOKEN_SPEED 60.0f
#define SCORE_VALUE 20
#define POWER_VALUE 20
#define TOKEN_SIZE 12

static Rectangle boundsFromPos(Vector2 p) {
	return (Rectangle){p.x - TOKEN_SIZE / 2.0f, p.y - TOKEN_SIZE / 2.0f,
	                   TOKEN_SIZE, TOKEN_SIZE};
}

Token *token_Create(Vector2 spawn, TokenType t) {
	Token *tk = malloc(sizeof *tk);
	*tk =
	    (Token){.pos = spawn, .vel = (Vector2){0, TOKEN_SPEED}, .type = t};
	return tk;
}

bool token_Update(Token *t, Game *g, float dt) {
	t->pos = Vector2Add(t->pos, Vector2Scale(t->vel, dt));

	if (t->pos.y > 720 + TOKEN_SIZE) return true;

	Rectangle tkRect = boundsFromPos(t->pos);
	if (CheckCollisionCircleRec(g->player->pos, PLAYER_RADIUS, tkRect)) {
		if (t->type == TT_SCORE)
			g->player->score += SCORE_VALUE;
		else
			g->player->power += POWER_VALUE;
		return true;
	}
	return false;
}

void token_Draw(Token *t) {
	Texture2D tex =
	    (t->type == TT_SCORE) ? TEX_TOKEN_SCORE : TEX_TOKEN_POWER;
	DrawTextureV(tex,
	             (Vector2){t->pos.x - tex.width / 2.0f,
	                       t->pos.y - tex.height / 2.0f},
	             WHITE);
}

void token_Destroy(Token *t) { free(t); }
