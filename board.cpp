#include "board.h"


Board::Board() {
	numRows = 6;
	numCols = 7;
	Initialize();
}

// function makes the board all empty
void Board::Initialize() {

	for (int row = 0; row < numRows; row++)
	{
		for (int column = 0; column < numCols; column++)
		{
			grid[row][column] = 0;
		}
	}
	
}

/*
Draws the board
1 is the blocker
2 is red , player one
3 is yellow, player two or bot
0 is empty and default
*/
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

// If I want to reset the board for like mutiple games, use this function and maybe modify it in the future
void Board::ClearBoard(){
	Initialize();
	}


// adds a checker at the specified location
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



// Updates the board with the chip in the lowest empty section of the column
// might delete this as it is kind of redundant with empty section function
void Board::Update(int area, char type) {
	int y = 0;
	for (y = numCols - 1; y >= 0; y--) {
		if (grid[y][area] == 0) {
			AddChip(area,y, type);
			break;
		}
	}
}

//returns the lowest empty section in the column, if there is no empty section, return -1 
//important for player use
int Board::EmptySection(int x) {
	int y;
	for (y = numRows-1; y>= 0; y--) {
		if (grid[y][x] == 0) {

			return y;
		}
	}
		return -1;

}

// after each person goes, this should be called to see if anyone won (win requirement is connect 4 rules)
int Board::CheckWinner() {
	int winner = 0;
	for (int person = 2; person <= 3; person++) {
		//check horizontal
		for (int y = 0; y < numRows; y++) {
			for (int x = 0; x < numCols; x++) {
				if (grid[y][x] == person) {
					if (grid[y][x + 1] == person && grid[y][x + 2] == person && grid[y][x + 3] == person) {
						winner = person;
						break;
					}
					else if (grid[y + 1][x] == person && grid[y + 2][x] == person && grid[y + 3][x] == person) {
						winner = person;
						break;
					}
					else if (grid[y + 1][x + 1] == person && grid[y + 2][x + 2] == person && grid[y + 3][x + 3] == person) {
						winner = person;
						break;
					}
					else if (grid[y - 1][x + 1] == person && grid[y - 2][x + 2] == person && grid[y - 3][x + 3] == person) {
						winner = person;
						break;
					}

				}
			}
		}
	}
	return winner;

}