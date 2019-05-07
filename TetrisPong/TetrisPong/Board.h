#pragma once
#include "Point.h"

const char DEFAULT_UPKEY = 'w', DEFAULT_DOWNKEY = 's';
class Board {
	Point up, down;

protected:
	enum { right = 1, left = -1, SafeDistance = 5, LeftBorder = 20, MAX_Y = 24, MIN_Y = 4 };
public:
	//-- CONSTRUCTORS -- //
	Board(const Point& up1, const Point& down1) : down(down1), up(up1) {}
	//-- END OF CONSTRUCTORS -- //
	void draw();
	void drawBorder(int erase = 0);
	int getX()const 
	{
		return (up.getX());
	}
	int getY() const
	{
		return (up.getY()) + 1;
	}
	char getFigure() const
	{
		return (up.getFigure());
	}
	void reset(int x , int upY, int downY)
	{
		//drawBorder(1);
		up.set(x, upY);
		down.set(x, downY);
		//drawBorder();
	}
	int whichPlayer()const //Returns the current player
	{
		if (up.getX() <= LeftBorder)
			return left;
		else return right;
	}
	void push() //Pushes the player +1 on the X axis
	{
		drawBorder(1);
		up.move((-1)*whichPlayer(), 0);
		down.move((-1)*whichPlayer(), 0);
		drawBorder();
	}
	void pullBack(int distance) // Pulls back the player 5 blocks back
	{
		if (4 < getX() && getX() < 76)
		{
			drawBorder(1);
			for (int i = 0; i < distance; i++)
			{
				up.move(whichPlayer(), 0);
				down.move(whichPlayer(), 0);
			}
			drawBorder();
		}
	}
	void erase(); // Erases the board
	void moveUp()
	{
		down.erase();
		down.move(0, -1);
		up.move(0, -1);
		up.draw();
	}
	void moveDown()
	{
		up.erase();
		up.move(0, 1);
		down.move(0, 1);
		down.draw();
	}
	virtual void setPredection(int pred) {};
	virtual void setBombPressed(int pressed) {};
};