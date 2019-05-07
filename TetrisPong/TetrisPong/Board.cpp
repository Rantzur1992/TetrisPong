#pragma once
#include "Board.h"

void Board::draw()
{
	Point temp = down;
	temp.draw();
	while (temp != up) {
		temp.move(0, -1);
		temp.draw();
	}
}

void Board::erase()
{
	Point temp = up;
	while (temp != down)
	{
		temp.erase();
		temp.move(0, 1);
	}
	temp.erase();
}

void Board::drawBorder(int erase)
{
	Point Painter;
	char figure = '|';
	if (erase == 1)
	{
		figure = ' ';
	}
	Painter = Point(getX() + whichPlayer(), MAX_Y, figure);
	while (Painter.getY() != MIN_Y)
	{
		Painter.draw();
		Painter.move(0, -1);
	}
	Painter.draw();
}
