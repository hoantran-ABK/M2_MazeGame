#pragma once
#include "GameState.h"

#include <set>

class StateMachineExampleGame;

class HighScoreState : public GameState
{
	StateMachineExampleGame* m_pOwner;
	std::set<int> m_HighScores;

public:
	HighScoreState(StateMachineExampleGame* pOwner);
	~HighScoreState() = default;

	virtual bool Update(bool IsGameOver, bool processInput = true) override;

	void ProcessInput(bool IsGameOver) override;

	virtual void Draw() override;
};

