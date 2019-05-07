#pragma once
#include "DeadBoard.h"
#include "Ball.h"
#include <list>

const char KABOOM_SIGN = (const char)254;
class GraveYard
{
	enum { noKaboom, Kaboom };
	enum { leftWall = 1, rightWall = 79, Empty = 0, Full = 7, on = 1, off = 0 };
	enum { right = 1, left = -1 };
	enum { KaboomMotionSpeed = 25 };
	list <list<DeadBoard>> nestedGrave;
	list <DeadBoard> singleColumn;
public:

	int getTopX(); //Returns the X value of the first columm
	void dropToTop(DeadBoard & b); //Drop the dead into the ocean(To the top)
	int insert(DeadBoard b); // Insert dead board in to the heap
	void initialize(DeadBoard & b); //Make empty list and drop the first dead board
	void TetrisKaboom(list<list<DeadBoard>>::iterator & column); // Exploding line animation(KABOOM!)
	bool insertedToSpace(DeadBoard& b, list<list<DeadBoard>>::iterator & column); //Checks if there is space for the board to be inserted , and save the column
	void addColumn(DeadBoard & b); //Adds a column to the graveyard
	void pushToColumn(DeadBoard & b, list<DeadBoard> & grave); // Insert a dead board into the column
	void printKaboom(const DeadBoard & down, const DeadBoard & up); //Animation
	void moveHeap(list<list<DeadBoard>>::iterator & kaboom); //Drop heap after kaboom
	void draw(int clear = 0); // Draws the graveyard
	void clear(); // Clears the graveyard
	bool graveIsEmpty()
	{
		return (nestedGrave.size() == Empty);
	}
	bool columnIsFull(list<list<DeadBoard>>::iterator & column)
	{
		return ((*column).size() == Full);
	}
	list<list<DeadBoard>> ::iterator findColumn(int x); // returns iterator to column of dead boards by x
	int colisionCheck(Ball & b); // checks if ball is hit deadboard
	void colisionKaboom(int x); // ball hit deadboard animation
};

