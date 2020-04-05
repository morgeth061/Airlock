/*
 * Texture Manager header file
 * Adapted from GBC GAME3001 SDL Template
 * Editors:
 * - Ryan Ethier
 */

#pragma once
#ifndef __TEXTURE_MANAGER__
#define __TEXTURE_MANAGER__

 // Core Libraries
#include <iostream>
#include <string>
#include <unordered_map>

#include "glm/vec2.hpp"

// SDL Libraries
#include<SDL.h>
#include<SDL_image.h>

#include "Config.h"


class TextureManager {
public:
	//Singleton
	static TextureManager* Instance()
	{
		if (s_pInstance == 0)
		{
			s_pInstance = new TextureManager();
			return s_pInstance;
		}

		return s_pInstance;
	}


	bool load(const std::string& file_name, const std::string& id, SDL_Renderer* renderer);

	void draw(std::string id, int x, int y, int width, int height, SDL_Renderer* pRenderer, SDL_RendererFlip flip = SDL_FLIP_NONE);
	void draw(std::string id, int x, int y, SDL_Renderer* pRenderer, bool centered = false, SDL_RendererFlip flip = SDL_FLIP_NONE);
	void draw();
	void draw(std::string id, int x, int y, int width, int height, SDL_Renderer* pRenderer, double angle, int alpha, SDL_RendererFlip flip = SDL_FLIP_NONE);
	void draw(std::string id, int x, int y, SDL_Renderer* pRenderer, double angle, int alpha, bool centered = false, SDL_RendererFlip flip = SDL_FLIP_NONE);

	void drawFrame(std::string id, int x, int y, int width, int height, int currentRow, int currentFrame, SDL_Renderer* pRenderer, SDL_RendererFlip flip = SDL_FLIP_NONE);
	void drawFrame(std::string id, int x, int y, int currentRow, int currentFrame, SDL_Renderer* pRenderer, bool centered = false, SDL_RendererFlip flip = SDL_FLIP_NONE);
	void drawFrame(std::string id, int x, int y, int width, int height, int currentRow, int currentFrame, SDL_Renderer* pRenderer, double angle, int alpha, SDL_RendererFlip flip = SDL_FLIP_NONE);
	void drawFrame(std::string id, int x, int y, int currentRow, int currentFrame, SDL_Renderer* pRenderer, double angle, int alpha, bool centered = false, SDL_RendererFlip flip = SDL_FLIP_NONE);

	void drawText(const std::string& id, int x, int y, SDL_Renderer* renderer, double angle, int alpha, bool centered = false, SDL_RendererFlip flip = SDL_FLIP_NONE);

	glm::vec2 getTextureSize(std::string id);

	bool addTexture(const std::string& id, std::shared_ptr<SDL_Texture> texture);
	SDL_Texture* getTexture(const std::string& id);

	void setAlpha(std::string id, Uint8 newAlpha);

	void setColour(std::string id, Uint8 red, Uint8 green, Uint8 blue);

private:

	//constructor
	TextureManager();

	//deconstructor
	~TextureManager();

	//texture map
	std::unordered_map<std::string, std::shared_ptr<SDL_Texture>> m_textureMap;

	bool m_exists(const std::string& id);


	//singleton
	static TextureManager* s_pInstance;
};

//definition
typedef TextureManager Texture;

#endif /* defined(__TEXTURE_MANAGER__) */
