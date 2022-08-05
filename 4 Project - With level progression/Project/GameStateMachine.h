#pragma once

class GameState;

class GameStateMachine
{
public:
	virtual ~GameStateMachine() = default;

	virtual bool Init() = 0;
	virtual bool UpdateCurrentState(bool & IsReadyForInput, bool & IsDoneWithInput, bool processInput = true) = 0;
	virtual void DrawCurrentState(bool & IsReadyForInput, bool & IsDoneWithInput, bool IsGameOver) = 0;
	virtual void ChangeState(GameState* pNewState) = 0;
	virtual bool Cleanup() = 0;

	virtual void SetIsDone(bool done) { m_isDone = done; }
	virtual bool GetIsDone() { return m_isDone; }

	virtual void ProcessStateInputs(bool & IsReadyForInput, bool & IsDoneWithInput, bool IsGameOver) { return; }
private:
	bool m_isDone = false;
};

