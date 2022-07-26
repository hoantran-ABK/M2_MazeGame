#include <iostream>
#include <windows.h>

#include "Shield.h"

using namespace std;

Shield::Shield(int x, int y, ActorColor color)
	: PlacableActor(x, y, color)
{
}

void Shield::Draw()
{
	HANDLE console = GetStdHandle(STD_OUTPUT_HANDLE);

	SetConsoleTextAttribute(console, (int)m_color);

	cout << "S";

	SetConsoleTextAttribute(console, (int)ActorColor::Regular);
}
