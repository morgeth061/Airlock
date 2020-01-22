#pragma once
#ifndef __TEXT_MANAGER__
#define __TEXT_MANAGER__

#include <iostream>
#include <string>

#include "SDL.h"
#include "SDL_ttf.h"

using namespace std;

class TextManager
{
private:
	//constructor
	TextManager();

	//deconstructor
	~TextManager();

	static TextManager* s_pInstance;

public:
	static TextManager* Instance()
	{
		if (s_pInstance == 0)
		{
			s_pInstance = new TextManager();
			return s_pInstance;
		}
	}

	void setTextColour(string id, Uint8 red, Uint8 green, Uint8 blue);
	void setTextFont(string fontName);
};

typedef TextManager TheTextManager;

#endif /*defined __TEXT_MANAGER__*/