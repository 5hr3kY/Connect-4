#pragma once
#include "board.h"

class Game {
public:
	Game();
	Board board;
	int UserInput();
	void Draw();
	std::string phase;
	std::string confirmationPhase;
	int initSection;

	void NewTurn();

	void BotTurn();
	void UserTurn();
	int round;
	int previousRound;
	int winner;
	const char* message{};

};