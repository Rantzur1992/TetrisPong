#pragma once
#include "Gotoxy.h"
const char EMPTY_SIGN = ' ';

class Point {
	enum { null = -1 };
	char figure;
	int x, y;

public:
	Point() : x(null), y(null), figure(EMPTY_SIGN) {}
	Point(int x1, int y1, char ch = EMPTY_SIGN) : x(x1), y(y1), figure(ch) { };

	int getX()const {
		return x;
	}
	int getY()const {
		return y;
	}
	char getFigure()const { // Get the char sign of the point
		return figure;
	}
	void move(int dir_x, int dir_y) {
		x += dir_x;
		y += dir_y;
	}
	void set(int newX, int newY, char newFigure = EMPTY_SIGN) // Set the X and Y of the given point
	{
		if (newFigure != EMPTY_SIGN)
			figure = newFigure;
		x = newX;
		y = newY;
	}
	void draw()
	{
		gotoxy(x, y);
		std::cout << figure;
	}
	void draw(char c) // Draw overloaded with a spefic char
	{
		gotoxy(x, y);
		std::cout << c;
	}
	void erase()
	{
		gotoxy(x, y);
		std::cout << (const char)EMPTY_SIGN;
	}
	void eraseMiddle() // Erase the middle point of the board
	{
		gotoxy(x, y + 1);
		std::cout << (const char)EMPTY_SIGN;
	}
	bool operator!=(const Point& p) const {
		return x != p.x || y != p.y;
	}
};