#pragma once
#include "board.h"


//This includes how the logic of the game works

class Game {
public:
	Game();
	Board board;

	
	int UserInput();

	void Draw();
	void PlayerVSBot();
	void PlayerVSPlayer();
	//for confirmation for player turn
	std::string phase;
	std::string confirmationPhase;
	int initSection;

	// shows where the user is highlighting
	void CreateHighlight(int x);

	void NewTurn();

	// can make these into classes?
	void BotTurn();
	void UserTurn();

	// stuff for winning
	int winner;
	const char* message{};


	//text
	void TurnText(int turn);

	// stuff for making animation
	bool finishAnimation;
	bool startAnimation;
	bool Animate(int row,Color color, int location);
	double animationTime{ GetTime()};
	bool velocity;

	// against a player? false is against bot
	bool isPlayer;

	// checks if the game has started so it can start board or the menu
	bool gameStart;
	//checks if the game is over
	bool isEnd;

	int botX;
	int botY;

	void EndScreen();
	void BeginningScreen();

};