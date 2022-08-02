#include <iostream>
#include <windows.h>
#include "Door.h"

Door::Door(int x, int y, ActorColor color, ActorColor closedColor)
	: PlacableActor(x, y, color)
	, m_isOpen(false)
	, m_closedColor(closedColor)
{

}

void Door::Draw()
{
	HANDLE console = GetStdHandle(STD_OUTPUT_HANDLE);
	if (m_isOpen)
	{
		SetConsoleTextAttribute(console, (int)m_color);
	}
	else
	{
		SetConsoleTextAttribute(console, (int)m_closedColor);
	}
	std::cout << "|";
	SetConsoleTextAttribute(console, (int)ActorColor::Regular);
}

void Door::OnCollision(PlacableActor* collidingPlayer)
{
	Player* collidedPlayer = dynamic_cast<Player*>(collidingPlayer);

	if (!this->IsOpen())
	{
		if (collidedPlayer->HasKey(this->GetColor()))
		{
			this->Open();
			this->Remove();
			collidedPlayer->UseKey();
			collidedPlayer->SetPosition(this->GetXPosition(), this->GetYPosition());
			AudioManager::GetInstance()->PlayDoorOpenSound();
		}
		else
		{
			AudioManager::GetInstance()->PlayDoorClosedSound();
		}
	}
	else
	{
		collidedPlayer->SetPosition(this->GetXPosition(), this->GetYPosition());
	}
}
