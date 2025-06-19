#include "checker.h"

Checker::Checker(int r, int c, int t) {
	row = r;
	column = c;
	type = t;
	color = NewColor();
	velocity = 0.0f;
}

Color Checker::NewColor() {
	switch (type) {
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
	return color;
}

void Checker::Draw() {
	DrawRectangle(column,row, CHECKERLENGTHS, CHECKERLENGTHS, color);
}



