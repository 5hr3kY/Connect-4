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
	for (int row = 0; row < numRows; row++) {
		for (int column = 0; column < numCols; column++) {	
			switch (grid[row][column]) {
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

				DrawCircle(100 + column * 100, 150 + row * 100, 35, color);
			}
	}
}

void Board::ClearBoard(){
	Initialize();
	}

void Board::AddChip(int row, int column, char type) {
	// type is either 'B', 'R' or 'Y'
	if (type == 'B') {
		grid[row][column] = 1;
	}
	else if (type == 'R') {
		grid[row][column] = 2;
	}
	else if (type == 'Y') {
		grid[row][column] = 3;
	}
}


void Board::Update(int area, char type) {
	int y = 0;
	for (int rows =numRows; rows > 0; rows--) {
		if (grid[rows][area] == 0) {
			y = rows;
			break;
		}
	}
	AddChip(y, area, type);
}