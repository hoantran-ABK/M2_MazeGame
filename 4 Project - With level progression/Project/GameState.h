#pragma once

class GameState
{
public:
	virtual ~GameState() {}

	virtual void Enter() {}
	virtual bool Update(bool processInput = true) { return false; }

	virtual void ProcessInput() { return; }//int g_input) { return; }

	virtual void Draw() = 0;
	virtual void Exit() {}
};