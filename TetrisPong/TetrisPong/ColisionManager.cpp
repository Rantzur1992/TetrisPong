#include "ColisionManager.h"

void ColisionManager::colisionNavigation(Board & p1, Board & p2, Ball& b, GraveYard & Gravep1, GraveYard & Gravep2)
{
	int whichContact, relevantCorner = b.getRelevantCorner();
	if (b.getXDirection() == left)
	{
		whichContact = boardColisionCheck(p1, b, Gravep1);
		if (b.getState() == 0 && whichContact != -1)
		{
			regularBallColisionReaction(b, p1, Gravep1, whichContact);
		}
		else if (b.getState() == 1)
		{
			if (whichContact > 0)
			{
				BecomingBombBoardColision(b, p1, Gravep1, whichContact);
				p1.setBombPressed(0); // Reset pressed
				p2.setBombPressed(0);
			}

			if (whichContact == -1 && b.getX((const int)relevantCorner) <= p1.getX())
			{
				graveColisionManager(p1, b, Gravep1);
				p1.setBombPressed(0); // Reset pressed
				p2.setBombPressed(0);
			}
		}
		else // ball is a bomb
		{
			if (whichContact > 0)
			{
				BombBoardColisionReaction(b, p1, Gravep1);
				p1.setBombPressed(0); // Reset pressed
				p2.setBombPressed(0);
			}

			if (whichContact == -1 && b.getX((const int)relevantCorner) <= p1.getX())
			{
				graveColisionManager(p1, b, Gravep1);
				p1.setBombPressed(0); // Reset pressed
				p2.setBombPressed(0);
			}
		}
	}
	else
	{
		whichContact = boardColisionCheck(p2, b, Gravep2);
		if (b.getState() == 0 && whichContact != -1)
		{
			regularBallColisionReaction(b, p2, Gravep2, whichContact);
		}
		else if (b.getState() == 1)
		{
			if (whichContact > 0)
			{
				BecomingBombBoardColision(b, p2, Gravep2, whichContact);
				p1.setBombPressed(0); // Reset pressed
				p2.setBombPressed(0);
			}

			if (whichContact == -1 && b.getX((const int)relevantCorner) >= p2.getX())
			{
				graveColisionManager(p2, b, Gravep2);
				p1.setBombPressed(0); // Reset pressed
				p2.setBombPressed(0);
			}
		}
		else // ball is a bomb
		{
			if (whichContact > 0)
			{
				BombBoardColisionReaction(b, p2, Gravep2);
				p1.setBombPressed(0); // Reset pressed
				p2.setBombPressed(0);
			}

			if (whichContact == -1 && b.getX((const int)relevantCorner) >= p2.getX())
			{
				graveColisionManager(p2, b, Gravep2);
				p1.setBombPressed(0); // Reset pressed
				p2.setBombPressed(0);
			}
		}
	}
}
void ColisionManager::regularBallColisionReaction(Ball & b, Board & p, GraveYard & grave, int colisionType)
{
	if (colisionType == Miss)
	{
		b.move();
		Sleep(BallMotionSpeed);
		b.reset();
		p.erase();
		if (grave.insert(p) == Kaboom) { p.pullBack(5); }
		else { p.push(); }
		p.draw();
	}
	else if (colisionType == DiagnoalContact)
	{
		if (b.getXDirection() == left) { b.animateDiagonalLeft(p); }
		else { b.animateDiagonalRight(p); }
		b.changeYDirection();
		b.changeXDirection();
		b.move();
		p.draw();
		if (b.getXDirection() == right) { b.afterHitDiaLeft(); }
		else { b.afterHitDiaRight(); }
	}
	else // colisionType = Contact
	{
		if (b.getXDirection() == left) { b.animateLeftHit(p); }
		else { b.animateRightHit(p); }
		b.changeXDirection();
		b.move();
		p.draw();
		if (b.getXDirection() == right) { b.animateLeftAfterHit(p); }
		else { b.animateRightAfterHit(p); }

	}
}
void ColisionManager::BombGraveColisionReaction(Ball & b, Board & p, GraveYard & grave, int columnHit)
{
	b.BombHitGraveAnimation();
	grave.colisionKaboom(columnHit);
	b.BombHitGraveAnimation(1);
	p.erase();
	b.reset();
	p.drawBorder();
	grave.draw(1);
	grave.draw();
	p.pullBack(1);
	p.draw();
}
void ColisionManager::BombBoardColisionReaction(Ball & b, Board & p, GraveYard & grave)
{
	b.BombHitBoardAnimation();
	b.BombHitBoardAnimation(1);
	if (grave.insert(p) == Kaboom) { p.pullBack(5); }
	else { p.push(); p.push(); p.push(); }
	b.reset();
	p.erase();
	p.draw();
	p.drawBorder();
	grave.draw(1);
	grave.draw();
}
void ColisionManager::BecomingBombBoardColision(Ball & b, Board & p, GraveYard & grave, int colisionType)
{
	regularBallColisionReaction(b, p, grave, colisionType);
	b.setState(0);
}
void ColisionManager::BecomingBombGraveColision(Ball & b, Board & p, GraveYard & grave)
{
	p.erase();
	if (grave.insert(p) == Kaboom) { p.pullBack(5); }
	else { p.push(); }
	b.reset();
	p.draw();
	grave.draw(1);
	grave.draw();
}
