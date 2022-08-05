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
	//bool m_isGameOver = false;

	//Update(false);
	//while (!m_isGameOver)
	//{
	//	//std::this_thread::sleep_for(std::chrono::milliseconds(1));
	//	// update with no input
	//	Update(false);

	//	// Draw
	//	Draw();
	//	// Update with input
	//	ProcessStateMachineInputs();
	//	m_isGameOver = CheckGameDone();
	//}
	//m_isGameOver;
	//Draw();
	m_IsDoneWithInput = true;
	std::thread UpdateThread(&Game::UpdateLoop, this);
	//std::thread DrawThread(&Game::DrawLoop, this);
	std::thread InputThread(&Game::InputLoop, this);
	
	UpdateThread.join();
	//DrawThread.join();
	InputThread.join();

}

void Game::UpdateLoop()
{
	//bool t1 = m_isGameOver;
	//bool t2 = m_isGameOver.load();
	while (!m_isGameOver)
	{
		if (m_isGameOver) break;

		std::this_thread::sleep_for(std::chrono::milliseconds(50));
		// update with no input
		Update(false);

		// Draw
		Draw();
		// Update with input
		//ProcessStateMachineInputs();
		m_isGameOver = CheckGameDone();
		m_IsReadyForInput = true;
	}
	//m_isGameOver;
	//Draw();
}

void Game::InputLoop()
{
	while (!m_isGameOver)
	{
		if (m_isGameOver) break;

		//Update(false);
		ProcessStateMachineInputs();
		m_isGameOver = CheckGameDone();
	}
	m_isGameOver;
}

void Game::DrawLoop()
{
	while (!m_isGameOver)
	{
		if (m_isGameOver) break;
		Draw();
		m_isGameOver = CheckGameDone();
	}
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
	return m_pStateMachine->UpdateCurrentState(m_IsReadyForInput, m_IsDoneWithInput, processInput);
}

void Game::ProcessStateMachineInputs()
{
	m_pStateMachine->ProcessStateInputs(m_IsReadyForInput, m_IsDoneWithInput, m_isGameOver);
}

void Game::Draw()
{
	m_pStateMachine->DrawCurrentState(m_IsReadyForInput, m_IsDoneWithInput, m_isGameOver);
}
