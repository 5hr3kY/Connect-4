#pragma once
#include <raylib.h>
#include <iostream>

class Board {
public:
	Board();
	int numRows;
	int numCols;
	int grid[6][7];

	void Draw();
	void ClearBoard();

	void AddChip(int x, int y, char type);

	void Update(int area, char type);

	void Initialize();


	int EmptySection(int x);

	int CheckWinner();


};