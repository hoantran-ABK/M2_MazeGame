#pragma once
#include "GameState.h"

class StateMachineExampleGame;

class WinState : public GameState
{
	StateMachineExampleGame* m_pOwner;

public:
	WinState(StateMachineExampleGame* pOwner);
	~WinState() = default;

	virtual bool Update(bool processInput = true) override;

	void ProcessInput() override;//int g_input) override;

	virtual void Draw() override;
};
