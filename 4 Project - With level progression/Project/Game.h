#pragma once
#include <thread>
#include <mutex>
#include <conio.h>

#include "GameStateMachine.h"
#include "Player.h"
#include "Level.h"

//static std::mutex g_mutex;
//static int g_input;

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

	void GetInput();
	void ProcessInputs();
	void Draw();
};