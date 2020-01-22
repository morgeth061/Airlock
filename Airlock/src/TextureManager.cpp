/*
 * Texture Manager class
 * Taken from GBC GAME3001 SDL Template
 * Editors:
 * - Ryan Ethier
 */

#include "TextureManager.h"

TextureManager* TextureManager::s_pInstance = 0;

TextureManager::TextureManager()
{
}

TextureManager::~TextureManager()
{
}

bool TextureManager::load(std::string fileName, std::string id, SDL_Renderer* pRenderer)
{
	SDL_Surface* pTempSurface = IMG_Load(fileName.c_str());

	if (pTempSurface == 0)
	{
		return false;
	}
	SDL_Texture* pTexture = SDL_CreateTextureFromSurface(pRenderer, pTempSurface);

	SDL_FreeSurface(pTempSurface);

	// everything went ok, add the texture to our list
	if (pTexture != 0)
	{
		m_textureMap[id] = pTexture;
		return true;
	}
	// reaching here means something went wrong
	return false;
}

void TextureManager::draw(std::string id, int x, int y, int width, int height, SDL_Renderer* pRenderer, SDL_RendererFlip flip)
{
	SDL_Rect srcRect;
	SDL_Rect destRect;
	srcRect.x = 0;
	srcRect.y = 0;
	srcRect.w = destRect.w = width;
	srcRect.h = destRect.h = height;
	destRect.x = x;
	destRect.y = y;
	SDL_RenderCopyEx(pRenderer, m_textureMap[id], &srcRect, &destRect, 0, 0, flip);
}

void TextureManager::draw(std::string id, int x, int y, SDL_Renderer* pRenderer, bool centered, SDL_RendererFlip flip)
{
	SDL_Rect srcRect;
	SDL_Rect destRect;

	srcRect.x = 0;
	srcRect.y = 0;

	int textureWidth, textureHeight;

	SDL_QueryTexture(m_textureMap[id], NULL, NULL, &textureWidth, &textureHeight);

	srcRect.w = destRect.w = textureWidth;
	srcRect.h = destRect.h = textureHeight;

	if (centered) {
		int xOffset = textureWidth * 0.5;
		int yOffset = textureHeight * 0.5;
		destRect.x = x - xOffset;
		destRect.y = y - yOffset;
	}
	else {
		destRect.x = x;
		destRect.y = y;
	}

	SDL_RenderCopyEx(pRenderer, m_textureMap[id], &srcRect, &destRect, 0, 0, flip);
}

void TextureManager::draw(std::string id, int x, int y, int width, int height, SDL_Renderer* pRenderer, double angle, int alpha, SDL_RendererFlip flip)
{
	SDL_Rect srcRect;
	SDL_Rect destRect;
	srcRect.x = 0;
	srcRect.y = 0;
	srcRect.w = destRect.w = width;
	srcRect.h = destRect.h = height;
	destRect.x = x;
	destRect.y = y;

	SDL_SetTextureAlphaMod(m_textureMap[id], alpha);
	SDL_RenderCopyEx(pRenderer, m_textureMap[id], &srcRect, &destRect, angle, 0, flip);
}

void TextureManager::draw(std::string id, int x, int y, SDL_Renderer* pRenderer, double angle, int alpha, bool centered, SDL_RendererFlip flip)
{
	SDL_Rect srcRect;
	SDL_Rect destRect;

	srcRect.x = 0;
	srcRect.y = 0;

	int textureWidth, textureHeight;

	SDL_QueryTexture(m_textureMap[id], NULL, NULL, &textureWidth, &textureHeight);

	srcRect.w = destRect.w = textureWidth;
	srcRect.h = destRect.h = textureHeight;

	if (centered) {
		int xOffset = textureWidth * 0.5;
		int yOffset = textureHeight * 0.5;
		destRect.x = x - xOffset;
		destRect.y = y - yOffset;
	}
	else {
		destRect.x = x;
		destRect.y = y;
	}

	SDL_SetTextureAlphaMod(m_textureMap[id], alpha);
	SDL_RenderCopyEx(pRenderer, m_textureMap[id], &srcRect, &destRect, angle, 0, flip);
}

void TextureManager::drawFrame(std::string id, int x, int y, int width, int height, int currentRow, int currentFrame, SDL_Renderer* pRenderer, SDL_RendererFlip flip)
{
	SDL_Rect srcRect;
	SDL_Rect destRect;

	srcRect.x = width * currentFrame;
	srcRect.y = height * (currentRow - 1);
	srcRect.w = destRect.w = width;
	srcRect.h = destRect.h = height;
	destRect.x = x;
	destRect.y = y;
	SDL_RenderCopyEx(pRenderer, m_textureMap[id], &srcRect, &destRect, 0, 0, flip);
}

void TextureManager::drawFrame(std::string id, int x, int y, int currentRow, int currentFrame, SDL_Renderer* pRenderer, bool centered, SDL_RendererFlip flip)
{
	SDL_Rect srcRect;
	SDL_Rect destRect;

	int textureWidth, textureHeight;

	SDL_QueryTexture(m_textureMap[id], NULL, NULL, &textureWidth, &textureHeight);

	srcRect.x = textureWidth * currentFrame;
	srcRect.y = textureHeight * (currentRow - 1);
	srcRect.w = destRect.w = textureWidth;
	srcRect.h = destRect.h = textureHeight;

	if (centered) {
		int xOffset = textureWidth * 0.5;
		int yOffset = textureHeight * 0.5;
		destRect.x = x - xOffset;
		destRect.y = y - yOffset;
	}
	else {
		destRect.x = x;
		destRect.y = y;
	}

	SDL_RenderCopyEx(pRenderer, m_textureMap[id], &srcRect, &destRect, 0, 0, flip);
}

void TextureManager::drawFrame(std::string id, int x, int y, int width, int height, int currentRow, int currentFrame, SDL_Renderer* pRenderer, double angle, int alpha, SDL_RendererFlip flip)
{
	SDL_Rect srcRect;
	SDL_Rect destRect;

	srcRect.x = width * currentFrame;
	srcRect.y = height * currentRow;
	srcRect.w = destRect.w = width;
	srcRect.h = destRect.h = height;
	destRect.x = x;
	destRect.y = y;

	SDL_SetTextureAlphaMod(m_textureMap[id], alpha);
	SDL_RenderCopyEx(pRenderer, m_textureMap[id], &srcRect, &destRect, angle, 0, flip);
}

void TextureManager::drawFrame(std::string id, int x, int y, int currentRow, int currentFrame, SDL_Renderer* pRenderer, double angle, int alpha, bool centered, SDL_RendererFlip flip)
{
	SDL_Rect srcRect;
	SDL_Rect destRect;

	int textureWidth, textureHeight;

	SDL_QueryTexture(m_textureMap[id], NULL, NULL, &textureWidth, &textureHeight);

	srcRect.x = textureWidth * currentFrame;
	srcRect.y = textureHeight * currentRow;
	srcRect.w = destRect.w = textureWidth;
	srcRect.h = destRect.h = textureHeight;

	if (centered) {
		int xOffset = textureWidth * 0.5;
		int yOffset = textureHeight * 0.5;
		destRect.x = x - xOffset;
		destRect.y = y - yOffset;
	}
	else {
		destRect.x = x;
		destRect.y = y;
	}

	SDL_SetTextureAlphaMod(m_textureMap[id], alpha);
	SDL_RenderCopyEx(pRenderer, m_textureMap[id], &srcRect, &destRect, angle, 0, flip);
}

//glm::vec2 TextureManager::getTextureSize(std::string id)
//{
//	int width, height;
//	SDL_QueryTexture(m_textureMap[id], NULL, NULL, &width, &height);
//	glm::vec2 size;
//
//	size.x = width;
//	size.y = height;
//
//	return size;
//}

void TextureManager::setAlpha(std::string id, Uint8 newAlpha)
{
	SDL_Texture* pTexture = m_textureMap[id];
	SDL_SetTextureAlphaMod(pTexture, newAlpha);
}

void TextureManager::setColour(std::string id, Uint8 red, Uint8 green, Uint8 blue)
{
	SDL_Texture* pTexture = m_textureMap[id];
	SDL_SetTextureColorMod(pTexture, red, green, blue);
}