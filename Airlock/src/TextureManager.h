/*
 * Texture Manager header file
 * Taken from GBC GAME3001 SDL Template
 * Editors:
 * - Ryan Ethier
 */

#pragma once
#ifndef __TextureManager__
#define __TextureManager__

// Core Libraries
#include <iostream>
#include <string>
#include <map> 

//#include <glm\vec2.hpp>

// SDL Libraries
#include<SDL.h>
#include<SDL_image.h>


class TextureManager {
public:
	static TextureManager* Instance()
	{
		if (s_pInstance == 0)
		{
			s_pInstance = new TextureManager();
			return s_pInstance;
		}

		return s_pInstance;
	}


	bool load(std::string fileName, std::string id, SDL_Renderer* pRenderer);

	void draw(std::string id, int x, int y, int width, int height, SDL_Renderer* pRenderer, SDL_RendererFlip flip = SDL_FLIP_NONE);
	void draw(std::string id, int x, int y, SDL_Renderer* pRenderer, bool centered = false, SDL_RendererFlip flip = SDL_FLIP_NONE);
	void draw(std::string id, int x, int y, int width, int height, SDL_Renderer* pRenderer, double angle, int alpha, SDL_RendererFlip flip = SDL_FLIP_NONE);
	void draw(std::string id, int x, int y, SDL_Renderer* pRenderer, double angle, int alpha, bool centered = false, SDL_RendererFlip flip = SDL_FLIP_NONE);

	void drawFrame(std::string id, int x, int y, int width, int height, int currentRow, int currentFrame, SDL_Renderer* pRenderer, SDL_RendererFlip flip = SDL_FLIP_NONE);
	void drawFrame(std::string id, int x, int y, int currentRow, int currentFrame, SDL_Renderer* pRenderer, bool centered = false, SDL_RendererFlip flip = SDL_FLIP_NONE);
	void drawFrame(std::string id, int x, int y, int width, int height, int currentRow, int currentFrame, SDL_Renderer* pRenderer, double angle, int alpha, SDL_RendererFlip flip = SDL_FLIP_NONE);
	void drawFrame(std::string id, int x, int y, int currentRow, int currentFrame, SDL_Renderer* pRenderer, double angle, int alpha, bool centered = false, SDL_RendererFlip flip = SDL_FLIP_NONE);

	//glm::vec2 getTextureSize(std::string id);

	void setAlpha(std::string id, Uint8 newAlpha);

	void setColour(std::string id, Uint8 red, Uint8 green, Uint8 blue);

private:

	TextureManager();
	~TextureManager();

	std::map<std::string, SDL_Texture*> m_textureMap;

	static TextureManager* s_pInstance;
};

typedef TextureManager TheTextureManager;

#endif /* defined(__TextureManager__) */
