#include "Demo/Modules/RenderModule.h"
#include "SDL_image.h"
#include "Gamejam/Core/App.hpp"

jam::demo::RenderModule::RenderModule()
{
	SDL_Renderer* screen = App::Get().m_renderer;
	App& app = App::Get();

	m_texture = SDL_CreateTexture(screen, SDL_PIXELFORMAT_RGBA8888,
		SDL_TEXTUREACCESS_TARGET, app.m_width, app.m_height);
}

jam::demo::RenderModule::~RenderModule()
{
	SDL_Renderer* screen = App::Get().m_renderer;
	const auto target = SDL_GetRenderTarget(screen);
	if(target == m_texture)
		SDL_SetRenderTarget(screen, nullptr);
	SDL_DestroyTexture(m_texture);
}

void jam::demo::RenderModule::PreRender() const
{
	SDL_Renderer* screen = App::Get().m_renderer;

	SDL_SetRenderDrawColor(screen, 
		colorForegroundClear, colorForegroundClear, colorForegroundClear, 0);
	SDL_SetRenderTarget(screen, m_texture);

	SDL_SetRenderDrawColor(screen, 
		colorBackgroundClear, colorBackgroundClear, colorBackgroundClear, 0);
	SDL_RenderClear(screen);
}

void jam::demo::RenderModule::PostRender() const
{
	SDL_Renderer* screen = App::Get().m_renderer;
	App& app = App::Get();

	SDL_SetRenderTarget(screen, nullptr);

	SDL_Rect scaler;
	scaler.x = xOffset + app.m_width * (1 - zoom) / 2;
	scaler.y = yOffset + app.m_height * (1 - zoom) / 2;
	scaler.w = app.m_width * zoom;
	scaler.h = app.m_height * zoom;

	SDL_RenderCopyEx(screen, m_texture, nullptr, &scaler,
		angle, nullptr, SDL_FLIP_NONE);
}

SDL_Texture* jam::demo::RenderModule::GetTexture(const std::string& path)
{
	const auto found = m_textureMap.find(path);
	if (found != m_textureMap.end())
		return found->second;

	SDL_Surface* surface = IMG_Load(path.c_str());
	SDL_Renderer* renderer = App::Get().m_renderer;
	SDL_Texture* texture = SDL_CreateTextureFromSurface(renderer, surface);

	SDL_FreeSurface(surface);
	return texture;
}

void jam::demo::RenderModule::Clear()
{
	for (const auto& texture : m_textureMap)
		SDL_DestroyTexture(texture.second);
	m_textureMap.clear();
}
