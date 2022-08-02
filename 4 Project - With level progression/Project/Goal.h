#pragma once
#include "PlacableActor.h"
#include "Player.h"
class Goal : public PlacableActor
{
public:
	Goal(int x, int y);

	virtual ActorType GetType() override { return ActorType::Goal; }
	virtual void Draw() override;

	void OnCollision(PlacableActor * collidingPlayer) override;
};

