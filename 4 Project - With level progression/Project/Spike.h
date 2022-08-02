#pragma once
#include <iostream>
#include <windows.h>

#include "PlacableActor.h"
#include "Player.h"

class Spike : public PlacableActor
{
public :
	Spike(int x, int y, int maxActive, int maxDelay);

	ActorType GetType();
	void Draw();

	void Trigger();
	void Update();
	bool IsTriggered();
	bool IsActive();

	void OnCollision(PlacableActor* collidingPlayer) override;

private:
	int m_active;
	int m_delay;

	int m_maxActive;
	int m_maxDelay;
};

