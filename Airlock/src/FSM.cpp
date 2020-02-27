//includes
#include "FSM.h"
#include "Engine.h"
#include "Game.h"
#include "TextureManager.h"
#include <iostream>

using namespace std;

//GENERAL
int playerHealth;

//begin current state
void State::Render()
{
	SDL_RenderPresent(Engine::Instance().GetRenderer());
}

void State::Resume()
{
	
}
//end current state

/*
 * PAUSE STATE
 */

PauseState::PauseState() //ctor. of pause state
{
	
}

void PauseState::Enter() //"on enter" for pause state
{
	cout << "Entering Pause State" << endl;
}

void PauseState::Update() //update for pause state
{
	if (Engine::Instance().KeyDown(SDL_SCANCODE_RETURN))
		Engine::Instance().GetFSM().PopState();
}

void PauseState::Render() //render for pause state
{
	Engine::Instance().GetFSM().GetStates().front()->Render();
	SDL_SetRenderDrawBlendMode(Engine::Instance().GetRenderer(), SDL_BLENDMODE_BLEND);
	SDL_SetRenderDrawColor(Engine::Instance().GetRenderer(), 0, 0, 255, 128);
	SDL_Rect rect = { 256, 128, 512, 512 };
	SDL_RenderFillRect(Engine::Instance().GetRenderer(), &rect);
	State::Render();
}

void PauseState::Exit() //"on exit" for pause state
{
	cout << "Exiting Pause..." << endl;
}
//end of pause state

/*
 * GAME STATE
 */

GameState::GameState() //ctor. of game state
{
	//Game::Instance()->init("Airlock", 0, 0, 1856, 960, false);
	Game::Instance()->init("Airlock", 0, 0, 1856, 960, false);
}

void GameState::Enter() //"on enter" of game state
{
	cout << "Entering Game..." << endl;
	Texture::Instance()->load("../Assets/textures/FP_Level1.png", "Level1", TheGame::Instance()->getRenderer());
	Texture::Instance()->load("../Assets/textures/FP_Level2.png", "Level2", TheGame::Instance()->getRenderer());
	Texture::Instance()->load("../Assets/textures/playerHealthBack.png", "playerHealthBack", TheGame::Instance()->getRenderer());
	Texture::Instance()->load("../Assets/textures/playerHealth.png", "playerHealthBar", TheGame::Instance()->getRenderer());
	Texture::Instance()->load("../Assets/textures/playerInventory.png", "playerInv", TheGame::Instance()->getRenderer());
	Texture::Instance()->load("../Assets/textures/playerInventorySelected.png", "playerInvSelected", TheGame::Instance()->getRenderer());
	Texture::Instance()->load("../Assets/textures/Loading_Screen.png", "loadingScreen", TheGame::Instance()->getRenderer());
}

void GameState::Update() //update for game state
{
	while (TheGame::Instance()->running())
	{
		TheGame::Instance()->handleEvents();
		TheGame::Instance()->update();
		TheGame::Instance()->render();

	}
	if (Engine::Instance().KeyDown(SDL_SCANCODE_P))
		Engine::Instance().GetFSM().PushState(new PauseState());
	else if (Engine::Instance().KeyDown(SDL_SCANCODE_X))
		Engine::Instance().GetFSM().ChangeState(new TitleState());
}

void GameState::Render() //render for game state
{
	SDL_SetRenderDrawColor(Engine::Instance().GetRenderer(), 255, 255, 255, 255);
	SDL_RenderClear(Engine::Instance().GetRenderer());
	//Texture::Instance()->draw("level1Map", 0, 0, Engine::Instance().GetRenderer(), false);
	if (dynamic_cast<GameState*>(Engine::Instance().GetFSM().GetStates().back()))
		State::Render();
}

void GameState::Exit() //"on exit" for game state
{
	TheGame::Instance()->clean();
	cout << "Exiting Game..." << endl;
}

void GameState::Resume() //on resume from pause
{
	cout << "Resuming Game..." << endl;
}
// End GameState.

/*
 * TITLE STATE
 */

// Begin TitleState.
TitleState::TitleState() //ctor. for title state
{
	
}

void TitleState::Enter() //"on enter" for title state
{
	cout << "Entering Title..." << endl;
	Texture::Instance()->load("../Assets/textures/Airlock_Logo.png", "title", Engine::Instance().GetRenderer());
	Texture::Instance()->load("../Assets/textures/Background.png", "background", Engine::Instance().GetRenderer());
	Texture::Instance()->load("../Assets/textures/Begin_Game.png", "begin", Engine::Instance().GetRenderer());
}

void TitleState::Update() //update for title state
{
	if (Engine::Instance().KeyDown(SDL_SCANCODE_RETURN))
		Engine::Instance().GetFSM().ChangeState(new GameState());
}

void TitleState::Render() //render for title state
{
	SDL_SetRenderDrawColor(Engine::Instance().GetRenderer(), 100, 100, 100, 255);
	SDL_RenderClear(Engine::Instance().GetRenderer());
	Texture::Instance()->draw("background", 0, 0, Engine::Instance().GetRenderer(), false);
	Texture::Instance()->draw("title", (1028/2)-7, 768/3, Engine::Instance().GetRenderer(), true);
	Texture::Instance()->draw("begin", 1028 / 2, 768 / 2, Engine::Instance().GetRenderer(), true);
	State::Render();
}

void TitleState::Exit() //"on exit" for title state
{
	cout << "Exiting Title..." << endl;
}
// End TitleState.

// Begin FSM.

//FSM constructor
FSM::FSM()
{
	
}

//FSM deconstructor
FSM::~FSM()
{
	
}

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
	//end of state
	if (!m_vStates.empty())
	{
		m_vStates.back()->Exit();
		delete m_vStates.back();
		m_vStates.back() = nullptr;
		m_vStates.pop_back();
	}
	m_vStates.back()->Resume();
}

void FSM::Clean()
{
	//cleanup
	while (!m_vStates.empty())
	{
		m_vStates.back()->Exit();
		delete m_vStates.back();
		m_vStates.back() = nullptr;
		m_vStates.pop_back();
	}
}

vector<State*>& FSM::GetStates() { return m_vStates; }
// End FSM.