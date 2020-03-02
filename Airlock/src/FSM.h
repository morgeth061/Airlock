/*
 * FSM header
 * Adapted from GBC GAME1017 SDL Template
 * Editors:
 * - Ryan Ethier
 */
#pragma once
#include <vector>
#include "Button.h"
using namespace std;

class State // Abstract base class.
{
protected:
	State() {}
public:
	virtual void Enter() = 0;
	virtual void Update() = 0;
	virtual void Render();
	virtual void Exit() = 0;
	virtual void Resume();
};

class PauseState : public State
{
public:
	PauseState();
	void Enter();
	void Update();
	void Render();
	void Exit();
};

class GameState : public State
{
public:
	GameState();
	void Enter();
	void Update();
	void Render();
	void Exit();
	void Resume();
};

class LevelSelectState : public State
{
private:
	vector<Button*> m_vButtons;
public:
	LevelSelectState();
	void Enter();
	void Update();
	void Render();
	void Exit();
};


class TitleState : public State
{
private:
	vector<Button*> m_vButtons;
public:
	TitleState();
	void Enter();
	void Update();
	void Render();
	void Exit();
};

class FSM
{
private:
	vector<State*> m_vStates;
public:
	FSM();
	~FSM();
	void Update();
	void Render();
	void ChangeState(State* pState); // Normal state change.
	void PushState(State* pState); // GameState to PauseState.
	void PopState(); // PauseState to GameState.
	void Clean();
	vector<State*>& GetStates();
};
