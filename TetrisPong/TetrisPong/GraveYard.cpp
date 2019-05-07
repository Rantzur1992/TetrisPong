#pragma once
#include "GraveYard.h"

int GraveYard::insert(DeadBoard b)
{
	if (graveIsEmpty())
	{
		initialize(b);
	}
	else {
		dropToTop(b);
		list<list<DeadBoard>>::iterator column;
		if (insertedToSpace(b, column) == false)
			addColumn(b);
		else
		{
			if (columnIsFull(column))
			{
				TetrisKaboom(column);
				return Kaboom;
			}
		}
	}
	return noKaboom;
}
void GraveYard::TetrisKaboom(list<list<DeadBoard>>::iterator & column)
{
	list<DeadBoard>::iterator down, up;
	down = (*column).begin();
	up = (*column).end(); up--;
	//Kaboom Animation
	printKaboom((*down), (*up));
	(*column).erase((*column).begin(), (*column).end());
	column = nestedGrave.erase(column);

	//Move Animation
	if (nestedGrave.size() != Empty && column != nestedGrave.end())
	{
		moveHeap(column);
	}
}
void GraveYard::addColumn(DeadBoard & b)
{
	singleColumn.push_back(b);
	nestedGrave.push_back(singleColumn);
	singleColumn.erase(singleColumn.begin(), singleColumn.end());
}
void GraveYard::initialize(DeadBoard & b)
{
	if (b.whichPlayer() == left)
	{
		while (b.getX() != leftWall)
		{
			b.drop();
		}
	}
	else
	{
		while (b.getX() != rightWall)
		{
			b.drop();
		}
	}

	singleColumn.push_back(b);
	nestedGrave.push_back(singleColumn);
	singleColumn.erase(singleColumn.begin(), singleColumn.end());
}
bool GraveYard::insertedToSpace(DeadBoard & b, list<list<DeadBoard>>::iterator & emptyColumnSpace)
{
	bool inserted = false, stuck = false;
	list<list<DeadBoard>>::iterator column = nestedGrave.end();	column--;
	list<DeadBoard> ::iterator down, up;
	while (stuck != true)
	{

		up = (*column).end(); up--;
		down = (*column).begin();

		if ((*down).getBottomBorder() < b.getUpperBorder())
		{
			inserted = true;
			emptyColumnSpace = column;
			b.drop();
		}
		else if ((*up).getUpperBorder() > b.getBottomBorder())
		{
			inserted = true;
			emptyColumnSpace = column;
			b.drop();
		}
		else
		{
			if (up == down)
			{
				stuck = true;
			}
			else
			{
				down = (*column).begin();
				up = (*column).begin();	up++;
				for (int i = 0; i < (int)(*column).size() - 1; i++)
				{
					if ((*down).getUpperBorder() > b.getBottomBorder())
					{
						if ((*up).getBottomBorder() < b.getUpperBorder())
						{
							inserted = true;
							emptyColumnSpace = column;
							b.drop();
						}
						else stuck = true;
					}
					down++; up++;
				}
				if (inserted == false) { stuck = true; }
			}
		}
		if (nestedGrave.begin() != column)
			column--;
		else stuck = true;
	}
	if (inserted)
	{
		pushToColumn(b, (*emptyColumnSpace));
	}
	return inserted;
}
void GraveYard::printKaboom(const DeadBoard & down, const DeadBoard & up)
{
	Point painter = Point(down.getX(), down.getBottomBorder(), KABOOM_SIGN);
	while (painter.getY() != up.getUpperBorder())
	{
		painter.draw();
		painter.move(0, -1);
		Sleep(KaboomMotionSpeed);
	}
	painter.draw();
	Sleep(KaboomMotionSpeed);
	while (painter.getY() != down.getBottomBorder())
	{
		painter.erase();
		painter.move(0, 1);
	}
	painter.erase();
}
void GraveYard::moveHeap(list<list<DeadBoard>>::iterator & kaboom)
{
	list<list<DeadBoard>>::iterator top = nestedGrave.end(); top--;
	while (kaboom != top)
	{
		for (DeadBoard & b : (*kaboom))
		{
			b.drop();
		}
		kaboom++;
	}
	for (DeadBoard & b : (*kaboom))
	{
		b.drop();
	}
}
void GraveYard::dropToTop(DeadBoard & b)
{
	while (b.getX() != getTopX() - (b.whichPlayer()))
	{
		b.drop();
	}
}
int GraveYard::getTopX()
{
	list<list<DeadBoard>>::iterator column = nestedGrave.end();
	column--;
	list<DeadBoard> ::iterator down = (*column).begin();
	return (*down).getX();
}
void GraveYard::pushToColumn(DeadBoard & b, list<DeadBoard> & grave)
{
	list<DeadBoard> ::iterator down, up;
	down = (grave).begin();
	up = (grave).end();	up--;

	if ((*down).getBottomBorder() < b.getUpperBorder())
	{
		grave.push_front(b);
	}
	else if ((*up).getUpperBorder() > b.getBottomBorder())
	{
		grave.push_back(b);
	}
	else
	{
		up = (grave).begin(); up++;
		for (int i = 0; i < (int)grave.size() - 1; i++)
		{
			if ((*down).getUpperBorder() > b.getBottomBorder()
				&& (*up).getBottomBorder() < b.getUpperBorder())
			{
				grave.insert(up, b);
				break;
			}
			else { up++; down++; }
		}
	}
}
void GraveYard::draw(int clear)
{
	for (auto & column : nestedGrave)
	{
		for (auto & b : (column))
		{
			if (clear == off)
				b.draw();
			else b.erase();
		}
	}
}
void GraveYard::clear()
{
	draw(on);
	for (auto & column : nestedGrave)
	{
		column.clear();
	}
	nestedGrave.clear();
}
list<list<DeadBoard>> ::iterator GraveYard::findColumn(int x)
{
	list<list<DeadBoard>>::iterator foundedColumn = nestedGrave.begin();
	for (int i = 0; i < (int)(nestedGrave).size() - 1; foundedColumn++)
	{
		if ((*(*foundedColumn).begin()).getX() == x)
		{
			return foundedColumn;
		}
	}
	if ((*(*foundedColumn).begin()).getX() == x)
	{
		return foundedColumn;
	}
	return nestedGrave.end();
}
int GraveYard::colisionCheck(Ball & b)
{

	if (b.getX(b.getRelevantCorner()) == 1)
	{
		return 1;
	}
	if (b.getX(b.getRelevantCorner()) == 79)
	{
		return 79;
	}
	else {
		bool gotHit = false;
		for (auto & column : nestedGrave)
		{
			for (auto & deadB : column)
			{
				for (int i = 0; i < 12; i++)
				{
					if (deadB.gotHit({ b.getX(i),b.getY(i) }))
					{
						return b.getX(i);
					}
				}
			}
		}
	}
	return -1;
}

void GraveYard::colisionKaboom(int x)
{
	if (nestedGrave.size() > 0)
	{
		list<list<DeadBoard>> ::iterator column;
		column = findColumn(x);
		if (column != nestedGrave.end())
			TetrisKaboom(column);
	}
}

