#pragma once
#include "board.h"

class Game {
public:
	Game();
	Board board;

	
	int UserInput();

	void Draw();

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



	int botX;
	int botY;
};