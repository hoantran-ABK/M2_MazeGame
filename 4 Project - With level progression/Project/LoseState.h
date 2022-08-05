#pragma once
#include "GameState.h"

class StateMachineExampleGame;

class LoseState : public GameState
{
	StateMachineExampleGame* m_pOwner;

public:
	LoseState(StateMachineExampleGame* pOwner);
	~LoseState() = default;

	virtual bool Update(bool IsGameOver, bool processInput = true) override;

	void ProcessInput(bool IsGameOver) override;

	virtual void Draw() override;
};


