#pragma once
#include "Board.h"
#include "Ball.h"

class PcBoard : public Board
{
	char diff='a';
	int prediction;
public:
	PcBoard(const Point& up, const Point& down) : Board(up, down) { prediction = -1; }
	enum { BEST = 'a' , GOOD = 'b' , NOVICE = 'c' };
	void calculate(const Ball&);
	void move();
	int getPrediction();
	void setPredection(int pred);
	void setDiff(char diff) { (*this).diff = diff; }
};