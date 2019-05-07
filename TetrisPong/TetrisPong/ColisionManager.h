#pragma once
#include "GameManager.h"
#include "GraveYard.h"

class ColisionManager
{
	enum { BallMotionSpeed = 100 };
	enum { FullContact = 3, PartialContact = 2, AlmostMissContact = 1, Kaboom = 1 };
	enum { Contact = 2, DiagnoalContact = 1, Miss = 0 };
	enum { left = -1, right = 1, fromUp = 1, fromDown = -1 };
	enum { leftCorner = 4, rightCorner = 7 };
	enum { Regular, BecomingBomb, Bomb };

public:
	void colisionNavigation(Board & p1, Board & p2, Ball& b, GraveYard & Gravep1, GraveYard & Gravep2);
	//----------- HIT REACTIONS FUNCTIONS -----------//
	void regularBallColisionReaction(Ball & b, Board & p, GraveYard & grave, int colisionType);
	void BecomingBombGraveColision(Ball & b, Board & p, GraveYard & grave);
	void BecomingBombBoardColision(Ball & b, Board & p, GraveYard & grave, int colisionType);
	void BombGraveColisionReaction(Ball & b, Board & p, GraveYard & grave, int  columnHit);
	void BombBoardColisionReaction(Ball & b, Board & p, GraveYard & grave);

	 // checks if ball on the board X
	bool borderTouch(const Ball & b, const Board & p)
	{
		int relevantCorner = b.getRelevantCorner();
		return b.getX(relevantCorner) == p.getX();
	}
	//Checks special miss and 'fix' it for best gaming
	void fixProblematicContact1(Board & p, Ball& b)
	{
		if (b.getX(1) == p.getX())
		{
			if (b.getY(1) == p.getY() + 2 ||
				b.getY(9) == p.getY() - 2)
			{
				b.changeYDirection();
			}
		}
		if (b.getX(2) == p.getX())
		{
			if (b.getY(2) == p.getY() + 2 ||
				b.getY(10) == p.getY() - 2)
			{
				b.changeYDirection();
			}
		}
	}
	//Checks special miss and 'fix' it for best gaming
	void fixProblematicContact2(Board & p, Ball& b,GraveYard & grave)
	{
		if (borderTouch(b, p))
		{
			int relevantCorner = b.getRelevantCorner();
			if ((b.getY(relevantCorner) + 3 == p.getY() && b.getYDirection() == 1) || 
			(b.getY(relevantCorner) - 3 == p.getY() && b.getYDirection() == -1))
			{
				if (b.getState() == 2)
				{
					BombBoardColisionReaction(b, p, grave);
				}
				else // ball isnt a bomb
				{
					b.setState(0);
					if (b.getXDirection() == right)
						b.afterHitDiaRight();
					else b.afterHitDiaLeft();
					b.changeXDirection();
					b.changeYDirection();
					b.move();
				}
			}
		}
	}
	//Checks for a diagonal colison of board and ball
	bool diagonalColision(const Ball & b, const Board & p)
	{
		int center = p.getY();
		int upperCorner = 0, bottomCorner = 0;
		if (p.whichPlayer() == left)
		{
			upperCorner = 0;
			bottomCorner = 8;
		}
		else // player p2 (right)
		{
			upperCorner = 3;
			bottomCorner = 11;
		}
		return 	(((b.getYDirection() == fromDown) && (b.getY(upperCorner) == center)) ||
			((b.getYDirection() == fromUp) && (b.getY(bottomCorner) == center)));
	}
	//Checks the area of the ball which has hit the board , returns how many points of said ball hits the board.
	int hitSurfaceArea(const Board & p, const Ball& b)
	{
		int boardCenter = p.getY();
		int relevantCorner = b.getRelevantCorner();
		// hit whole board
		if (b.getY(relevantCorner) == boardCenter)
			return FullContact;
		// hit at one point
		else if ((b.getY(relevantCorner) == boardCenter - 2 ||
			b.getY(relevantCorner) == boardCenter + 2))
			return AlmostMissContact;
		else // hit at the sides
			return PartialContact;
	}
	//Checks for Board colision - And returns which (if exist)
	int boardColisionCheck(Board & p, Ball& b, GraveYard & Grave)
	{
		fixProblematicContact2(p, b, Grave);
		if (borderTouch(b, p))
		{
			int relevantCorner = b.getRelevantCorner();
			if ((b.getY((const int)relevantCorner) >= p.getY() - 2) &&
				(b.getY((const int)relevantCorner) <= p.getY() + 2))
			{
				if (hitSurfaceArea(p, b) >= AlmostMissContact)
				{
					if (diagonalColision(b, p))
					{
						return DiagnoalContact;
					}
					else
					{
						return Contact;
					}
				}
			}
			else //miss
			{
				p.setPredection(-1); // DONT FORGET TOO ADD HAIM
				return Miss;
			}
		}
		fixProblematicContact1(p, b);
		return -1;
	}
	//Checks for DeadBoard colision - And activates reaction
	void graveColisionManager(Board & p, Ball& b, GraveYard & Grave)
	{
		int columnHit;
		columnHit = Grave.colisionCheck(b);
		if (columnHit != -1)
		{
			if (b.getState() == 1) // becoming a bomb
			{
				BecomingBombGraveColision(b, p, Grave);
			}
			if (b.getState() == 2) // Bomb
			{
				BombGraveColisionReaction(b, p, Grave, columnHit);
				if (b.getXDirection() == p.whichPlayer())
					b.changeXDirection();
			}
		}
	}
};