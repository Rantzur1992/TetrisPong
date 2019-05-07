#pragma once
#include "Ball.h"
#include "Screen.h"
#include "Color.h"

Ball::Ball()
{
	int rand = (std::rand() % 10) + 10;
	int i;
	for (i = 0; i < SIZE; i++)
	{
		giantBall[i].set(CENTER_SCREENX, rand, DEFAULT_SIGN);
	}
	BigBang();
}
void Ball::BigBang()
{
	//part 1
	giantBall[0].move(-1, -1);
	giantBall[1].move(0, -1);
	giantBall[2].move(1, -1);
	giantBall[3].move(2, -1);
	//part 2
	giantBall[4].move(-1, 0);
	giantBall[5].move(0, 0); // this is the 'center'
	giantBall[6].move(1, 0);
	giantBall[7].move(2, 0);
	//part 3
	giantBall[8].move(-1, 1);
	giantBall[9].move(0, 1);
	giantBall[10].move(1, 1);
	giantBall[11].move(2, 1);
}
void Ball::reset()
{
	iterations = 0;
	x40 = 0;
	state = 0;
	int rand = (std::rand() % 10) + 10;
	erase();
	for (int i = 0; i < SIZE; i++)
	{
		giantBall[i].set(CENTER_SCREENX, rand);
	}
	BigBang();
}
void Ball::draw()
{
	if (state == 2)
		setTextColor(Color::LIGHTRED);
	for (int i = 0; i < SIZE; i++)
	{
		if (i == 0 || i == 3 || i == 8 || i == 11)
		{
			giantBall[i].draw(EMPTY);
		}
		else
		{
			if (state == 1)
			{
				if (getX(0) % 3 == 0)
				{
					setTextColor(Color::LIGHTRED);
				}
				else if (getX(0) % 3 == 1)
					setTextColor(Color::RED);
				else setTextColor(Color::WHITE);
			}
			giantBall[i].draw();
		}
	}
	setTextColor(Color::WHITE);
}
void Ball::erase()
{
	for (int i = 0; i < SIZE; i++)
	{
		giantBall[i].erase();
	}
}
void Ball::setDirection(int newDir_x, int newDir_y)
{
	for (int i = 0; i < SIZE; i++)
		giantBall[i].move(newDir_x, newDir_y);

}
void Ball::move()
{
	//hit wall
	if (Screen::isOn_X_Edge(*this)) {
		dir_x *= -1;
	}
	if (Screen::isOn_Y_Edge(*this)) {
		dir_y *= -1;
	}
	this->erase();
	for (int i = 0; i < SIZE; i++)
	{
		giantBall[i].move(dir_x, dir_y);
	}
	this->draw();
}
void Ball::animateRightHit(Board &board)
{
	animateRightAfterHit(board);
}
void Ball::animateLeftHit(Board &board)
{
	animateLeftAfterHit(board);
}


//----------- HIT ANIMATION FUNCTIONS -----------//
void Ball::animateRightAfterHit(Board &board)
{
	int i;
	//Coming from the bottom
	if (dir_y == up)
	{
		for (i = 0; i < SIZE; i++)
		{
			if (i == 0 || i == 3 || i == 8 || i == 11)
				giantBall[i].erase();
			else
				giantBall[i].draw();
		}
	}

	//Coming from the top
	if (dir_y == 1)
	{
		for (i = 0; i < SIZE; i++)
		{
			if (i == 0 || i == 1 || i == 8 || i == 11)
				giantBall[i].erase();
			else
				giantBall[i].draw();
		}
	}
	board.draw();
	Sleep(AnimationSpeed);
}
void Ball::animateLeftAfterHit(Board &board)
{
	int i;
	//Coming from the bottom
	if (dir_y == -1)
	{
		for (i = 0; i < SIZE; i++)
		{
			if (i == 0 || i == 3 || i == 10 || i == 11)
				giantBall[i].erase();
			else
				giantBall[i].draw();
		}
	}

	//Coming from the top
	if (dir_y == 1)
	{
		for (i = 0; i < SIZE; i++)
		{
			if (i == 2 || i == 3 || i == 8 || i == 11)
				giantBall[i].erase();
			else
				giantBall[i].draw();
		}
	}
	board.draw();
	Sleep(AnimationSpeed);
}
void Ball::animateDiagonalRight(Board & board)
{
	int i;
	//Coming from the bottom
	if (dir_y == up)
	{
		for (i = 0; i < SIZE; i++)
		{
			if (i == 0 || i == 3 || i == 8 || i == 11)
				giantBall[i].erase();
			else
				giantBall[i].draw();
		}
	}

	//Coming from the top
	if (dir_y == down)
	{
		for (i = 0; i < SIZE; i++)
		{
			if (i == 0 || i == 9 || i == 8 || i == 11)
				giantBall[i].erase();
			else
				giantBall[i].draw();
		}
	}
	board.draw();
	Sleep(AnimationSpeed);
}
void Ball::animateDiagonalLeft(Board & board)
{
	int i;
	//Coming from the bottom
	if (dir_y == up)
	{
		for (i = 0; i < SIZE; i++)
		{
			if (i == 2 || i == 3 || i == 8 || i == 11)
				giantBall[i].erase();
			else
				giantBall[i].draw();
		}
	}

	//Coming from the top
	if (dir_y == down)
	{
		for (i = 0; i < SIZE; i++)
		{
			if (i == 2 || i == 0 || i == 3 || i == 11)
				giantBall[i].erase();
			else
				giantBall[i].draw();
		}
	}
	board.draw();
	Sleep(AnimationSpeed);
}

//----------- DIAGONAL FUNCTIONS -----------//

//Animation after RIGHT diagonal hit
void Ball::afterHitDiaRight()
{
	int i;

	// Coming diagonal from the TOP
	if (dir_y == down)
	{
		for (i = 0; i < SIZE; i++)
		{
			if (i == 2 || i == 3 || i == 0 || i == 11)
				giantBall[i].erase();
			else
				giantBall[i].draw();
		}
	}

	// Coming diagonal from the BOTTOM
	if (dir_y == up)
	{
		for (i = 0; i < SIZE; i++)
		{
			if (i == 2 || i == 3 || i == 8 || i == 11)
				giantBall[i].erase();
			else
				giantBall[i].draw();
		}
	}
	Sleep(AnimationSpeed);
}
//Animation after LEFT diagonal hit
void Ball::afterHitDiaLeft()
{
	int i;
	// Coming diagonal from the TOP
	if (dir_y == down)
	{
		for (i = 0; i < SIZE; i++)
		{
			if (i == 2 || i == 3 || i == 0 || i == 11)
				giantBall[i].erase();
			else
				giantBall[i].draw();
		}
	}

	// Coming diagonal from the BOTTOM
	if (dir_y == up)
	{
		for (i = 0; i < SIZE; i++)
		{
			if (i == 2 || i == 3 || i == 8 || i == 11)
				giantBall[i].erase();
			else
				giantBall[i].draw();
		}
	}
	Sleep(AnimationSpeed);
}
void Ball::BombHitGraveAnimation(int clear)
{
	for (int i = 0; i < SIZE; i++)
	{
		if (i == 0 || i == 3 || i == 8 || i == 11)
		{
			giantBall[i].draw(EMPTY);
		}
		else
		{
			if (clear == 1) {
				giantBall[i].draw(EMPTY);
				Sleep(30);
			}
			else giantBall[i].draw((char)254);
		}
	}
}

void Ball::BombHitBoardAnimation(int clear)
{
	BombHitGraveAnimation(clear);
}

