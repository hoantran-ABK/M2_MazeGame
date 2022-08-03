#pragma once
#include <thread>

#include "GameStateMachine.h"
#include "Player.h"
#include "Level.h"

class Game
{
	GameStateMachine* m_pStateMachine;
public:
	Game();
	void Initialize(GameStateMachine* pStateMachine);
	void RunGameLoop();
	void Deinitialize();

	bool CheckGameDone();

private:
	bool Update(bool processInput = true);

	void ProcessInputs();
	void Draw();
};