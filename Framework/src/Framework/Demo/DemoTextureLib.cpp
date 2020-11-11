#include "Gamejam/Demo/DemoTextureLib.h"
#include <SDL_image.h>
#include <Gamejam/Core/App.hpp>

jam::demo::DemoTextureLib& jam::demo::DemoTextureLib::Get()
{
	// Singleton pattern.
	static DemoTextureLib* lib = nullptr;
	if (lib == nullptr)
		lib = new DemoTextureLib();
	return *lib;
}

SDL_Texture* jam::demo::DemoTextureLib::GetTexture(const std::string key)
{
	// If map contains key, return value. Otherwise load texture and return that.

	const auto found = m_textureMap.find(key);
	if (found != m_textureMap.end())
		return found->second;

	SDL_Surface* surface = IMG_Load(key.c_str());
	SDL_Renderer* renderer = App::Get().m_renderer;
	SDL_Texture* texture = SDL_CreateTextureFromSurface(renderer, surface);

	SDL_FreeSurface(surface);
	return texture;
}

void jam::demo::DemoTextureLib::Clear()
{
	// Useful when unloading a level.

	for (const auto& texture : m_textureMap)
		SDL_DestroyTexture(texture.second);
}
