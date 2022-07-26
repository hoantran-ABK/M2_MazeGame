#include "GameplayState.h"

#include <iostream>
#include <conio.h>
#include <windows.h>
#include <assert.h>

#include "Enemy.h"
#include "Key.h"
#include "Door.h"
#include "Money.h"
#include "Goal.h"
#include "AudioManager.h"
#include "Utility.h"
#include "StateMachineExampleGame.h"

#include "Shield.h"
#include "Spike.h"

using namespace std;

constexpr int kArrowInput = 224;
constexpr int kLeftArrow = 75;
constexpr int kRightArrow = 77;
constexpr int kUpArrow = 72;
constexpr int kDownArrow = 80;
constexpr int kEscapeKey = 27;

GameplayState::GameplayState(StateMachineExampleGame* pOwner)
	: m_pOwner(pOwner)
	//, m_didBeatLevel(false)
	, m_skipFrameCount(0)
	, m_currentLevel(0)
	, m_pLevel(nullptr)
{
	m_LevelNames.push_back("Level1.txt");
	//m_LevelNames.push_back("Level2.txt");
	//m_LevelNames.push_back("Level3.txt");
	m_LevelNames.push_back("LevelX.txt");
	m_LevelNames.push_back("LevelT.txt");
}

GameplayState::~GameplayState()
{
	InputThread->join();
	delete InputThread;

	delete m_pLevel;
	m_pLevel = nullptr;
}

bool GameplayState::Load()
{
	if (m_pLevel)
	{
		delete m_pLevel;
		m_pLevel = nullptr;
	}

	m_pLevel = new Level();

	return m_pLevel->Load(m_LevelNames.at(m_currentLevel), m_player.GetXPositionPointer(), m_player.GetYPositionPointer());
}

void GameplayState::Enter()
{
	Load();

	// Start Thread Here: Moved from my previous version which was back up at the Game class. 
	// The issue with having the threads up in the Game class is that the threading for input had to be abstracted
	// for every GameState which meant that when switching from say GameplayState to WinState, 
	// the Input thread that was running on GameplayState's instance would be deleted while the InputThread was 
	// waiting resulting in some Race Conditions since it would then read an input and try to 
	// access stuff from GameplayState that didn't exist anymore.

	InputThread = new std::thread(&GameplayState::GetInput, this);
	// End thread at destructor? Or where Gameplay State will end(down in CHeckBeatLevel maybe)
}

void GameplayState::GetInput()
{
	int l_input;
	int* old;
	while (true)
	{
		if (m_IsGameDone)
		{
			break;
		}
		int a_input = _getch();
		if (a_input != kArrowInput)
		{
			m_IsArrowInput = false;
		}
		else
		{
			m_IsArrowInput = true;
		}
		l_input = _getch();

		
		std::lock_guard<std::mutex> Guard(mu);
		//mu.lock();
		old = g_input;
		/*if (g_input != nullptr)
		{
			delete g_input;
		}*/
		g_input = new int(l_input);
		delete old;
		//mu.unlock();
	}
}

void GameplayState::ProcessInput()//int g_input)
{
	if (m_player.GetBeatLevel())
	{
		CheckBeatLevel();
		return;
	}

	std::lock_guard<std::mutex> Guard(mu);
	//mu.lock();
	if (g_input == nullptr)
	{
		if (!m_IsGameDone)
		{
			HandleCollision(m_player.GetXPosition(), m_player.GetYPosition());
		}
		return;
	}

	// consume whatever is in g_input and get rid of it (as long as it's not nullptr)
	int input = *g_input;
	int* old = g_input;
	//delete g_input;
	g_input = nullptr;
	delete old;
	//mu.unlock();

	int arrowInput = 0;
	int newPlayerX = m_player.GetXPosition();
	int newPlayerY = m_player.GetYPosition();

	// One of the arrow keys were pressed
	if (m_IsArrowInput)//input == kArrowInput)
	{
		arrowInput = input;
	}

	if ((m_IsArrowInput && arrowInput == kLeftArrow) || //input == kArrowInput && arrowInput == kLeftArrow) ||
		(char)input == 'A' || (char)input == 'a')
	{
		newPlayerX--;
	}
	else if ((m_IsArrowInput && arrowInput == kRightArrow) ||//input == kArrowInput && arrowInput == kRightArrow) ||
		(char)input == 'D' || (char)input == 'd')
	{
		newPlayerX++;
	}
	else if ((m_IsArrowInput && arrowInput == kUpArrow) ||//input == kArrowInput && arrowInput == kUpArrow) ||
		(char)input == 'W' || (char)input == 'w')
	{
		newPlayerY--;
	}
	else if ((m_IsArrowInput && arrowInput == kDownArrow) || //input == kArrowInput && arrowInput == kDownArrow) ||
		(char)input == 'S' || (char)input == 's')
	{
		newPlayerY++;
	}
	else if (input == kEscapeKey)
	{
		m_pOwner->LoadScene(StateMachineExampleGame::SceneName::MainMenu);
	}
	else if ((char)input == 'Z' || (char)input == 'z')
	{
		m_player.DropKey();
	}

	// If position never changed
	if (newPlayerX == m_player.GetXPosition() && newPlayerY == m_player.GetYPosition())
	{
		//return false;
	}
	else
	{
		HandleCollision(newPlayerX, newPlayerY);
	}
}

void GameplayState::CheckBeatLevel()
{
	if (m_player.GetBeatLevel())
	{
		++m_skipFrameCount;
		if (m_skipFrameCount > kFramesToSkip)
		{
			//m_didBeatLevel = false;
			m_player.SetBeatLevel(false);

			m_skipFrameCount = 0;
			++m_currentLevel;
			if (m_currentLevel == m_LevelNames.size())
			{
				m_IsGameDone = true;
				Utility::WriteHighScore(m_player.GetMoney());

				AudioManager::GetInstance()->PlayWinSound();

				m_pOwner->LoadScene(StateMachineExampleGame::SceneName::Win);
			}
			else
			{
				// On to the next level
				Load();
			}
		}
	}
}

bool GameplayState::Update(bool processInput)
{
	/*if (processInput && !m_player.GetBeatLevel())
	{
		ProcessInput();
	}*/

	CheckBeatLevel();

	return false;
}

void GameplayState::HandleCollision(int newPlayerX, int newPlayerY)
{
	// Update Actors does collision check based on X,Y pos as well
	PlacableActor* collidedActor = m_pLevel->UpdateActors(newPlayerX, newPlayerY);
	if (collidedActor != nullptr)
	{
		collidedActor->OnCollision(&m_player);
	}

	else if (m_pLevel->IsSpace(newPlayerX, newPlayerY)) // no collision
	{
		m_player.SetPosition(newPlayerX, newPlayerY);
	}
	else if (m_pLevel->IsWall(newPlayerX, newPlayerY))
	{
		// wall collision, do nothing
	}

	// IF for whatever reason, health drops to 0, signal game over
	if (m_player.GetLives() < 0)
	{
		m_IsGameDone = true;
		//TODO: Go to game over screen
		AudioManager::GetInstance()->PlayLoseSound();
		m_pOwner->LoadScene(StateMachineExampleGame::SceneName::Lose);
	}

}

void GameplayState::Draw()
{
	HANDLE console = GetStdHandle(STD_OUTPUT_HANDLE);
	system("cls");

	m_pLevel->Draw();

	// Set cursor position for player 
	COORD actorCursorPosition;
	actorCursorPosition.X = m_player.GetXPosition();
	actorCursorPosition.Y = m_player.GetYPosition();
	SetConsoleCursorPosition(console, actorCursorPosition);
	m_player.Draw();

	// Set the cursor to the end of the level
	COORD currentCursorPosition;
	currentCursorPosition.X = 0;
	currentCursorPosition.Y = m_pLevel->GetHeight();
	SetConsoleCursorPosition(console, currentCursorPosition);

	DrawHUD(console);
}

void GameplayState::DrawHUD(const HANDLE& console)
{
	cout << endl;

	// Top Border
	// applied TA : Dean Jones's fix for odd UI bug from slack in levelupu_students channel
	if (m_pLevel->GetWidth() < 53)
	{
		for (int i = 0; i < 53; ++i)
		{
			cout << Level::WAL;
		}
		cout << endl;
	}
	else
	{
		for (int i = 0; i < m_pLevel->GetWidth(); ++i)
		{
			cout << Level::WAL;
		}
		cout << endl;
	}

	// Left Side border
	cout << Level::WAL;

	cout << " wasd-move " << Level::WAL << " z-drop key " << Level::WAL;

	cout << " $:" << m_player.GetMoney() << " " << Level::WAL;
	cout << " lives:" << m_player.GetLives() << " " << Level::WAL;
	cout << " key:";
	if (m_player.HasKey())
	{
		m_player.GetKey()->Draw();
	}
	else
	{
		cout << " ";
	}

	// RightSide border
	CONSOLE_SCREEN_BUFFER_INFO csbi;
	GetConsoleScreenBufferInfo(console, &csbi);

	COORD pos;
	if (m_pLevel->GetWidth() < 53)
	{
		pos.X = 52;

	}
	else
	{
		pos.X = m_pLevel->GetWidth() - 1;

	}
	pos.Y = csbi.dwCursorPosition.Y;
	SetConsoleCursorPosition(console, pos);

	cout << Level::WAL;
	cout << endl;

	// Bottom Border
	if (m_pLevel->GetWidth() < 53)
	{
		for (int i = 0; i < 53; ++i)
		{
			cout << Level::WAL;
		}
		cout << endl;
	}
	else
	{
		for (int i = 0; i < m_pLevel->GetWidth(); ++i)
		{
			cout << Level::WAL;
		}
		cout << endl;
	}
	cout << endl;
}