#pragma once
#include <thread>
#include <iostream>
#include <chrono>
#include <atomic>

#include "GameStateMachine.h"
#include "Player.h"
#include "Level.h"

class Game
{
	GameStateMachine* m_pStateMachine;

	std::atomic<bool> m_isGameOver = false;
	bool m_IsReadyForInput = false;
	bool m_IsDoneWithInput = false;
public:
	Game();
	void Initialize(GameStateMachine* pStateMachine);
	void RunGameLoop();

	void UpdateLoop();
	void InputLoop();
	void DrawLoop();

	void Deinitialize();

	bool CheckGameDone();

private:
	bool Update(bool processInput = true);

	void ProcessStateMachineInputs();
	void Draw();
};