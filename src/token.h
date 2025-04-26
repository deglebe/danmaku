/* src/tokens.h
 * token header
 * by: thomas bruce
 * date: 26/04/2025
 */

#ifndef TOKEN_H
#define TOKEN_H

#include <raylib.h>
#include <stdbool.h>
#include "game.h"

typedef enum { TT_SCORE, TT_POWER } TokenType;

typedef struct Token {
	Vector2   pos;
	Vector2   vel;
	TokenType type;
} Token;

Token *token_Create(Vector2 spawn, TokenType t);

bool token_Update(struct Token *t, struct Game *g, float dt);

void token_Draw(Token *t);
void token_Destroy(Token *t);

#endif /* TOKEN_H */

