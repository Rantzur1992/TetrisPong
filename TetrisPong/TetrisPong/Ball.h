#pragma once
#include "Point.h"
#include "Board.h"
#include "Color.h"
const char DEFAULT_SIGN = 'O',EMPTY = ' ';

class Ball {
	Point giantBall[12];
	enum {AnimationSpeed= 50};
	enum {Regular, BecomingBomb , Bomb};
	int dir_x = left, dir_y = down;
	int state=0;

public:
	/* This are public because game manager must handle this aswell as the ball*/
	int iterations = 0;
	int x40 = 0;

	enum {right=1,left = -1,up = -1,down = 1, SIZE = 12 ,CENTER_SCREENX = 39,Center=5};
	Ball(); // Constructor in the CPP file
	int getY(const int & i)const {
		return giantBall[i].getY();
	}
	int getX(const int & i)const {
		return giantBall[i].getX();
	}
	char getFigure()const {
		return giantBall[Center].getFigure();
	}
	int getXDirection()const {
		return dir_x;
	}
	int getYDirection()const {
		return dir_y;
	}
	int getState()const
	{
		return state;
	}
	void setState(int newState)
	{
		if (newState <= 2 && newState >= 0)
			state = newState;
	}
	void BigBang(); //Spread the points into ball shape
	void reset(); // Reset the ball into the orginial position
	void draw(); // Draw the ball
	void setDirection(int newDir_x, int newDir_y); //Set new direction for the ball (Iterate through the points)
	void move(); // Move the ball
	void erase(); // Erase the ball from the screen
	void changeYDirection() 
	{
		dir_y *= -1;
	}
	void changeXDirection() 
	{
		dir_x *= -1;
	}
	// returns most front corner
	int getRelevantCorner() const  
	{
		if (getXDirection() == right)
			return 7;
		else return 4;
	} 

	//-- Animation Functions --//
	void animateRightHit(Board &board); // Animate the right side hit
	void animateRightAfterHit(Board &board); // Animate the right side after hit
	void animateLeftHit(Board &board); // Animate the left side hit
	void animateLeftAfterHit(Board &board); // Animate the left side after the hit
	void animateDiagonalRight(Board &board); //Animate the right diagonal colision
	void animateDiagonalLeft(Board &board); // Animate the left diagonal colision
	void afterHitDiaRight(); //Animate the  RIGHT aftermath of diagonal colison
	void afterHitDiaLeft();	// //Animate the LEFT aftermath of diagonal colison
	void BombHitBoardAnimation(int clear = 0);
	void BombHitGraveAnimation(int clear = 0);
	void setTextColor(Color colorToSet) {
		SetConsoleTextAttribute(GetStdHandle(STD_OUTPUT_HANDLE), (int)colorToSet);
	}
};
