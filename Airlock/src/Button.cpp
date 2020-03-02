#include <iostream>
#include "Button.h"
#include "Engine.h"
#include "Game.h"
#include "SDL.h"
#include "SDL_image.h"

using namespace std;

Button::Button(const char* s, SDL_Rect src, SDL_Rect dst)
	: m_rSrc(src), m_rDst(dst), m_state(STATE_UP)
{
	cout << "Constructing button!" << endl;
	// Set the button image. You should have some fail checking just in case. 
	m_pText = IMG_LoadTexture(Engine::Instance().GetRenderer(), s);
}

Button::~Button()
{
	SDL_DestroyTexture(m_pText);
}

bool Button::MouseCollision()
{
	int mx = Engine::Instance().GetMousePos().x;
	int my = Engine::Instance().GetMousePos().y;
	return (mx < (m_rDst.x + m_rDst.w) && mx > m_rDst.x &&
		    my < (m_rDst.y + m_rDst.h) && my > m_rDst.y);
}

void Button::Update()
{
	bool col = MouseCollision();
	switch (m_state)
	{
	case STATE_UP:
		if (col)   
			m_state = STATE_OVER;
		break;
	case STATE_OVER:
		if (!col)
			m_state = STATE_UP;
		else if (col && Engine::Instance().GetMouseState(0))
			m_state = STATE_DOWN;
		break;
	case STATE_DOWN:
		if (!Engine::Instance().GetMouseState(0))
		{
			if (col)
			{
				m_state = STATE_OVER;
				// Execute new "callback".
				Execute();
			}
			else 
				m_state = STATE_UP;
		}
		break;
	}
}

void Button::Render()
{
	m_rSrc.x = m_rSrc.w * (int)m_state;
	SDL_RenderCopy(Engine::Instance().GetRenderer(), m_pText, &m_rSrc, &m_rDst);
}

// Yes, the downside of the command pattern is we need a subclass for each unique type of button.

PlayButton::PlayButton(const char * s, SDL_Rect src, SDL_Rect dst):Button(s, src, dst){}
void PlayButton::Execute()
{
	Engine::Instance().GetFSM().ChangeState(new GameState());
}

MenuButton::MenuButton(const char* s, SDL_Rect src, SDL_Rect dst) :Button(s, src, dst) {}
void MenuButton::Execute()
{
	Engine::Instance().GetFSM().ChangeState(new TitleState());
}

LevelSelectButton::LevelSelectButton(const char* s, SDL_Rect src, SDL_Rect dst) :Button(s, src, dst) {}
void LevelSelectButton::Execute()
{
	Engine::Instance().GetFSM().ChangeState(new LevelSelectState());
}

Level1Button::Level1Button(const char* s, SDL_Rect src, SDL_Rect dst) :Button(s, src, dst) {}
void Level1Button::Execute()
{
	Engine::Instance().GetFSM().ChangeState(new GameState());
}

Level2Button::Level2Button(const char* s, SDL_Rect src, SDL_Rect dst) :Button(s, src, dst) {}
void Level2Button::Execute()
{
	Game::Instance()->setCurrentLevel(LEVEL2);
	Engine::Instance().GetFSM().ChangeState(new GameState());
}

Level3Button::Level3Button(const char* s, SDL_Rect src, SDL_Rect dst) :Button(s, src, dst) {}
void Level3Button::Execute()
{
	Game::Instance()->setCurrentLevel(LEVEL2);
	Engine::Instance().GetFSM().ChangeState(new GameState());
}

ExitButton::ExitButton(const char * s, SDL_Rect src, SDL_Rect dst):Button(s, src, dst){}
void ExitButton::Execute()
{
	exit(EXIT_SUCCESS);
}

ResumeButton::ResumeButton(const char * s, SDL_Rect src, SDL_Rect dst) :Button(s, src, dst) {}
void ResumeButton::Execute()
{
	Engine::Instance().GetFSM().PopState();
}