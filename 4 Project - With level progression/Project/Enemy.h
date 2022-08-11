#pragma once
#include <chrono>

#include "PlacableActor.h"
#include "Player.h"
class Enemy : public PlacableActor
{
public:
	Enemy(int x, int y, int deltaX = 0, int deltaY = 0, int wait = 500);

	virtual ActorType GetType() override { return ActorType::Enemy; }
	virtual void Draw() override;
	virtual void Update() override;

	void OnCollision(PlacableActor* collidingPlayer) override;

protected:
	void InitDirection();

private:
	int m_movementInX;
	int m_movementInY;

	int m_currentMovementX;
	int m_currentMovementY;

	int m_directionX;
	int m_directionY;

	std::chrono::time_point<std::chrono::system_clock> m_startTime;
	int m_waitTime;

	void UpdateDirection(int& current, int& direction, int& movement);

};

