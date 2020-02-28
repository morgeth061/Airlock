#pragma once
#include "SDL.h"

class Button // Button is now an example of the command design pattern.
{
protected: // Private but inherited!
	enum state { STATE_UP, STATE_OVER, STATE_DOWN } m_state; // Note the new syntax and missing m_iFrame.
	SDL_Rect m_rSrc;
	SDL_Rect m_rDst;
	SDL_Texture* m_pText;
	//std::function<void()> m_callback; // No more callback!
	bool MouseCollision(); // Moved here. Not needed outside class.
	virtual void Execute() = 0; // Pure virtual method, meaning Button is now an abstract class (interface)!
public:
	Button(const char* s, SDL_Rect src, SDL_Rect dst);
	~Button();
	void Update();
	void Render();
};

class PlayButton : public Button
{
private:
	void Execute();
public:
	PlayButton(const char* s, SDL_Rect src, SDL_Rect dst);
};

class MenuButton : public Button
{
private:
	void Execute();
public:
	MenuButton(const char* s, SDL_Rect src, SDL_Rect dst);
};

class LevelSelectButton : public Button
{
private:
	void Execute();
public:
	LevelSelectButton(const char* s, SDL_Rect src, SDL_Rect dst);
};

class Level1Button : public Button
{
private:
	void Execute();
public:
	Level1Button(const char* s, SDL_Rect src, SDL_Rect dst);
};

class Level2Button : public Button
{
private:
	void Execute();
public:
	Level2Button(const char* s, SDL_Rect src, SDL_Rect dst);
};

class Level3Button : public Button
{
private:
	void Execute();
public:
	Level3Button(const char* s, SDL_Rect src, SDL_Rect dst);
};


class ExitButton : public Button
{
private: 
	void Execute();
public:
	ExitButton(const char* s, SDL_Rect src, SDL_Rect dst);
};

class ResumeButton : public Button
{
private:
	void Execute();
public:
	ResumeButton(const char* s, SDL_Rect src, SDL_Rect dst);
};