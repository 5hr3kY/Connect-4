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

	void AddChip(int x, int y, char type);

	void Update(int area, char type);

	void Initialize();

	bool IsEmpty(int x, int y);

	int EmptySection(int x);
private:

};