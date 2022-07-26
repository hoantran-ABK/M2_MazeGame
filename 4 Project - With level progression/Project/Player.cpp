#include <iostream>

#include "Player.h"
#include "Key.h"
#include "AudioManager.h"

using namespace std;

constexpr int kStartingNumberOfLives = 3;

Player::Player()
	: PlacableActor(0, 0, ActorColor::Regular)
	, m_pCurrentKey(nullptr)
	, m_money(0)
	, m_lives(kStartingNumberOfLives)
	, m_shield(false)
{

}

bool Player::HasShield()
{
	return m_shield;
}

void Player::PickupShield()
{
	this->m_shield = true;
}

void Player::ConsumeShield()
{
	this->m_shield = false;
}

bool Player::HasKey()
{
	return m_pCurrentKey != nullptr;
}

bool Player::HasKey(ActorColor color)
{
	return HasKey() && m_pCurrentKey->GetColor() == color;
}

void Player::PickupKey(Key* key)
{
	m_pCurrentKey = key;
}

void Player::UseKey()
{
	if (m_pCurrentKey)
	{
		m_pCurrentKey->Remove();
		m_pCurrentKey = nullptr;
	}
}

void Player::DropKey()
{
	if (m_pCurrentKey)
	{
		AudioManager::GetInstance()->PlayKeyDropSound();
		m_pCurrentKey->Place(m_pPosition->x, m_pPosition->y);
		m_pCurrentKey = nullptr;
	}
}

void Player::Draw()
{

	HANDLE console = GetStdHandle(STD_OUTPUT_HANDLE);

	if (this->HasShield())
	{
		this->m_color = ActorColor::Cyan;
		SetConsoleTextAttribute(console, (int)this->m_color);
		cout << "@";

		SetConsoleTextAttribute(console, (int)ActorColor::Regular);
	}
	else
	{
		this->m_color = ActorColor::Regular;
		SetConsoleTextAttribute(console, (int)this->m_color);
		cout << "@";

		SetConsoleTextAttribute(console, (int)ActorColor::Regular);
	}
	
}
