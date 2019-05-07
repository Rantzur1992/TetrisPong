#pragma once
#include <stdio.h>
#include <stdlib.h>
#include <conio.h>
#include "GameManager.h"
#include "ColisionManager.h"


const int ESC = 27;
int gameStarted = 0; // Keeping global as it is an important flag

void GameManager::presentMenu()
{
	char diff;
	int selection;

	while (true)
	{
		system("cls");
		cout << "----------------------------------" << endl;
		cout << "Select one of the following: " << endl;
		cout << "(1) Start a new game - Human vs Human" << endl
			<< "(2) Start a new game - Human vs Computer" << endl
			<< "(3) Start a new game - Computer vs Computer" << endl;
		if (gameStarted == 1 || gameStarted == 2 || gameStarted == 3)
			cout << "(4) Continue a paused game" << endl;
		cout << "(8) Present instructions and keys" << endl;
		cout << "(9) EXIT" << endl;
		cout << "----------------------------------" << endl;
		cin >> selection;
		switch (selection)
		{
		case 1: // HUMAN VS HUMAN
			system("cls");
			reset();
			//register keyboard listeners
			kbManager.registerKbListener(&p1);
			kbManager.registerKbListener(&p2);
			
			start(p1,p2);
			system("cls");
			break;
		case 2: // HUMAN VS PC
			system("cls");
			reset();

			//register keyboard listener (Only The Human)
			kbManager.registerKbListener(&p1);

			cout << "Select difficulty" << endl
				<< "(a) BEST " << endl
				<< "(b) GOOD " << endl
				<< "(c) NOVICE " << endl;
			cin >> diff;
			system("cls");
			m_pc2.setDiff(diff);
			start(p1, m_pc2);
			break;

		case 3: // PC VS PC
			system("cls");
			reset();
			cout << "Select difficulty" << endl
				<< "(a) BEST " << endl
				<< "(b) GOOD " << endl
				<< "(c) NOVICE " << endl;
			cin >> diff;
			m_pc1.setDiff(diff);
			m_pc2.setDiff(diff);
			system("cls");
			start(m_pc1, m_pc2);
			break;

		case 4:
			//Resume the current on going game
			system("cls");
			if(gameStarted == HumanVsHuman)
				start(p1,p2);
			if (gameStarted == HumanVsPc)
				start(p1, m_pc2);
			if (gameStarted == PcVsPc)
				start(m_pc1, m_pc2);
			system("cls");
			break;
		case 8:
			system("cls");
			presentInstructions();
			break;
		case 9:
			exit(on);

		default:
			break;
		}
	}
}

void GameManager::start(Board & p1, Board & p2) //Generic Start 
{
	setStandard();
	ColisionManager colMan;
	int exit = off;
	p1.draw();
	p1.drawBorder();
	p2.draw();
	p2.drawBorder();
	while (true && exit == off)
	{
		kbManager.handleKeyboard(exit);
		ball.move();
		colMan.colisionNavigation(p1, p2, ball, grave1, grave2);
		if (PlayerBoard * p1ref = dynamic_cast<PlayerBoard *>(&p1)){
			humanRoundFunction((*p1ref),ball);
		}
		else { //p1 is pc Object
			PcBoard * p1pcref = dynamic_cast<PcBoard *>(&p1);
			computerRoundFunction((*p1pcref), ball);
		}
		if (PlayerBoard * p2ref = dynamic_cast<PlayerBoard *>(&p2)) {
			humanRoundFunction((*p2ref), ball);
		}
		else { //p2 is pc Object
			PcBoard * p2pcref = dynamic_cast<PcBoard *>(&p2);
			computerRoundFunction((*p2pcref), ball);
		}

		/* LOSING CONDITIONS */
		if (p1.getX() >= Victory::player1)
		{
			defeat(1);
			break;
		}
		if (p2.getX() <= Victory::player2)
		{
			defeat(2);
			break;
		}
		Sleep(Ballspeed);
	}

}
void GameManager::humanRoundFunction(PlayerBoard & p,Ball & ball)
{
	if (p.getBombPressed()) // If one of the players pressed the bomb button and it was NOT yet pressed
	{
		if (ball.getState() == 0) // The ball must be in "regular"
			ball.setState(1); // The ball shall start becoming a bomb

		if (ball.getX(Ball::Center) == 40) //Count the times the cneter of the ball passes the x = 40 column
			ball.x40++;

		if (ball.iterations == 8 && ball.getState() == 1) //Check if ball stayed in "becoming a bomb" state after 8 game iterations
		{
			ball.setState(2); // BECOME A BOMB!
			ball.iterations = 0;
		}
		ball.iterations++;
	}
}
void GameManager::computerRoundFunction(PcBoard & p, Ball & ball)
{
	p.calculate(ball);
	if (ball.getXDirection() == p.whichPlayer())
		p.move();
}
void GameManager::reset()
{
	p1.reset(Player1Default::X1, Player1Default::Yup1, Player1Default::Ydown1);
	p2.reset(Player2Default::X2, Player2Default::Yup2, Player2Default::Ydown2);
	m_pc1.reset(Player1Default::X1, Player1Default::Yup1, Player1Default::Ydown1);
	m_pc2.reset(Player2Default::X2, Player2Default::Yup2, Player2Default::Ydown2);
	kbManager.clearListener(&p1);
	kbManager.clearListener(&p2);

	ball.reset();
	grave1.clear();
	grave2.clear();
	system("cls");
}
void GameManager::DrawUI()
{
	setTextColor((Color)250);
	Point wallPainter(0,3, Wallsign);
	for (int i = 1; i <= 80; i++)
	{
		wallPainter.draw();
		wallPainter.move(1,0);
		Sleep(WallPainterspeed);
	}
	for (int i = 1; i <= 22; i++)
	{
		wallPainter.draw();
		wallPainter.move(0, 1);
		Sleep(WallPainterspeed);
	}
	for (int i = 1; i <= 80; i++)
	{
		wallPainter.draw();
		wallPainter.move(-1, 0);
		Sleep(WallPainterspeed);
	}
	for (int i = 1; i <= 22; i++)
	{
		wallPainter.draw();
		wallPainter.move(0, -1);
		Sleep(WallPainterspeed);
	}
	setTextColor(Color::WHITE);
}
void GameManager::defeat(int player)
{
	system("cls");
	gotoxy(messageX, messageY);
	cout << "Player " << player << " LOST! " << endl;
	gameStarted = off;
	Sleep(LoadingTime);
	reset();
}
void GameManager::setStandard()
{
	DrawUI();
	ball.draw();
	grave1.draw(0);
	grave2.draw(0);
}



