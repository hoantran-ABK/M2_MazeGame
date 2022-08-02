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
}


bool Spike::IsActive()
{
	return m_active > 0 && m_delay == 0;
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
