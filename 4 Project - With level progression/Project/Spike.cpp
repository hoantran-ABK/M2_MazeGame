#include "Spike.h"

using namespace std;



Spike::Spike(int x, int y, int maxActive, int maxDelay)
	: PlacableActor(x,y),
	m_maxActive(maxActive),
	m_maxDelay(maxDelay),
	m_active(0),
	m_delay(0)
{
}

ActorType Spike::GetType()
{
	return ActorType::Spike;
}

void Spike::Draw()
{
	if (!IsActive())
	{
		cout << ".";
	}
	else
	{
		cout << "#";
	}
}

void Spike::Trigger()
{
	m_active = m_maxActive;
	m_delay = m_maxDelay;

	m_startDelayTime = std::chrono::system_clock::now();
}

void Spike::Update()
{
	if (m_delay > 0)
	{
		m_delay--;
		return;
	}

	if (m_active > 0 && m_delay == 0)
	{
		m_active--;
		return;
	}
}

bool Spike::IsTriggered()
{
	return m_delay > 0;
	//std::chrono::time_point<std::chrono::system_clock> currentDelayTime = std::chrono::system_clock::now();
	//return std::chrono::duration_cast<std::chrono::milliseconds>(currentDelayTime - m_startDelayTime).count() < m_waitDelayTime;
}


bool Spike::IsActive()
{
	return m_active > 0 && m_delay == 0;
	//std::chrono::time_point<std::chrono::system_clock> currentActiveTime = std::chrono::system_clock::now();
	//return std::chrono::duration_cast<std::chrono::milliseconds>(currentActiveTime - m_startActiveTime).count() < m_waitActiveTime;
}

void Spike::OnCollision(PlacableActor* collidingPlayer)
{
	Player* collidedPlayer = dynamic_cast<Player*>(collidingPlayer);

	collidedPlayer->SetPosition(this->GetXPosition(), this->GetYPosition());

	if (this->IsActive())
	{
		if (collidedPlayer->HasShield())
		{
			collidedPlayer->ConsumeShield();
		}
		else
		{
			AudioManager::GetInstance()->PlayLoseLivesSound();
			collidedPlayer->DecrementLives();
			
		}
		this->Update();
	}
	else if (this->IsTriggered() && !this->IsActive())
	{
		// do nothing, it should become active later
	}
	else if (!this->IsTriggered() && !this->IsActive())
	{
		//not active nor triggered, trigger the spike trap
		this->Trigger();
	}
}
