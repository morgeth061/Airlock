//includes
#include "FSM.h"
#include "Engine.h"
#include "Game.h"
#include "Button.h"
#include "TextureManager.h"
#include "SoundManager.h"
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

void PauseState::HandleEvents() {} //handle events for pause state 

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
	Game::Instance()->init();
}

void GameState::Enter() //"on enter" of game state
{
	cout << "Entering Game..." << endl;
	//Load Textures
	Texture::Instance()->load("../Assets/textures/FP_Level1.png", "Level1", TheGame::Instance()->getRenderer());
	Texture::Instance()->load("../Assets/textures/FP_Level1_Walls.png", "Level1Walls", TheGame::Instance()->getRenderer());
	Texture::Instance()->load("../Assets/textures/FP_Level2.png", "Level2", TheGame::Instance()->getRenderer());
	Texture::Instance()->load("../Assets/textures/FP_Level2_Walls.png", "Level2Walls", TheGame::Instance()->getRenderer());
	Texture::Instance()->load("../Assets/textures/FP_Level3.png", "Level3", TheGame::Instance()->getRenderer());
	Texture::Instance()->load("../Assets/textures/FP_Level3_Walls.png", "Level3Walls", TheGame::Instance()->getRenderer());
	Texture::Instance()->load("../Assets/textures/FP_Debug.png", "Debug", TheGame::Instance()->getRenderer());
	Texture::Instance()->load("../Assets/textures/Player_Circle.png", "playerCircle", TheGame::Instance()->getRenderer());
	Texture::Instance()->load("../Assets/textures/Player_Circle_Transparent.png", "playerCircleTransparent", TheGame::Instance()->getRenderer());
	Texture::Instance()->load("../Assets/textures/playerHealthBack.png", "playerHealthBack", TheGame::Instance()->getRenderer());
	Texture::Instance()->load("../Assets/textures/playerHealth.png", "playerHealthBar", TheGame::Instance()->getRenderer());
	Texture::Instance()->load("../Assets/textures/playerInventory.png", "playerInv", TheGame::Instance()->getRenderer());
	Texture::Instance()->load("../Assets/textures/playerInventorySelected.png", "playerInvSelected", TheGame::Instance()->getRenderer());
	Texture::Instance()->load("../Assets/textures/Loading_Screen.png", "loadingScreen", TheGame::Instance()->getRenderer());
	Texture::Instance()->load("../Assets/textures/ScoreScreen_v1.png", "WonScreen", TheGame::Instance()->getRenderer());	Texture::Instance()->load("../Assets/textures/BreakableRock.png", "breakableRock", TheGame::Instance()->getRenderer());
	Texture::Instance()->load("../Assets/textures/Chest_Open.png", "chestOpen", TheGame::Instance()->getRenderer());
	Texture::Instance()->load("../Assets/textures/Chest_Closed.png", "chestClosed", TheGame::Instance()->getRenderer());

	//load sounds
	SoundManager::Instance()->load("../Assets/audio/Sound/Enemy_Hurt.wav", "enemyHurt", SOUND_SFX);
	SoundManager::Instance()->load("../Assets/audio/Sound/Game_Start.wav", "gameStart", SOUND_SFX);
	SoundManager::Instance()->load("../Assets/audio/Sound/Player_Death.wav", "playerDeath", SOUND_SFX);
	SoundManager::Instance()->load("../Assets/audio/Sound/Player_Hurt.wav", "playerHurt", SOUND_SFX);
	SoundManager::Instance()->load("../Assets/audio/Sound/Player_Pickup.wav", "playerPickup", SOUND_SFX);
	SoundManager::Instance()->load("../Assets/audio/Sound/Player_Shot1.wav", "playerShot1", SOUND_SFX);
	SoundManager::Instance()->load("../Assets/audio/Sound/Player_Shot2.wav", "playerShot2", SOUND_SFX);
	SoundManager::Instance()->load("../Assets/audio/Sound/Player_Slash.wav", "playerSlash", SOUND_SFX);
	SoundManager::Instance()->load("../Assets/audio/Sound/Player_Walk.wav", "playerWalk", SOUND_SFX);

	SoundManager::Instance()->playSound("gameStart", 0);
}

void GameState::Update() //update for game state
{
	TheGame::Instance()->update();
	//if (Engine::Instance().KeyDown(SDL_SCANCODE_P))
	//	Engine::Instance().GetFSM().PushState(new PauseState());
	//else if (Engine::Instance().KeyDown(SDL_SCANCODE_X))
	//	Engine::Instance().GetFSM().ChangeState(new TitleState());
}

void GameState::Render() //render for game state
{
	//SDL_RenderClear(Engine::Instance().GetRenderer());
	TheGame::Instance()->render();
	//Texture::Instance()->draw("level1Map", 0, 0, Engine::Instance().GetRenderer(), false);
	if (dynamic_cast<GameState*>(Engine::Instance().GetFSM().GetStates().back()))
	State::Render();
}

void GameState::HandleEvents() //handle events for game state 
{
	TheGame::Instance()->handleEvents();
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
 * LEVEL SELECT STATE
 */

 // Begin TitleState.
LevelSelectState::LevelSelectState() //ctor. for title state
{

}

void LevelSelectState::Enter() //"on enter" for title state
{
	cout << "Entering Title..." << endl;
	Texture::Instance()->load("../Assets/textures/Airlock_Logo.png", "title", Engine::Instance().GetRenderer());
	Texture::Instance()->load("../Assets/textures/TitleScreen.png", "titleScreen", Engine::Instance().GetRenderer());
	m_vButtons.push_back(new Level1Button("../Assets/textures/A_Button_Level1.png", { 0,0,500,100 }, { (1856 / 2) - 250,(960 / 2),500,100 }));
	m_vButtons.push_back(new Level2Button("../Assets/textures/A_Button_Level2.png", { 0,0,500,100 }, { (1856 / 2) - 250,(960 / 2) + 125,500,100 }));
	m_vButtons.push_back(new Level3Button("../Assets/textures/A_Button_Level3.png", { 0,0,500,100 }, { (1856 / 2) - 250,(960 / 2) + 250,500,100 }));
}

void LevelSelectState::Update() //update for title state
{
	if (Engine::Instance().KeyDown(SDL_SCANCODE_RETURN))
		Engine::Instance().GetFSM().ChangeState(new GameState());
	for (int i = 0; i < m_vButtons.size(); i++)
	{
		if (m_vButtons[i]->Update() == 1) return;
	}
}

void LevelSelectState::Render() //render for title state
{
	SDL_SetRenderDrawColor(Engine::Instance().GetRenderer(), 100, 100, 100, 255);
	SDL_RenderClear(Engine::Instance().GetRenderer());
	Texture::Instance()->draw("titleScreen", 0, 0, Engine::Instance().GetRenderer(), false);
	//Texture::Instance()->draw("title", (1028 / 2) - 7, 768 / 3, Engine::Instance().GetRenderer(), true);
	//Texture::Instance()->draw("begin", 1028 / 2, 768 / 2, Engine::Instance().GetRenderer(), true);
	for (int i = 0; i < m_vButtons.size(); i++)
		m_vButtons[i]->Render();
	State::Render();
}

void LevelSelectState::HandleEvents() {} //handle events for level select state 

void LevelSelectState::Exit() //"on exit" for title state
{
	cout << "Exiting Title..." << endl;
	for (int i = 0; i < m_vButtons.size(); i++)
	{
		delete m_vButtons[i];
		m_vButtons[i] = nullptr;
	}
	m_vButtons.clear();
	m_vButtons.shrink_to_fit();
}
// End LevelSelectState.

/*
 * TITLE STATE
 */

 // Begin TitleState.
TitleState::TitleState() //ctor. for title state
{
	m_vButtons.push_back(new PlayButton("../Assets/textures/A_Button_StartGame.png", { 0,0,500,100 }, { (1856 / 2) - 250,960/2,500,100 }));
	m_vButtons.push_back(new LevelSelectButton("../Assets/textures/A_Button_LevelSelect.png", { 0,0,500,100 }, { (1856 / 2) - 250,(960/2) + 125,500,100 }));
}

void TitleState::Enter() //"on enter" for title state
{
	cout << "Entering Title..." << endl;

	//load textures
	Texture::Instance()->load("../Assets/textures/Airlock_Logo.png", "title", Engine::Instance().GetRenderer());
	Texture::Instance()->load("../Assets/textures/TitleScreen.png", "titleScreen", Engine::Instance().GetRenderer());
	Texture::Instance()->load("../Assets/textures/Begin_Game.png", "begin", Engine::Instance().GetRenderer());

	//load sounds
	SoundManager::Instance()->load("../Assets/audio/Music/Music_World1.mp3", "world1Music", SOUND_MUSIC);

	SoundManager::Instance()->playMusic("world1Music", -1);
	
	m_vButtons.push_back(new PlayButton("../Assets/textures/A_Button_StartGame.png", { 0,0,500,100 }, { (1856/2)-250,960 / 2,500,100 }));
	m_vButtons.push_back(new LevelSelectButton("../Assets/textures/A_Button_LevelSelect.png", { 0,0,500,100 }, { (1856 / 2) - 250,(960 / 2) + 125,500,100 }));
}

void TitleState::Update() //update for title state
{
	if (Engine::Instance().KeyDown(SDL_SCANCODE_RETURN))
		Engine::Instance().GetFSM().ChangeState(new GameState());
	for (int i = 0; i < m_vButtons.size(); i++)
	{
		if (m_vButtons[i]->Update() == 1) return;
	}
}

void TitleState::Render() //render for title state
{
	SDL_SetRenderDrawColor(Engine::Instance().GetRenderer(), 100, 100, 100, 255);
	SDL_RenderClear(Engine::Instance().GetRenderer());
	Texture::Instance()->draw("titleScreen", 0, 0, Engine::Instance().GetRenderer(), false);
	//Texture::Instance()->draw("title", (1028/2)-7, 768/3, Engine::Instance().GetRenderer(), true);
	//Texture::Instance()->draw("begin", 1028 / 2, 768 / 2, Engine::Instance().GetRenderer(), true);
	for (int i = 0; i < m_vButtons.size(); i++)
		m_vButtons[i]->Render();
	State::Render();
}

void TitleState::HandleEvents() {} // handle events for title state


void TitleState::Exit() //"on exit" for title state
{
	cout << "Exiting Title..." << endl;
	for (int i = 0; i < m_vButtons.size(); i++)
	{
		delete m_vButtons[i];
		m_vButtons[i] = nullptr;
	}
	m_vButtons.clear();
	m_vButtons.shrink_to_fit();
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

void FSM::HandleEvents()
{
	if (!m_vStates.empty())
		m_vStates.back()->HandleEvents(); // Invokes the Handle Events of the current state.
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