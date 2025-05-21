#include "game.h"
#include "board.h"
#include <iostream>

Game::Game()
{
	board = Board();
	phase = "Player";
	confirmationPhase = "Unconfirmed";
	initSection = -1;
}

int Game::UserInput() {
	int key = GetKeyPressed();

	switch (key) {
	case KEY_ONE:
		return 0;
	case KEY_TWO:
		return 1;
	case KEY_THREE:
		return 2;
	case KEY_FOUR:
		return 3;
	case KEY_FIVE:
		return 4;
	case KEY_SIX:
		return 5;
	case KEY_SEVEN:
		return 6;

	case KEY_ENTER:
		return 7;
	default:
		return -1;
	}
}

void Game::Draw() {
	board.Draw();
	if (phase == "Player") {
		UserTurn();
	}
	if (phase == "Bot") {
		BotTurn();
	}
}


void Game::NewTurn() {
	if (phase == "Player") {
		phase = "Bot";
		confirmationPhase = "Unconfirmed";
		initSection = -1;
	}
	else if (phase == "Bot") {
		phase = "Player";
	}

}


void Game::BotTurn() {  
	// Bot logic here for now is just random generator  
	int x = rand() % board.numCols;  
	int y = board.numRows - 1; // Corrected to use numRows instead of numCols  

	while (y >= 0 && board.grid[y][x] != 0) {  
		if (y == 0) {  
			x = rand() % board.numCols;  
		}  
	y--;  
	}  

	if (y >= 0) { // Ensure valid index before updating the board  
		board.Update(x, 'Y');
		NewTurn();
	}
}

void Game::UserTurn() {
	int key = UserInput();
	if (confirmationPhase == "Confirmed" && key == 7) {
		int y = board.EmptySection(initSection);
		if (y == -1) {
			confirmationPhase = "Unconfirmed";
			std::cout << "BUSSY" << std::endl;

			initSection = -1;
			return;
		}
		board.AddChip(initSection,y, 'R');
		NewTurn();
	}
	else if (key != 7 && key != -1) {
		confirmationPhase = "Confirmed";
		initSection = key;
	}
}

