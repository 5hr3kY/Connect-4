#pragma once
#include "config.h"


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