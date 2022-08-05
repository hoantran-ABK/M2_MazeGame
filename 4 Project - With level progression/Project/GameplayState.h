#pragma once
#include "GameState.h"
#include "Player.h"
#include "Level.h"

#include <windows.h>
#include <vector>
#include <string>

class StateMachineExampleGame;

class GameplayState : public GameState
{
	StateMachineExampleGame* m_pOwner;
	
	Player m_player;
	Level* m_pLevel;

	int m_skipFrameCount;
	static constexpr int kFramesToSkip = 1;

	int m_currentLevel;

	std::vector<std::string> m_LevelNames;

public:
	GameplayState(StateMachineExampleGame* pOwner);
	~GameplayState();

	virtual void Enter() override;
	virtual bool Update(bool IsGameOver, bool processInput = true) override;
	virtual void Draw() override;


protected:
	void ProcessInput(bool IsGameOver) override;
	void CheckBeatLevel();

private:
	void HandleCollision(int newPlayerX, int newPlayerY);
	bool Load();
	void DrawHUD(const HANDLE& console);
};
