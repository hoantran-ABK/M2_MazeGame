#pragma once
#include "PlacableActor.h"
#include "Player.h"
class Money : public PlacableActor
{
public:
	Money(int x, int y, int worth);

	int GetWorth() const { return m_worth; }

	virtual ActorType GetType() override { return ActorType::Money; }
	virtual void Draw() override;

	void OnCollision(PlacableActor* collidingPlayer) override;

private:
	int m_worth;
};

