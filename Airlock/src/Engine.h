#pragma once
#include <SDL.h>
#include <SDL_image.h>
#include <SDL_mixer.h>
#include <SDL_ttf.h>

// Do not include any macros, initialized properties or full function definitions in this header.

class Engine
{
private: // Private properties.
	bool m_bRunning; // Loop control flag.
	const Uint8* m_iKeystates; // Keyboard state container.
	Uint32 m_start, m_end, m_delta, m_fps; // Fixed timestep variables.
	SDL_Window* m_pWindow; // This represents the SDL window.
	SDL_Renderer* m_pRenderer; // This represents the buffer to draw to.

private: // Private methods.
	bool Init(const char* title, int xpos, int ypos, int width, int height, int flags);
	void Wake();
	void Sleep();
	void HandleEvents();

	void Update();
	void Render();
	void Clean();
public: // Public methods.
	Engine();
	~Engine();
	int Run();
	static Engine& Instance();
	bool KeyDown(SDL_Scancode c);
};
