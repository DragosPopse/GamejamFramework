#include <Gamejam\Core\App.hpp>
#include "SDL.h"
#include "Gamejam/Demo/Behaviours/DemoRenderBehaviour.h"
#include "Gamejam/Demo/Components/DemoTransformComponent.h"
#include "Gamejam/Demo/Components/DemoRenderComponent.h"

jam::demo::DemoRenderBehaviour::DemoRenderBehaviour(jecs::SystemManager& manager) :
	ISystemBehaviour<DemoRenderComponent>(manager)
{
	SDL_Renderer* screen = App::Get().m_renderer;
	App& app = App::Get();

	m_texture = SDL_CreateTexture(screen, SDL_PIXELFORMAT_RGBA8888,
		SDL_TEXTUREACCESS_TARGET, app.m_width, app.m_height);
}

jam::demo::DemoRenderBehaviour::~DemoRenderBehaviour()
{
	SDL_Renderer* screen = App::Get().m_renderer;
	SDL_SetRenderTarget(screen, nullptr);
	SDL_DestroyTexture(m_texture);
}

void jam::demo::DemoRenderBehaviour::Update()
{
	//PreRender();

	/*
	This is a very simple version of a rendererbehaviour.
	The Example in JECS contains a slightly more complex renderer that can also
	do the basics like rotating, scaling, mirroring, multiple frames and whatever.
	*/

	// Get the screen to render on.
	SDL_Renderer* screen = App::Get().m_renderer;
	App& app = App::Get();

	// Get the required components.
	auto& renderers = GetSet<DemoRenderComponent>();
	auto& transforms = GetSet<DemoTransformComponent>();

	const int32_t screenWidth = app.m_width, screenHeight =  app.m_height;
	const int32_t DRAW_THRESHOLD = 64;

	// Iterate over all the renderers to render them on the screen.
	const int32_t count = renderers.GetCount();
	for (int32_t i = 0; i < count; ++i)
	{
		auto& instance = *renderers[i];
		const int32_t index = renderers.dense[i];
		auto& transform = transforms.instances[index];
		auto& texture = instance.texture;

		int32_t w, h;
		SDL_QueryTexture(texture, nullptr, nullptr, &w, &h);

		int32_t x = transform.x + instance.xOffset - xOffset;
		int32_t y = transform.y + instance.yOffset - yOffset;

		const float xScaledModifier = instance.scale + transform.xScale - 1;
		const float yScaledModifier = instance.scale + transform.yScale - 1;

		const float size = w / instance.count;

		const float xSize = size * xScaledModifier;
		const float ySize = h * yScaledModifier;

		const float wHalf = xSize / 2;
		const float hHalf = ySize / 2;

		if (instance.xCenter)
			x -= wHalf;
		if (instance.yCenter)
			y -= hHalf;

		SDL_Rect srcRect;
		srcRect.x = size * instance.index;
		srcRect.y = 0;
		srcRect.w = size;
		srcRect.h = h;

		SDL_Rect dstRect;
		dstRect.w = xSize;
		dstRect.h = ySize;
		dstRect.x = x;
		dstRect.y = y;

		SDL_RenderCopyEx(screen, texture, &srcRect, &dstRect,
			instance.degrees + transform.degrees, nullptr, instance.flip);
	}

	//PostRender();
}

void jam::demo::DemoRenderBehaviour::PreRender() const
{
	SDL_Renderer* screen = App::Get().m_renderer;

	int32_t color = 0xFF;
	SDL_SetRenderDrawColor(screen, color, color, color, color);
	SDL_SetRenderTarget(screen, m_texture);

	color = 0x22;
	SDL_SetRenderDrawColor(screen, color, color, color, color);
	SDL_RenderClear(screen);
}

void jam::demo::DemoRenderBehaviour::PostRender() const
{
	SDL_Renderer* screen = App::Get().m_renderer;
	App& app = App::Get();

	SDL_SetRenderTarget(screen, nullptr);

	SDL_Rect scaler;
	scaler.x = app.m_width * (1 - m_zoom) / 2;
	scaler.y = app.m_height * (1 - m_zoom) / 2;
	scaler.w = app.m_width * m_zoom;
	scaler.h = app.m_height * m_zoom;

	SDL_RenderCopyEx(screen, m_texture, nullptr, &scaler,
		m_angle, nullptr, SDL_FLIP_NONE);
}