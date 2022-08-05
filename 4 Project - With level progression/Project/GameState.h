#pragma once

class GameState
{
public:
	virtual ~GameState() {}

	virtual void Enter() {}
	virtual bool Update(bool IsGameOver, bool processInput = true) { return false; }

	virtual void ProcessInput(bool IsGameOver) { return; }

	virtual void Draw() = 0;
	virtual void Exit() {}
};