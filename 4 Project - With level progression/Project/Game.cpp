#include "Game.h"

Game::Game()
	: m_pStateMachine(nullptr)
{

}

void Game::Initialize(GameStateMachine* pStateMachine)
{
	if (pStateMachine != nullptr)
	{
		pStateMachine->Init();
		m_pStateMachine = pStateMachine;
	}
}

void Game::RunGameLoop()
{
	bool isGameOver = false;

	//std::thread InputThread(&Game::ProcessInputs, this);

	//Update(false);
	while (!isGameOver)
	{
		// update with no input
		Update(false);

		// Draw
		// M4_Ch4 : to reduce "flickering", make something that limits Draw() calls until enemies / other active actors update
			// ie Don't re-draw anything unless something actually needs to be updated
		Draw();
		// Update with input
		ProcessInputs();
		isGameOver = CheckGameDone();
	}

	Draw();
}

void Game::Deinitialize()
{
	if (m_pStateMachine != nullptr)
		m_pStateMachine->Cleanup();
}

bool Game::CheckGameDone()
{
	return m_pStateMachine->GetIsDone();
}

bool Game::Update(bool processInput)
{
	return m_pStateMachine->UpdateCurrentState(processInput);
}


void Game::ProcessInputs()
{
	m_pStateMachine->ProcessInputs();
}

void Game::Draw()
{
	m_pStateMachine->DrawCurrentState();
}
