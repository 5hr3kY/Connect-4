#pragma once
#include "config.h"

//this is primarily for the pieces and their functioning


class Checker {
public:
	int row;
	int column;
	int type;
	Color color;
	Checker(int r, int c, int t);
	Color NewColor();
	void Draw();
	double animationTime{ GetTime() };
	double velocity;
};