#pragma once
#include <iostream>
#include <chrono>
#include <windows.h>

#include "PlacableActor.h"
#include "Player.h"

// M4_Ch4 : Spike Class needs to be refactored to properly operate in a real time environment
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

	std::chrono::time_point<std::chrono::system_clock> m_startActiveTime;
	std::chrono::time_point<std::chrono::system_clock> m_startDelayTime;
	int m_waitDelayTime;
	int m_waitActiveTime;
};

