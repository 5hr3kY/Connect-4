#pragma once
#include <raylib.h>


class Board {
public:
	Board();
	int numRows;
	int numCols;
	int grid[6][7];
	void Draw();
	void ClearBoard();

	void AddChip(int row, int column, char type);

	void Update(int area, char type);

	void Initialize();
private:

};