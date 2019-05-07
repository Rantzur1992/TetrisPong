#pragma once
#include "GameManager.h"


void ShowConsoleCursor(bool showFlag);
void ShowConsoleCursor(bool showFlag)
{
	HANDLE out = GetStdHandle(STD_OUTPUT_HANDLE);
	CONSOLE_CURSOR_INFO  cursorInfo;
	GetConsoleCursorInfo(out, &cursorInfo);
	cursorInfo.bVisible = showFlag; // set the cursor visibility
	SetConsoleCursorInfo(out, &cursorInfo);
}

int main()
{
	ShowConsoleCursor(false);
	KeyboardManager kbManager;
	Ball ball;
	PlayerBoard pBoard1({ 4,10,'#' }, { 4, 12, '#' }, 'q', 'a', 's');
	PlayerBoard pBoard2({ 76,11,'#' }, { 76,13,'#' }, 'p','l','k');
	
	PcBoard pcBoard1({ 4,10,'#' }, { 4, 12, '#' });
	PcBoard pcBoard2({ 76,11,'#' }, { 76,13,'#' });

	GameManager StanLee(pBoard1,pBoard2, pcBoard1 , pcBoard2, ball,kbManager);
	StanLee.presentMenu();
}


