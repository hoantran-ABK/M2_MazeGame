#pragma once

class GameState;

class GameStateMachine
{
public:
	virtual ~GameStateMachine() = default;

	virtual bool Init() = 0;
	virtual bool UpdateCurrentState(bool processInput = true) = 0;
	virtual void DrawCurrentState() = 0;
	virtual void ChangeState(GameState* pNewState) = 0;
	virtual bool Cleanup() = 0;

	virtual void SetIsDone(bool done) { m_isDone = done; }
	virtual bool GetIsDone() { return m_isDone; }

private:
	bool m_isDone = false;
};

