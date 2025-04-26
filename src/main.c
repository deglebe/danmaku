/* src/main.c
 * main
 * by: thomas bruce
 * date: 26/04/2025
 */

#include <raylib.h>

#include "assets.h"
#include "game.h"

int main(void) {
	const int W = 480, H = 720;
	InitWindow(W, H, "danmaku");
	SetTargetFPS(60);
	assets_Load();

	Game g;
	danmaku_Init(&g);

	while (!WindowShouldClose()) {
		float dt = GetFrameTime();
		danmaku_Update(&g, dt);

		BeginDrawing();
		ClearBackground(RAYWHITE);
		danmaku_Draw(&g);
		EndDrawing();
	}

	danmaku_Shutdown(&g);
	assets_Unload();
	CloseWindow();
	return 0;
}
