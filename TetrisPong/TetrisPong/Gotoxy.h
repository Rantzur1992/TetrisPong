#pragma once
#define _GOTOXY_H_
#include <iostream>
#include <windows.h>
#include <process.h>
#include <stdlib.h>
#include <stdio.h>
using namespace std;

// function definition -- requires windows.h // was Made By Amir
inline void gotoxy(int x, int y)
{
	HANDLE hConsoleOutput;
	COORD dwCursorPosition;
	cout.flush();
	dwCursorPosition.X = x;
	dwCursorPosition.Y = y;
	hConsoleOutput = GetStdHandle(STD_OUTPUT_HANDLE);
	SetConsoleCursorPosition(hConsoleOutput, dwCursorPosition);
}
// function definition -- requires process.h // was Made By Amir
inline void clrscr()
{
	system("cls");
}

