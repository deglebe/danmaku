/* src/assets.c
 * handles asset loading/unloading
 * by: thomas bruce
 * date: 26/04/2025
 */

#include "assets.h"

Texture2D TEX_BULLET_BLUE, TEX_BULLET_GREEN, TEX_BULLET_RED;
Texture2D TEX_TOKEN_SCORE, TEX_TOKEN_POWER;
Texture2D TEX_PLAYER, TEX_ENEMY, TEX_BOSS;

void assets_Load(void) {
	TEX_BULLET_BLUE = LoadTexture("res/bullet_player.png");
	TEX_BULLET_GREEN = LoadTexture("res/bullet_enemy.png");
	TEX_BULLET_RED = LoadTexture("res/bullet_track.png");
	TEX_TOKEN_SCORE = LoadTexture("res/token_score.png");
	TEX_TOKEN_POWER = LoadTexture("res/token_power.png");
	TEX_PLAYER = LoadTexture("res/player.png");
	TEX_ENEMY = LoadTexture("res/enemy.png");
	TEX_BOSS = LoadTexture("res/boss.png");
}

void assets_Unload(void) {
	UnloadTexture(TEX_BULLET_BLUE);
	UnloadTexture(TEX_BULLET_GREEN);
	UnloadTexture(TEX_BULLET_RED);
	UnloadTexture(TEX_TOKEN_SCORE);
	UnloadTexture(TEX_TOKEN_POWER);
	UnloadTexture(TEX_PLAYER);
	UnloadTexture(TEX_ENEMY);
	UnloadTexture(TEX_BOSS);
}
