#pragma once
#include "GameState.h"

class StateMachineExampleGame;

class WinState : public GameState
{
	StateMachineExampleGame* m_pOwner;

public:
	WinState(StateMachineExampleGame* pOwner);
	~WinState() = default;

	virtual bool Update(bool IsGameOver, bool processInput = true) override;

	void ProcessInput(bool IsGameOver) override;

	virtual void Draw() override;
};
