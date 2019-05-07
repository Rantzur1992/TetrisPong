#pragma once
#include "PlayerBoard.h"
#include "PcBoard.h"
#include "Ball.h"
#include "KeyboardManager.h"
#include "GraveYard.h"
#include "Color.h"


class GameManager
{
	enum {HumanVsHuman = 1 , HumanVsPc = 2 , PcVsPc = 3};
	enum {LoadingTime = 5000,messageX=40,messageY=12,off=0,on=1,Wallsign = '\xB2'};
	enum Victory{player1=20,player2=60};
	enum Player1Default{ X1 = 4, Yup1 = 10, Ydown1 = 12 };
	enum Player2Default{ X2 = 76, Yup2 = 11, Ydown2 = 13 };
	enum MotionSpeed {WallPainterspeed=10,Ballspeed=50};
	PlayerBoard p1, p2;
	PcBoard m_pc1, m_pc2;
	Ball ball;
	KeyboardManager kbManager;
	GraveYard grave1, grave2;

public:
	GameManager(PlayerBoard player1 , PlayerBoard player2 ,PcBoard pc1 , PcBoard pc2 ,  Ball gameBall, KeyboardManager manager) :
		p1(player1) , p2(player2) , m_pc1(pc1) , m_pc2(pc2), ball(gameBall) , kbManager(manager){}
	void presentMenu(); //Presents the Main Menu for to the player
	void start(Board & p1, Board & p2); // Start the game(Human vs Human)
	void reset(); // reset the game to starting positions
	void DrawUI(); // Draw the game UI
	void defeat(int player); // Handles losing menu
	void presentInstructions()
	{
		cout << "INSTRUCTIONS!" << endl;
		cout << "The keys for player 1 (left player) are :" << endl;
		cout << "To move the board up press Q or q" << endl;
		cout << "To move the board down press A or a" << endl;
		cout << "The keys for player 2 (right player) are :" << endl;
		cout << "To move the board up press P or p" << endl;
		cout << "To move the board down press L or l" << endl;
		cout << "When a player misses the ball , a copy board of him shall 'drop' and stay there , this is the tetris part of the game" << endl;
		cout << "The dead boards will start to accumelate and gain height , pushing the player to the oppisite side the the arena" << endl;
		cout << "Incase dropped boards complete a full line, the entire line would explode and the board would go back five blocks" << endl;
		cout << "The game will end once a player's board gets too far from his starting position\n" << endl;
	}
	void setStandard();
	void computerRoundFunction(PcBoard & p, Ball & ball);
	void humanRoundFunction(PlayerBoard & p, Ball & ball);
	void setTextColor(Color colorToSet) {
		SetConsoleTextAttribute(GetStdHandle(STD_OUTPUT_HANDLE), (int)colorToSet);
	}
};

