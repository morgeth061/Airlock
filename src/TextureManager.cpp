/*
 * Texture Manager class
 * Adapted from GBC GAME3001 SDL Template
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

inline bool TextureManager::m_exists(const std::string& id)
{
	return m_textureMap.find(id) != m_textureMap.end();
}

bool TextureManager::load(const std::string& file_name, const std::string& id, SDL_Renderer* renderer)
{
	if (m_exists(id))
	{
		return true;
	}

	const auto pTempSurface(Config::make_resource(IMG_Load(file_name.c_str())));


	if (pTempSurface == nullptr)
	{
		return false;
	}

	const auto pTexture(Config::make_resource(SDL_CreateTextureFromSurface(renderer, pTempSurface.get())));

	// everything went ok, add the texture to our list
	if (pTexture != nullptr)
	{
		m_textureMap[id] = pTexture;
		return true;
	}

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
	SDL_RenderCopyEx(pRenderer, m_textureMap[id].get(), &srcRect, &destRect, 0, 0, flip);
}

void TextureManager::draw(std::string id, int x, int y, SDL_Renderer* pRenderer, bool centered, SDL_RendererFlip flip)
{
	SDL_Rect srcRect;
	SDL_Rect destRect;

	srcRect.x = 0;
	srcRect.y = 0;

	int textureWidth, textureHeight;

	SDL_QueryTexture(m_textureMap[id].get(), NULL, NULL, &textureWidth, &textureHeight);

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

	SDL_RenderCopyEx(pRenderer, m_textureMap[id].get(), &srcRect, &destRect, 0, 0, flip);
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

	SDL_SetTextureAlphaMod(m_textureMap[id].get(), alpha);
	SDL_RenderCopyEx(pRenderer, m_textureMap[id].get(), &srcRect, &destRect, angle, 0, flip);
}

void TextureManager::draw(std::string id, int x, int y, SDL_Renderer* pRenderer, double angle, int alpha, bool centered, SDL_RendererFlip flip)
{
	SDL_Rect srcRect;
	SDL_Rect destRect;

	srcRect.x = 0;
	srcRect.y = 0;

	int textureWidth, textureHeight;

	SDL_QueryTexture(m_textureMap[id].get(), NULL, NULL, &textureWidth, &textureHeight);

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

	SDL_SetTextureAlphaMod(m_textureMap[id].get(), alpha);
	SDL_RenderCopyEx(pRenderer, m_textureMap[id].get(), &srcRect, &destRect, angle, 0, flip);
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
	SDL_RenderCopyEx(pRenderer, m_textureMap[id].get(), &srcRect, &destRect, 0, 0, flip);
}

void TextureManager::drawFrame(std::string id, int x, int y, int currentRow, int currentFrame, SDL_Renderer* pRenderer, bool centered, SDL_RendererFlip flip)
{
	SDL_Rect srcRect;
	SDL_Rect destRect;

	int textureWidth, textureHeight;

	SDL_QueryTexture(m_textureMap[id].get(), NULL, NULL, &textureWidth, &textureHeight);

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

	SDL_RenderCopyEx(pRenderer, m_textureMap[id].get(), &srcRect, &destRect, 0, 0, flip);
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

	SDL_SetTextureAlphaMod(m_textureMap[id].get(), alpha);
	SDL_RenderCopyEx(pRenderer, m_textureMap[id].get(), &srcRect, &destRect, angle, 0, flip);
}

void TextureManager::drawFrame(std::string id, int x, int y, int currentRow, int currentFrame, SDL_Renderer* pRenderer, double angle, int alpha, bool centered, SDL_RendererFlip flip)
{
	SDL_Rect srcRect;
	SDL_Rect destRect;

	int textureWidth, textureHeight;

	SDL_QueryTexture(m_textureMap[id].get(), NULL, NULL, &textureWidth, &textureHeight);

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

	SDL_SetTextureAlphaMod(m_textureMap[id].get(), alpha);
	SDL_RenderCopyEx(pRenderer, m_textureMap[id].get(), &srcRect, &destRect, angle, 0, flip);
}

void TextureManager::drawText(const std::string& id, const int x, const int y, SDL_Renderer* renderer, const double angle, const int alpha, const bool centered, const SDL_RendererFlip flip)
{
	SDL_Rect srcRect;
	SDL_Rect destRect;

	srcRect.x = 0;
	srcRect.y = 0;

	int textureWidth, textureHeight;

	SDL_QueryTexture(m_textureMap[id].get(), nullptr, nullptr, &textureWidth, &textureHeight);

	srcRect.w = destRect.w = textureWidth;
	srcRect.h = destRect.h = textureHeight;

	if (centered) {
		const int xOffset = textureWidth * 0.5;
		const int yOffset = textureHeight * 0.5;
		destRect.x = x - xOffset;
		destRect.y = y - yOffset;
	}
	else {
		destRect.x = x;
		destRect.y = y;
	}

	SDL_SetTextureAlphaMod(m_textureMap[id].get(), alpha);
	SDL_RenderCopyEx(renderer, m_textureMap[id].get(), &srcRect, &destRect, angle, nullptr, flip);
}

glm::vec2 TextureManager::getTextureSize(std::string id)
{
	int width, height;
	SDL_QueryTexture(m_textureMap[id].get(), NULL, NULL, &width, &height);
	glm::vec2 size;

	size.x = width;
	size.y = height;

	return size;
}

bool TextureManager::addTexture(const std::string& id, std::shared_ptr<SDL_Texture> texture)
{
	if (m_exists(id))
	{
		return true;
	}

	m_textureMap[id] = std::move(texture);

	return true;
}

SDL_Texture* TextureManager::getTexture(const std::string& id)
{
	return m_textureMap[id].get();
}

void TextureManager::setAlpha(std::string id, Uint8 newAlpha)
{
	SDL_Texture* pTexture = m_textureMap[id].get();
	SDL_SetTextureAlphaMod(pTexture, newAlpha);
}

void TextureManager::setColour(std::string id, Uint8 red, Uint8 green, Uint8 blue)
{
	SDL_Texture* pTexture = m_textureMap[id].get();
	SDL_SetTextureColorMod(pTexture, red, green, blue);
}