#pragma once
#include "board.h"
#include <string>

class Game {
public:
	Game();
	Board board;
	int UserInput();
	void Draw();
	std::string phase;
	std::string second_phase;
	int init_section;
};