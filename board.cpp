#include "board.h"


Board::Board() {
	numRows = 6;
	numCols = 7;
	Initialize();
}

void Board::Initialize() {
	for (int row = 0; row < numRows; row++)
	{
		for (int column = 0; column < numCols; column++)
		{
			grid[row][column] = 0;
		}
	}
	
}


void Board::Draw() {
	//draw the area
	Color color; 
	DrawRectangle(50, 100, 700, 600, GRAY);
	for (int y = 0; y < numRows; y++) {
		for (int x = 0; x< numCols;x++) {	
			switch (grid[y][x]) {
			case 1:
				color = BLUE;
				break;
			case 2:
				color = RED;
				break;
			case 3:
				color = YELLOW;
				break;
			default:
				color = WHITE;
				break;
			}

				DrawCircle(100 + x * 100, 150 + y * 100, 35, color);
			}
	}
}

void Board::ClearBoard(){
	Initialize();
	}

void Board::AddChip(int x, int y, char type) {
	// type is either 'B', 'R' or 'Y'
	if (type == 'B') {
		grid[y][x] = 1;
	}
	else if (type == 'R') {
		grid[y][x] = 2;
	}
	else if (type == 'Y') {
		grid[y][x] = 3;
	}
}


void Board::Update(int area, char type) {
	int y = 0;
	for (y = numCols - 1; y >= 0; y--) {
		if (grid[y][area] == 0) {
			AddChip(area,y, type);
			break;
		}
	}
}


int Board::EmptySection(int x) {
	int y;
	for (y = numRows-1; y>= 0; y--) {
		if (grid[y][x] == 0) {

			return y;
		}
	}
		return -1;

}

bool Board::IsEmpty(int x, int y) {
	if (grid[y][x] == 0) {
		return true;
	}
	else {
		return false;
	}
}