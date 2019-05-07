#pragma once
#include "PcBoard.h"
#include "Screen.h"

void PcBoard::calculate(const Ball &b)
{
	int miss = 0;
	int deviation = 0;
	int relevantCorner, increment;
	int lastPoint;

	if (diff == GOOD)
		miss = std::rand() % 40;
	if (diff == NOVICE)
		miss = std::rand() % 10;

	//no prediction
	if (prediction == -1 && (b.getXDirection() == whichPlayer())) 
	{
		if (b.getXDirection() == -1)
			relevantCorner = 4;
		else relevantCorner = 7;
		int Xdistance = abs(b.getX(relevantCorner) - getX()) - 1;
		increment = b.getYDirection();
		lastPoint = b.getY(relevantCorner);
		for (int i = 0; i < Xdistance; i++)
		{
			lastPoint += increment;
			if (lastPoint == MIN_Y + 1 ||
				lastPoint == MAX_Y  - 1)
				increment *= (-1);
		}
		prediction = lastPoint;
		if (miss == 0 && diff != BEST)
			prediction += std::rand() % 2 + 3;
	}
	else //prediction exist
	{
		//prediction isnt relevant
		if (b.getXDirection() == whichPlayer()*(-1))
			prediction = -1;

	}
}

void PcBoard::move()
{
	if (prediction != -1)
	{
		if (getY() > (prediction) && (getY() > Screen::MIN_Y + 1))
			moveUp();
		else if (getY() < (prediction) && (getY() < Screen::MAX_Y - 1))
			moveDown();
	}
}

int PcBoard::getPrediction()
{
	return prediction;
}

void PcBoard::setPredection(int pred)
{
	prediction = pred;
}





