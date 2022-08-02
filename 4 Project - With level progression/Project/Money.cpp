#include <iostream>
#include "Money.h"

Money::Money(int x, int y, int worth)
	: PlacableActor(x, y)
	, m_worth(worth)
{

}

void Money::Draw()
{
	std::cout << "$";
}

void Money::OnCollision(PlacableActor* collidingPlayer)
{
	AudioManager::GetInstance()->PlayMoneySound();
	this->Remove();
	Player* collidedPlayer = dynamic_cast<Player*>(collidingPlayer);

	collidedPlayer->AddMoney(this->GetWorth());
	collidedPlayer->SetPosition(this->GetXPosition(), this->GetYPosition());
}
