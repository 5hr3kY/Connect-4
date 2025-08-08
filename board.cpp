#include "board.h"
#include "config.h"
#include "checker.h"

Board::Board() {
	numRows = 6;
	numCols = 7;
	Initialize();

}

// function makes the board all empty
void Board::Initialize() {
	checkers.clear();
	for (int column = 0; column <= numCols; column++)
	{
		std::vector<Checker> col;
		for (int rows = 0; rows <= numRows; rows++){
		
			col.push_back(Checker( 150+(column * 95), 100+(rows*95), 0)); //100,150
		}
		checkers.push_back(col);
	}
	
}

/*
Draws the board
1 is the blocker
2 is red , player one
3 is yellow, player two or bot
0 is empty and default
*/

void Board::Draw1() {
	//draw the area

	for (int y = 0; y < numRows; y++) {
		for (int x = 0; x < numCols; x++) {
			checkers[y][x].Draw();//checkers[y][x]=Checker(100 + x * 95, 150 + y * 95, checkers[y][x]);
		}
	}
}
void Board::Draw2(){
	
	for (int y = 0; y <= numRows; y++) {
		DrawRectangle(50, 100 + y * 95, 700, 50, GRAY);
	}

	for (int x = 0; x <= numCols; x++) {
		DrawRectangle(50 + x * 95, 100, 50, 600, GRAY);
	}


}




// adds a checker at the specified location
void Board::AddChip(int x, int y, int type) {

	checkers[y][x].type = type;

	checkers[y][x].color = checkers[y][x].NewColor();
}



// Updates the board with the chip in the lowest empty section of the column
// might delete this as it is kind of redundant with empty section function
void Board::Update(int area, char type) {
	int y = 0;
	for (y = numCols - 1; y >= 0; y--) {
		if (checkers[y][area].type == 0) {
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
		if (checkers[y][x].type == 0) {

			return y;
		}
	}
		return -1;

}


int Board::CheckWinner() {
	
	int person;
	//check horizontal
	for (int y = 0; y < numRows; y++) {
		for (int x = 0; x < numCols; x++) {

			person = checkers[y][x].type;
			if (person == 0) continue; // skip empty spaces


			//horizontal check
			if (x <= 3) {
				//check down
				if (checkers[y][x + 1].type == person && checkers[y][x + 2].type == person && checkers[y][x + 3].type == person) return person;

				// diagonal up
				else if (y > 2) {
					if (checkers[y - 1][x + 1].type == person && checkers[y - 2][x + 2].type == person && checkers[y - 3][x + 3].type == person) return person;

				}
			}

			//vertical check
			if (y <= 2) {
				//check down
				if (checkers[y + 1][x].type == person && checkers[y + 2][x].type == person && checkers[y + 3][x].type == person) return person;

				//diagonal down
				else if (x <= 3) {
					if (checkers[y + 1][x + 1].type == person && checkers[y + 2][x + 2].type == person && checkers[y + 3][x + 3].type == person) return person;
				}

			}
		}
	}
	// nobody won yet
	return 0;
}