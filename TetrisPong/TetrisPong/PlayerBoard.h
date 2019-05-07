#pragma once
#include "Board.h"
#include "Screen.h"

class PlayerBoard : public Board 
{
	int bombPressed = 0;

	enum { kbdown, kbup , bomb };
	enum { right = 1, left = -1, SafeDistance = 5, LeftBorder = 20, MAX_Y = 24, MIN_Y = 4 };
	char kbChars[4]; //The chars that might be pressed by the user.

public:
	PlayerBoard(const Point& up, const Point& down, char upKey, char downKey , char bombKey) : Board(up,down)
	{
		kbChars[kbdown] = downKey;
		kbChars[kbup] = upKey;
		kbChars[bomb] = bombKey;
		kbChars[4] = '\0';
	}
	void handleKey(char c)
	{
		if (c == kbChars[kbdown] && (this->getY() < Screen::MAX_Y - 1))
			moveDown();
		if (c == kbChars[kbup] && (this->getY() > Screen::MIN_Y + 1))
			moveUp();
		if (c == kbChars[bomb] && bombPressed == 0)
			bombPressed = 1;
	}
	const char* getKbChars() {
		return kbChars;
	}

	int getBombPressed()
	{
		return bombPressed;
	}
	void setBombPressed(int pressed)
	{
		bombPressed = pressed;
	}
};