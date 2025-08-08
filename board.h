#pragma once
#include <raylib.h>
#include <iostream>
#include <vector>
#include "checker.h"


//this creates the board logic that can be manipulated

class Board {
public:
	Board();
	int numRows;
	int numCols;
	std::vector<std::vector<Checker>> checkers;
	void Draw1();
	void Draw2();

	void AddChip(int x, int y, int type);

	void Update(int area, char type);

	void Initialize();

	
	int EmptySection(int x);

	int CheckWinner();

};