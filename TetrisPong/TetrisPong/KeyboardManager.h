#pragma once
#include <list>
#include "PlayerBoard.h"

// was Made By Amir
class KeyboardManager
{
	enum{NUM_OF_CHARS = 26};
	std::list<PlayerBoard*> kbListeners[NUM_OF_CHARS];
	//Getting the index in the list of the right chars being pressed
	int getIndex(char c) {
		int index = c - 'a';
		if (index < 0 || index >= NUM_OF_CHARS) {
			index = c - 'A';
		if (index < 0 || index >= NUM_OF_CHARS) {
				return -1;
		}
	}
		return index;
	}

public:
	void registerKbListener(PlayerBoard* pKbListener);
	void handleKeyboard(int & exit);
	void clearListener(PlayerBoard* listeners);
}; 