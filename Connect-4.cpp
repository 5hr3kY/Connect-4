// Connect-4.cpp : This file contains the 'main' function. Program execution begins and ends there.
//
//maybe create a person class to hold the player and bot funcs

#include <raylib.h>

#include <iostream>
#include <vector>
#include "game.h"
#include <string>

using namespace std;


int main()
{
	InitWindow(800, 700, "Connect 4");
	Font font = GetFontDefault();
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
