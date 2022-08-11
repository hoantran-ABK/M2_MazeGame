#pragma once
#include "GameState.h"
#include "Player.h"
#include "Level.h"

#include <windows.h>
#include <vector>
#include <string>
#include <mutex>
#include <thread>

class StateMachineExampleGame;


class GameplayState : public GameState
{
	std::mutex mu;
	int * g_input = nullptr;
	bool m_IsGameDone = false;
	std::thread* InputThread = nullptr;
	bool m_IsArrowInput = false;

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
	virtual bool Update(bool processInput = true) override;
	virtual void Draw() override;


protected:
	void GetInput();

	void ProcessInput() override;// int g_input) override;
	void CheckBeatLevel();

private:
	void HandleCollision(int newPlayerX, int newPlayerY);
	bool Load();
	void DrawHUD(const HANDLE& console);
};
