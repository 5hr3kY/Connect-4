#include "game.h"
#include "board.h"
#include <iostream>
#include <string>
#include "config.h"

Game::Game()
{
	board = Board();
	phase = "Player";
	confirmationPhase = "Unconfirmed";
	initSection = -1;
	winner = 0;

	// checks if the animation is finihsed
	finishAnimation = false;

	// checks if the animation is started
	startAnimation = false;
	velocity = 0.0f;


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

	board.Draw1();

	if (startAnimation) {
		Color col;
		int vertical;
		int horizontal;
		int type;

		if (phase == "Player") {
			col = RED;
			type = 2;
			horizontal = initSection;
			vertical = board.EmptySection(initSection);
		}
		else if (phase == "Bot") {
			col = YELLOW;
			type = 3;
			horizontal = botX;
			vertical = botY;
		}
		finishAnimation = Animate(horizontal, col, vertical);

		if (finishAnimation) {
			startAnimation = false;
			finishAnimation = false;
			board.AddChip(horizontal, vertical, type);

			NewTurn();
			// reset the animation time
			animationTime = GetTime();
		}
	

	}

	board.Draw2();

	//draws the winner
	if (winner != 0) {
		DrawText(message, 100, 10, FONTSIZE, BLACK);
	}

	//writes whose turn it is
	if (phase == "Player") {
		TurnText(0);
	}
	else if (phase == "Bot") {
		TurnText(1);
	}

	if (phase == "Player") {
		UserTurn();
		return;
	}
	if (phase == "Bot" && !startAnimation) {
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
		botX = -1;
		botY = -1;
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
	do {
		botX = rand() % board.numCols;
		botY = board.EmptySection(botX);
	} while (botY == -1);



	startAnimation = true;
	animationTime = GetTime();

}


// This is for the users turn

void Game::UserTurn() {
	int key = UserInput();

	if (confirmationPhase == "Confirmed") 		DrawText("Confirm?", 10, 10, FONTSIZE, BLACK);

	//this part makes sure a key is already selected and they press confirm with the enter key
	if (confirmationPhase == "Confirmed" && key == 7) {

		//this part makes sure the row is useable
		int y = board.EmptySection(initSection);
		if (y == -1) {
			confirmationPhase = "Unconfirmed";

			initSection = -1;
			return;
		}

		startAnimation = true;
		animationTime = GetTime();
		
	}// this part sees if the user selected a new row
	else if (key != 7 && key != -1 && !startAnimation) {
		confirmationPhase = "Confirmed";
		initSection = key;
	}
	CreateHighlight(initSection);

}


void Game::TurnText(int turn) {
	std::string message;
	if (turn == 0) {
		message = "Player's Turn";
	}
	else if (turn == 1) {
		message = "Bot's Turn";
	}
	DrawText(message.c_str(), 500, 10, FONTSIZE, BLACK);
	return;
}

void Game::CreateHighlight(int x) {
	if (confirmationPhase == "Confirmed" && !startAnimation) {
		DrawRectangle(85 + x * 95, 40, 75, 60, {255,255,255,120}); // Draw a gray rectangle to highlight the selected colu
		DrawRectangle(100 + x * 95, 49, CHECKERLENGTHS, CHECKERLENGTHS, RED); // Draw a fake checker
		}
}


bool Game::Animate(int row, Color color,int location) {
	double currentAnimationTime = GetTime();
	double timeLeft = currentAnimationTime - animationTime;

	timeLeft *= 250;
	int y = static_cast<int>(timeLeft);
	velocity += 10 * timeLeft;

	y += velocity * timeLeft;

	if (y+50-(CHECKERLENGTHS/2) < location*95+100) {

		DrawRectangle(100 + row * 95,  y+50 , CHECKERLENGTHS, CHECKERLENGTHS, color);
		return false; //still animating
	}
	
	velocity = 0.0;
	return true;//not animating anymore cuz done
}


