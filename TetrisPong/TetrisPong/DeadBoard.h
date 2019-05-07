#pragma once
#include "Board.h"

class DeadBoard {
	Point up, down;
	enum { right = 1, left = -1, LeftBorder = 20, DropMotionSpeed = 40 };

public:

	DeadBoard(const Board &b) :up({ b.getX(),b.getY() - 1 ,b.getFigure() })
		, down({ b.getX(),b.getY() + 1 ,b.getFigure() }) {}
	void draw();
	int getX()const
	{
		return up.getX();
	}
	int getUpperBorder()const
	{
		return up.getY();
	} // Returns the upper Y value of the point
	int getBottomBorder() const
	{
		return down.getY();
	} // Returns the lower Y value of the point
	int whichPlayer() const
	{
		if (up.getX() <= LeftBorder)
			return left;
		else return right;
	}
	void erase();
	void drop()
	{
		int dir = whichPlayer();
		erase();
		up.move(dir, 0);
		down.move(dir, 0);
		draw();
		Sleep(DropMotionSpeed);
	} // Drops the dead body of the losing board to the left or right

	bool gotHit(const Point & p)
	{
		return ((down.getX() == p.getX()) &&
			(down.getY() >= p.getY() && up.getY() <= p.getY()));
	}
};