/* src/main.c
 * main
 * by: thomas bruce
 * date: 21/05/2025
 */

#include <raylib.h>
#include <string.h>

#include "assets.h"
#include "game.h"

/* Game dimensions and layout */
#define GAME_W 480
#define GAME_H 720
#define SCOREBOARD_W 200
#define BORDER 4
#define WINDOW_W (GAME_W + BORDER * 2 + SCOREBOARD_W)
#define WINDOW_H (GAME_H + BORDER * 2)

int main(int argc, char **argv) {
	InitWindow(WINDOW_W, WINDOW_H, "danmaku");
	SetTargetFPS(60);
	assets_Load();

	bool immortal = (argc > 1 && strcmp(argv[1], "immortal") == 0);
	Game g;
	danmaku_Init(&g, immortal);

	while (!WindowShouldClose()) {
		float dt = GetFrameTime();
		danmaku_Update(&g, dt);

		BeginDrawing();
		ClearBackground(RAYWHITE);

		// draw black border
		DrawRectangle(0, 0, GAME_W + BORDER * 2, GAME_H + BORDER * 2,
		              BLACK);

		// draw game background
		DrawRectangle(BORDER, BORDER, GAME_W, GAME_H, RAYWHITE);

		// set scissor for game area to prevent drawing outside
		BeginScissorMode(BORDER, BORDER, GAME_W, GAME_H);
		danmaku_Draw(&g);
		EndScissorMode();

		// draw scoreboard
		danmaku_DrawHUD(&g, GAME_W + BORDER * 2, BORDER);

		EndDrawing();
	}

	danmaku_Shutdown(&g);
	assets_Unload();
	CloseWindow();
	return 0;
}
