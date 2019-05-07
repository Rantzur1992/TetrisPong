#include "DeadBoard.h"

//done
void DeadBoard::draw()
{
	Point temp = down;
	temp.draw();
	while (temp != up) {
		temp.move(0, -1);
		temp.draw();
	}
}
void DeadBoard::erase()
{
	Point temp = up;
	while (temp != down)
	{
		temp.erase();
		temp.move(0, 1);
	}
	temp.erase();
}
