#include "game.h"
#include "board.h"
#include <iostream>

Game::Game()
{
	board = Board();
	phase = "Player";
	confirmationPhase = "Unconfirmed";
	initSection = -1;
	round = 0;
	previousRound = 0;
	winner = 0;

}


//gains the user input and the keys that i know will be used
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

// should rework this, very inefficient
void Game::Draw() {

	board.Draw();

	if (winner != 0) {
		DrawText(message, 100, 50, 30, BLACK);
	}

	if (phase == "Player") {
		UserTurn();
		return;
	}
	if (phase == "Bot") {
		BotTurn();
		return;
	}

}

// changes the turn
void Game::NewTurn() {
	if (phase == "Player") {
		phase = "Bot";
		confirmationPhase = "Unconfirmed";
		initSection = -1;
	}
	else if (phase == "Bot") {
		phase = "Player";
	}

	// if someone wins, the info will be gained here
	winner = board.CheckWinner();
	if (winner == 2) {
		message = "Red wins!";
	}
	else if (winner == 3) {
		message = "Yellow wins!";
	}
}


// This is for the bot turn, for now it randomly picks a section instead of thinking
void Game::BotTurn() { 
	int y;
	int x;
	do {
		x = rand() % board.numCols;
		y = board.EmptySection(x);
	} while (y == -1);

	board.AddChip(x, y, 'Y'); // Add a chip for the bot
	NewTurn();
}


// This is for the users turn

void Game::UserTurn() {
	int key = UserInput();

	//this part makes sure a key is already selected and they press confirm with the enter key
	if (confirmationPhase == "Confirmed" && key == 7) {

		//this part makes sure the row is useable
		int y = board.EmptySection(initSection);
		if (y == -1) {
			confirmationPhase = "Unconfirmed";

			initSection = -1;
			return;
		}


		board.AddChip(initSection,y, 'R');
		NewTurn();


	}// this part sees if the user selected a new row
	else if (key != 7 && key != -1) {
		confirmationPhase = "Confirmed";
		initSection = key;
	}
}
