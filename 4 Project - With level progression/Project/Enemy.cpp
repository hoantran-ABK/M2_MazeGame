#include "Enemy.h"
#include <iostream>

Enemy::Enemy(int x, int y, int deltaX, int deltaY, int wait)
	: PlacableActor(x, y)
	, m_currentMovementX(0)
	, m_currentMovementY(0)
	, m_directionX(0)
	, m_directionY(0)
	, m_movementInX(deltaX)
	, m_movementInY(deltaY)
{
	InitDirection();
	m_waitTime = wait;
	m_startTime = std::chrono::system_clock::now();
}

void Enemy::InitDirection()
{
	if (m_movementInX != 0)
	{
		m_directionX = 1;
	}
	if (m_movementInY != 0)
	{
		m_directionY = 1;
	}
}

void Enemy::Draw()
{
	std::cout << (char)153;
}

void Enemy::Update()
{
	std::chrono::time_point<std::chrono::system_clock> currentTime = std::chrono::system_clock::now();

	if (std::chrono::duration_cast<std::chrono::milliseconds>(currentTime - m_startTime).count() < m_waitTime)
	{
		return;
	}

	if (m_movementInX != 0)
	{
		UpdateDirection(m_currentMovementX, m_directionX, m_movementInX);
	}
	if (m_movementInY != 0)
	{
		UpdateDirection(m_currentMovementY, m_directionY, m_movementInY);
	}

	this->SetPosition(m_pPosition->x + m_directionX, m_pPosition->y + m_directionY);
	m_startTime = std::chrono::system_clock::now();
}

void Enemy::OnCollision(PlacableActor* collidingPlayer)
{
	this->Remove();
	
	Player* collidedPlayer = dynamic_cast<Player*>(collidingPlayer);

	collidedPlayer->SetPosition(this->GetXPosition(), this->GetYPosition());

	// TODO: make something to handle damage taken outside of Eneemy, maybe in Player OR GameplayState where this function is being used
	// add stuff for IF PLAYER IS SHIELDED, kill enemy, no lives taken
	if (collidedPlayer->HasShield())
	{
		AudioManager::GetInstance()->PlayMoneySound();
		collidedPlayer->AddMoney(10);
		collidedPlayer->ConsumeShield();
	}
	else
	{
		AudioManager::GetInstance()->PlayLoseLivesSound();
		collidedPlayer->DecrementLives();
		
		//Game Over moved to outside into HandleCollision in GameplayState
	}
}

void Enemy::UpdateDirection(int& current, int& direction, int& movement)
{
	

	current += direction;
	if (std::abs(current) > movement)
	{
		current = movement * direction;
		direction *= -1;
	}
}

