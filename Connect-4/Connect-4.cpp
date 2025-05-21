// Connect-4.cpp : This file contains the 'main' function. Program execution begins and ends there.
//

#include <iostream>
#include <vector>
#include <raylib.h>
#include "game.h"

using namespace std;


int main()
{
	InitWindow(800, 700, "Connect 4");
	SetTargetFPS(60);
	Game game = Game();
	while (!WindowShouldClose()) {

		// Update
		BeginDrawing();
		ClearBackground(LIGHTGRAY);
		game.Draw();
		EndDrawing();

	}

	CloseWindow();
}
