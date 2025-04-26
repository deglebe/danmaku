/* src/assets.h
 * asset handler headers and exposed textures
 * by: thomas bruce
 * date: 26/04/2025
 */

#ifndef ASSETS_H
#define ASSETS_H

#include <raylib.h>

extern Texture2D TEX_BULLET_BLUE, TEX_BULLET_GREEN, TEX_BULLET_RED;
extern Texture2D TEX_TOKEN_SCORE, TEX_TOKEN_POWER;
extern Texture2D TEX_PLAYER, TEX_ENEMY, TEX_BOSS;

void assets_Load(void);
void assets_Unload(void);

#endif
