/*
 * Engine header
 * Adapted from GBC GAME1011 SDL Template
 * Editors:
 * - Ryan Ethier
 */

#pragma once
#include <SDL.h>
#include <SDL_image.h>
#include <SDL_mixer.h>
#include <SDL_ttf.h>
#include "FSM.h"

class Engine
{
	//properties
private:
	bool m_bRunning; // Loop control flag.
	const Uint8* m_iKeystates; // Keyboard state container.
	Uint32 m_start, m_end, m_delta, m_fps; // Fixed timestep variables.
	SDL_Window* m_pWindow; // This represents the SDL window.
	SDL_Renderer* m_pRenderer; // This represents the buffer to draw to.
	FSM* m_pFSM;
	
	//methods
private:
	bool Init(const char* title, int xpos, int ypos, int width, int height, int flags);
	void Wake();
	void Sleep();
	void HandleEvents();

	void Update();
	void Render();
	void Clean();

	SDL_Point m_MousePos;
	bool m_MouseState[3] = { 0,0,0 }; // Button up/down. Left, Middle, Right.

public:
	Engine();
	~Engine();
	int Run();
	static Engine& Instance();
	bool KeyDown(SDL_Scancode c);
	SDL_Renderer* GetRenderer();
	FSM& GetFSM();
	SDL_Point& GetMousePos();
	bool GetMouseState(int idx);

	bool returnTitle = false; //check if user can go to title screen.
	bool gameWon = false; // check if user won

	vector <int> LevelPointsVec; //vector for points of each level
};
