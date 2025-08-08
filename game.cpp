#include "game.h"
#include "board.h"
#include <iostream>
#include <string>
#include "config.h"
#include <chrono>
#include <thread>

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

	isPlayer; // checks if the game is against a player or a bot, true is against player, false is against bot
	gameStart = false;

	isEnd = false;

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

void Game::Draw()
{
	if (gameStart) {

		//this part check if the game is against player
		if (isPlayer) {
			PlayerVSPlayer();
		}

		//this part will draw the game and its core aspects against a player
		else {
			PlayerVSBot();
		}
	}//if the game hasn't started, it checks if its the beginning menu or the losing/winning menu
	else {
		if (isEnd) {
			EndScreen();
		}
		else BeginningScreen();
	}
}

void Game::EndScreen() {
	bool mousePressed = IsMouseButtonPressed(MOUSE_LEFT_BUTTON);
	Vector2 mousePos = GetMousePosition();
	DrawText(message, (WIDTH/2)- (MeasureText(message,100)/2), 20, 100, GREEN);
	Rectangle MenuButton = { 50, 400, 300, 90 };
	Rectangle AgainButton = { 400, 400, 300, 90 };
	DrawRectangleRec(MenuButton, WHITE);
	DrawRectangleRec(AgainButton,WHITE);

	DrawText("Menu",200 -MeasureText("MENU",FONTSIZE)/2, 420, FONTSIZE, BLACK);
	DrawText("Play Again",550-MeasureText("Play Again",FONTSIZE)/2, 420, FONTSIZE,BLACK);

	if (mousePressed){
		if (CheckCollisionPointRec(mousePos, MenuButton)) {
			isEnd = false;
			gameStart = false;	
			board.Initialize();
			winner = 0;
			phase = "Player";
		
	
		}
		if (CheckCollisionPointRec(mousePos, AgainButton)) {
			gameStart = true;
			isEnd = false;
			winner = 0;
			board.Initialize();
			phase = "Player";

		}


	}
}


// this screen whill have a title and 2 buttons, a playervsplayer and a botvsplayer button
//    bool IsMouseButtonPressed(int button);
void Game::BeginningScreen() {
	bool mousePressed = IsMouseButtonPressed(MOUSE_LEFT_BUTTON);
	Vector2 mousePos = GetMousePosition();                         
	Rectangle PVBButton = { 50, 400, 300, 90 };
	Rectangle PVPButton = { 400, 400, 300, 90 };

	DrawText("Connect 4", (WIDTH/2)-260, 100, 100, BLACK);
	DrawRectangleRec(PVBButton, BLUE);
	DrawRectangleRec(PVPButton, BLUE);

	DrawText("Player vs Bot", 100, 420, FONTSIZE, WHITE);
	DrawText("Player vs Player", 420, 420, FONTSIZE, WHITE);

	if (mousePressed) {
		if (CheckCollisionPointRec(mousePos, PVBButton)) {
			isPlayer = false;
			gameStart = true;
		}

		if (CheckCollisionPointRec(mousePos, PVPButton)) {
			isPlayer = true;
			gameStart = true;
		}
	}
}

void Game::PlayerVSPlayer() {


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
		else if (phase == "Player2") {
			col = YELLOW;
			type = 3;
			horizontal = initSection;
			vertical = board.EmptySection(initSection);
			
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
		isEnd = true;
		gameStart = false;
		return;
	}

	//writes whose turn it is
	if (phase == "Player") {
		TurnText(3);
	}
	else if (phase == "Player2") {
		TurnText(4);
	}

	if (phase == "Player") {
		UserTurn();
		return;
	}
	if (phase == "Player2") {

		UserTurn();
		return;
	}

}

// should rework this, very inefficient
void Game::PlayerVSBot() {


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
		isEnd = true;
		gameStart = false;
		return;
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
	if (not isPlayer) {
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
	}
	else if (isPlayer) {
		if (phase == "Player") {
			phase = "Player2";
			confirmationPhase = "Unconfirmed";
			initSection = -1;
		}
		else if (phase == "Player2") {
			phase = "Player";
			confirmationPhase = "Unconfirmed";
			initSection = -1;
		}
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
		confirmationPhase = "Unconfirmed";
		
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
	else if (turn == 3) {
		message = "Player 1's Turn";
	}
	else if (turn == 4) {
		message = "Player 2's Turn";
	}
	DrawText(message.c_str(), 500, 10, FONTSIZE, BLACK);
	return;
}

void Game::CreateHighlight(int x) {
	if (confirmationPhase == "Confirmed" && !startAnimation) {
		Color type = phase == "Player" ? RED : YELLOW;
		DrawRectangle(85 + x * 95, 40, 75, 60, {255,255,255,120}); // Draw a gray rectangle to highlight the selected colu
		DrawRectangle(100 + x * 95, 49, CHECKERLENGTHS, CHECKERLENGTHS, type); // Draw a fake checker
		}
}


bool Game::Animate(int row, Color color,int location) {
	double currentAnimationTime = GetTime();
	double timeLeft = currentAnimationTime - animationTime;

	timeLeft *= 250;
	int y = static_cast<int>(timeLeft);
	velocity += 10 * timeLeft;

	y += velocity * timeLeft;

	if (y-7< location*95+100) {//-(CHECKERLENGTHS/2)

		DrawRectangle(100 + row * 95,  y+50 , CHECKERLENGTHS, CHECKERLENGTHS, color);
		return false; //still animating
	}
	
	velocity = 0.0;
	return true;//not animating anymore cuz done
}


