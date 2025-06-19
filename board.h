#pragma once
#include <raylib.h>
#include <iostream>
#include <vector>
#include "checker.h"


class Board {
public:
	Board();
	int numRows;
	int numCols;
	int grid[6][7];
	std::vector<std::vector<Checker>> checkers;
	void Draw1();
	void Draw2();

	void AddChip(int x, int y, int type);

	void Update(int area, char type);

	void Initialize();

	
	int EmptySection(int x);

	int CheckWinner();


};