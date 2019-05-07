#pragma once
#include "Gotoxy.h"

class Expression
{
	enum { CENTER_SCREENX = 39, TOP = 0 ,BOTTOM = 28};
public:
	static void printKaboom(int clear)
	{
		if (clear == 0)
		{
			gotoxy(CENTER_SCREENX, TOP);
			cout << " ";
			gotoxy(CENTER_SCREENX, TOP);
			cout << " ";
		}
		else
		{
			gotoxy(CENTER_SCREENX, TOP);
			cout << "Kaaaaaaboom!!";
			gotoxy(CENTER_SCREENX, TOP);
			cout << "(???)";
		}
	}
};