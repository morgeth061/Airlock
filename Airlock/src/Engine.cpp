/*
 * Engine class
 * Adapted from GBC GAME1011 SDL Template
 * Editors:
 * - Ryan Ethier
 */

//includes
#include "Engine.h"
#include <iostream>
#define WIDTH 1024
#define HEIGHT 768
#define FPS 60

using namespace std;

//constructor
Engine::Engine() :m_bRunning(false)
{
	cout << "Engine class constructed!" << endl;
}

//deconstructor
Engine::~Engine()
{
	
}

//methods
bool Engine::Init(const char* title, int xpos, int ypos, int width, int height, int flags)
{
	cout << "Initializing game..." << endl;
	// Attempt to initialize SDL.
	if (SDL_Init(SDL_INIT_EVERYTHING) == 0)
	{
		// Create the window.
		m_pWindow = SDL_CreateWindow(title, xpos, ypos, width, height, flags);
		if (m_pWindow != nullptr) // Window init success.
		{
			m_pRenderer = SDL_CreateRenderer(m_pWindow, -1, 0);
			if (m_pRenderer != nullptr) // Renderer init success.
			{
				if (TTF_Init() >= 0) {
					cout << "TTF INIT" << endl;
				}
				else return false;
			}
			else return false; // Renderer init fail.
		}
		else return false; // Window init fail.
	}
	else return false; // SDL init fail.
	m_fps = (Uint32)round((1 / (double)FPS) * 1000); // Sets FPS in milliseconds and rounds.
	m_iKeystates = SDL_GetKeyboardState(nullptr);
	m_pFSM = new FSM();
	m_pFSM->ChangeState(new TitleState());
	m_bRunning = true; // Everything is okay, start the engine.
	cout << "Init success!" << endl;
	return true;
}

void Engine::Wake()
{
	m_start = SDL_GetTicks();
}

void Engine::Sleep()
{
	m_end = SDL_GetTicks();
	m_delta = m_end - m_start;
	if (m_delta < m_fps) // Engine has to sleep.
		SDL_Delay(m_fps - m_delta);
}

void Engine::HandleEvents()
{
	SDL_Event event;

	while (SDL_PollEvent(&event))
	{
		switch (event.type)
		{
		case SDL_QUIT: // User pressed window's 'x' button.
			m_bRunning = false;
			break;
		case SDL_KEYDOWN: // Try SDL_KEYUP instead.
			if (event.key.keysym.sym == SDLK_ESCAPE)
				m_bRunning = false;
			break;
		}
	}
}

// Keyboard utility function.
bool Engine::KeyDown(SDL_Scancode c)
{
	if (m_iKeystates != nullptr)
	{
		if (m_iKeystates[c] == 1)
			return true;
		else
			return false;
	}
	return false;
}

void Engine::Update()
{
	m_pFSM->Update();
}

void Engine::Render()
{
	m_pFSM->Render();

}

void Engine::Clean()
{
	cout << "Cleaning game." << endl;
	SDL_DestroyRenderer(m_pRenderer);
	SDL_DestroyWindow(m_pWindow);
	TTF_Quit();
	SDL_Quit();
}

int Engine::Run()
{
	if (m_bRunning) 
		return -1;
	if (Init("Airlock", SDL_WINDOWPOS_CENTERED, SDL_WINDOWPOS_CENTERED, WIDTH, HEIGHT, 0) == false)
		return 1;
	while (m_bRunning) // Main engine loop.
	{
		Wake();
		HandleEvents();
		Update();
		Render();
		if (m_bRunning)
			Sleep();
	}
	Clean();
	return 0;
}


Engine& Engine::Instance() //static method that creates the instance
{
	static Engine instance;
	return instance;
}

SDL_Renderer* Engine::GetRenderer()
{
	return m_pRenderer;
}

FSM& Engine::GetFSM()
{
	return *m_pFSM;
}


void Engine::SetGameWon()
{
	m_bRunning = false;
	Clean();
}