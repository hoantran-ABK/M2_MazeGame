#pragma once
#include "PlacableActor.h"

class Key;

class Player : public PlacableActor
{
public:
	Player();

	bool HasShield();
	void PickupShield();
	void ConsumeShield();

	bool HasKey();
	bool HasKey(ActorColor color);
	void PickupKey(Key* key);
	void UseKey();
	void DropKey();
	Key* GetKey() { return m_pCurrentKey; }

	void AddMoney(int money) { m_money += money; }
	int GetMoney() { return m_money; }

	int GetLives() { return m_lives; }
	void DecrementLives() { m_lives--; }

	virtual ActorType GetType() override { return ActorType::Player; }
	virtual void Draw() override;

	bool GetBeatLevel() { return m_beatLevel; }
	void SetBeatLevel(bool beat) { m_beatLevel = beat; }
private:
	Key* m_pCurrentKey;
	int m_money;
	int m_lives;
	
	bool m_shield;

	bool m_beatLevel = false;
};
