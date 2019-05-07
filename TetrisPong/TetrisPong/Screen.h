#pragma once
#include "Ball.h"
class Screen
{
	enum{Top=1,Bottom =10,Left=0,Right=3};
public:
	enum {MIN_X = 1 , MAX_X = 79, MIN_Y = 4 , MAX_Y = 24};
	static bool isOn_Y_Edge(const Ball & ball)
	{
		return (ball.getY(Top) == MIN_Y || ball.getY(Bottom) == MAX_Y);
	}

	static bool isOn_X_Edge(const Ball & ball)
	{
		return ( ball.getX(Right)== MAX_X || ball.getX(Left) == MIN_X );
	}
};