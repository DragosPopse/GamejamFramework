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

		const int32_t xSize = w / instance.count;
		const int32_t ySize = h;

		const int32_t wHalf = xSize / 2;
		const int32_t hHalf = ySize / 2;

		if (instance.xCenter)
			x -= wHalf;
		if (instance.yCenter)
			y -= hHalf;

		/*
		// Out of bounds check.
		const bool outOfBoundsLeft = x - wHalf < -DRAW_THRESHOLD;
		if (outOfBoundsLeft)
			continue;

		const bool outOfBoundsBottom = y - hHalf < -DRAW_THRESHOLD;
		if (outOfBoundsBottom)
			continue;

		const bool outOfBoundsRight = x + wHalf > screenWidth + DRAW_THRESHOLD;
		if (outOfBoundsRight)
			continue;

		const bool outOfBoundsTop = y + hHalf > screenHeight + DRAW_THRESHOLD;
		if (outOfBoundsTop)
			continue;
		*/

		SDL_Rect srcRect;
		srcRect.x = xSize * instance.index;
		srcRect.y = 0;
		srcRect.w = xSize;
		srcRect.h = h;

		const float xScaledModifier = instance.scale + transform.xScale - 2;
		const float yScaledModifier = instance.scale + transform.yScale - 2;

		SDL_Rect dstRect;
		dstRect.w = xSize * (1 + xScaledModifier);
		dstRect.h = ySize * (1 + yScaledModifier);
		dstRect.x = x - dstRect.w / 2;
		dstRect.y = y - dstRect.h / 2;

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