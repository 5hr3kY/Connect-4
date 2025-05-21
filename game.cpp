#include "game.h"
#include "board.h"

Game::Game()
{
	board = Board();
	phase = "Player";
	second_phase = "Unconfirmed";
}

int Game::UserInput() {
	int key = GetKeyPressed();

	switch (key) {
	case KEY_ONE:
		return 0;
	case KEY_TWO:
		return 1;
	case KEY_THREE:
		return 2;
	case KEY_FOUR:
		return 3;
	case KEY_FIVE:
		return 4;
	case KEY_SIX:
		return 5;
	case KEY_SEVEN:
		return 6;

	case KEY_ENTER:
		return 7;
	default:
		return -1;
	}
}

void Game::Draw() {
	board.Draw();
	if (phase == "Player") {
		int key=UserInput();
		if (second_phase == "Confirmed" && key == 7) {

			board.Update(init_section, 'R');
			second_phase = "Unconfirmed";
		}
		else if (key != 7 && key != -1) {
			second_phase = "Confirmed";
			init_section = key;
		}
	}
}