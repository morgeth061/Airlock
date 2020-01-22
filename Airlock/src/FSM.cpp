/*
 * FSM class
 * Taken from GBC GAME1017 SDL Template
 * Editors:
 * - Ryan Ethier
 */
#include "FSM.h"
#include "Engine.h"
#include "TextureManager.h"
#include <iostream>
using namespace std;

// Begin State.
void State::Render()
{
	SDL_RenderPresent(Engine::Instance().GetRenderer());
}

void State::Resume() {}
// End State.

// Begin PauseState.
PauseState::PauseState() {}

void PauseState::Enter()
{
	cout << "Entering Pause..." << endl;
}

void PauseState::Update()
{
	if (Engine::Instance().KeyDown(SDL_SCANCODE_R))
		Engine::Instance().GetFSM().PopState();
}

void PauseState::Render()
{
	cout << "Rendering Pause..." << endl;
	Engine::Instance().GetFSM().GetStates().front()->Render(); // Invoke Render of GameState.
	SDL_SetRenderDrawBlendMode(Engine::Instance().GetRenderer(), SDL_BLENDMODE_BLEND);
	SDL_SetRenderDrawColor(Engine::Instance().GetRenderer(), 0, 0, 255, 128);
	SDL_Rect rect = { 256, 128, 512, 512 };
	SDL_RenderFillRect(Engine::Instance().GetRenderer(), &rect);
	State::Render();
}

void PauseState::Exit()
{
	cout << "Exiting Pause..." << endl;
}
// End PauseState.

// Begin GameState.
GameState::GameState() {}

void GameState::Enter()
{
	cout << "Entering Game..." << endl;
}

void GameState::Update()
{
	if (Engine::Instance().KeyDown(SDL_SCANCODE_P))
		Engine::Instance().GetFSM().PushState(new PauseState());
	else if (Engine::Instance().KeyDown(SDL_SCANCODE_X))
		Engine::Instance().GetFSM().ChangeState(new TitleState());
}

void GameState::Render()
{
	cout << "Rendering Game..." << endl;
	SDL_SetRenderDrawColor(Engine::Instance().GetRenderer(), 0, 255, 0, 255);
	SDL_RenderClear(Engine::Instance().GetRenderer());
	if (dynamic_cast<GameState*>(Engine::Instance().GetFSM().GetStates().back()))
		State::Render();
}

void GameState::Exit()
{
	cout << "Exiting Game..." << endl;
}

void GameState::Resume()
{
	cout << "Resuming Game..." << endl;
}
// End GameState.

// Begin TitleState.
TitleState::TitleState() {}

void TitleState::Enter()
{
	cout << "Entering Title..." << endl;
	TheTextureManager::Instance()->load("../Assets/textures/Airlock_Logo.png", "title", Engine::Instance().GetRenderer());
}

void TitleState::Update()
{
	if (Engine::Instance().KeyDown(SDL_SCANCODE_N))
		Engine::Instance().GetFSM().ChangeState(new GameState());
}

void TitleState::Render()
{
	cout << "Rendering Title..." << endl;
	SDL_SetRenderDrawColor(Engine::Instance().GetRenderer(), 100, 100, 100, 255);
	SDL_RenderClear(Engine::Instance().GetRenderer());
	TheTextureManager::Instance()->draw("title", 1028/2, 768/2, Engine::Instance().GetRenderer(), true);
	State::Render();
}

void TitleState::Exit()
{
	cout << "Exiting Title..." << endl;
}
// End TitleState.

// Begin FSM.
FSM::FSM() {}
FSM::~FSM() {}

void FSM::Update()
{
	if (!m_vStates.empty())
		m_vStates.back()->Update(); // Invokes the Update of the current state.
}

void FSM::Render()
{
	if (!m_vStates.empty())
		m_vStates.back()->Render(); // Invokes the Render of the current state.
}
void FSM::ChangeState(State* pState)
{
	if (!m_vStates.empty())
	{
		m_vStates.back()->Exit(); // Invokes the Exit of the current state.
		delete m_vStates.back(); // Deallocates current state.
		m_vStates.back() = nullptr;
		m_vStates.pop_back();
	}
	//PushState(pState);
	pState->Enter(); // Invoke the Enter of the NEW current state.
	m_vStates.push_back(pState); // Push the address of the NEW current state into the vector.
}

void FSM::PushState(State* pState)
{
	pState->Enter(); // Invoke the Enter of the NEW current state.
	m_vStates.push_back(pState); // Push the address of the NEW current state into the vector.
}

void FSM::PopState() // e.g. PauseState to GameState.
{
	if (!m_vStates.empty())
	{
		m_vStates.back()->Exit(); // Invokes the Exit of the current state.
		delete m_vStates.back(); // Deallocates current state.
		m_vStates.back() = nullptr;
		m_vStates.pop_back();
	}
	m_vStates.back()->Resume();
}

void FSM::Clean()
{
	while (!m_vStates.empty())
	{
		m_vStates.back()->Exit(); // Invokes the Exit of the current state.
		delete m_vStates.back(); // Deallocates current state.
		m_vStates.back() = nullptr;
		m_vStates.pop_back();
	}
}

vector<State*>& FSM::GetStates() { return m_vStates; }
// End FSM.