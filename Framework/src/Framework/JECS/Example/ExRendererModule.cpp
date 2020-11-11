#include <SDL_image.h>
#include "Gamejam/JECS/Examples/ExRendererModule.h"

jam::jecs::Examples::ExRendererModule::ExRendererModule(int32_t w, int32_t h) :
	WIDTH(w), HEIGHT(h)
{
	const int32_t undef = SDL_WINDOWPOS_UNDEFINED;
	_window = SDL_CreateWindow("Main", undef, undef, w, h, SDL_WINDOW_SHOWN);
	const int32_t flags = SDL_RENDERER_ACCELERATED | SDL_RENDERER_PRESENTVSYNC;
	_renderer = SDL_CreateRenderer(_window, -1, flags);

	_texture = SDL_CreateTexture(_renderer, SDL_PIXELFORMAT_RGBA8888,
		SDL_TEXTUREACCESS_TARGET, WIDTH, HEIGHT);
}

void jam::jecs::Examples::ExRendererModule::PreRender() const
{
	int32_t color = 0xFF;
	SDL_SetRenderDrawColor(_renderer, color, color, color, color);

	SDL_RenderClear(_renderer);
	SDL_SetRenderTarget(_renderer, _texture);

	color = 0x22;
	SDL_SetRenderDrawColor(_renderer, color, color, color, color);
	SDL_RenderClear(_renderer);
}

void jam::jecs::Examples::ExRendererModule::PostRender() const
{
	SDL_SetRenderTarget(_renderer, nullptr);

	SDL_Rect scaler;
	scaler.x = WIDTH * (1 - zoom) / 2;
	scaler.y = HEIGHT * (1 - zoom) / 2;
	scaler.w = WIDTH * zoom;
	scaler.h = HEIGHT * zoom;

	SDL_RenderCopyEx(_renderer, _texture, nullptr, &scaler,
		angle, nullptr, SDL_FLIP_NONE);

	SDL_RenderPresent(_renderer);
}

SDL_Renderer& jam::jecs::Examples::ExRendererModule::GetRenderer() const
{
	return *_renderer;
}

SDL_Texture* jam::jecs::Examples::ExRendererModule::GetTexture(const std::string& key)
{
	const auto found = _textureMap.find(key);
	if (found != _textureMap.end())
		return found->second;
	return _textureMap[key] = &LoadTexture(key);
}

SDL_Texture& jam::jecs::Examples::ExRendererModule::LoadTexture(const std::string& path) const
{
	SDL_Surface* surface = IMG_Load(path.c_str());
	SDL_Texture* texture = SDL_CreateTextureFromSurface(_renderer, surface);
	SDL_FreeSurface(surface);
	return *texture;
}
