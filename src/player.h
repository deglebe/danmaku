/* src/player.h
 * player struct and radius
 * by: thomas bruce
 * date: 26/04/2025
 */

#ifndef PLAYER_H
#define PLAYER_H

#include <raylib.h>
#include "game.h"

#define PLAYER_RADIUS	16.0f

typedef struct Player {
	Vector2 pos;
	int score, power, guns, lives;
	float shootCooldown;
} Player;

Player *player_Create(Vector2 spawn);
void player_Update(Player *p, Game *g, float dt);
void player_Draw(Player *p);
void player_Destroy(Player *p);

#endif
