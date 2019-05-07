#pragma once
#include <conio.h>
#include "KeyboardManager.h"

//insert board into kblist 
void KeyboardManager::registerKbListener(PlayerBoard * pKbListener)
{
	const char * chars = pKbListener->getKbChars();
	size_t numCharToRegister = strlen(chars)-1;
	for (size_t i = 0; i < numCharToRegister; ++i) {
		int index = getIndex(chars[i]);
		if (index != -1) {
			kbListeners[index].push_back(pKbListener);
		}
	}
}

//take input from keyboard and send command to the right board
void KeyboardManager::handleKeyboard(int & exit)
{
	if (_kbhit()) 
	{
		char k = _getch();
		if (k == 27)
		{
			exit = 1;
		}
		else
		{
			int index= getIndex(k);
			if (index != -1)
			{
				for (auto pKbListener : kbListeners[index])
				{
					pKbListener->handleKey(tolower(k));
				}
			}
		}
	}
}

void KeyboardManager::clearListener(PlayerBoard* listeners)
{
	const char * chars = listeners->getKbChars();
	size_t numCharToRegister = strlen(chars) - 1;

	for (size_t i = 0; i < numCharToRegister; ++i) {
		int index = getIndex(chars[i]);
		if (index != -1) {
			kbListeners[index].clear();
		}
	}
}


