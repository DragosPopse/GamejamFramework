#include "Demo/ComponentSystems/RenderSystem.h"
#include "SDL.h"
#include "Gamejam/Core/App.hpp"
#include "cECSar/ECSystemManager.h"
#include "Demo/Components/RenderComponent.h"
#include "Demo/Components/TransformComponent.h"
#include "Demo/Modules/RenderModule.h"

void jam::demo::RenderSystem::Update(cecsar::ECSystemManager& systemManager)
{
	// Get the screen to render on.
	SDL_Renderer* screen = App::Get().m_renderer;
	App& app = App::Get();

	// Get the required components.
	auto& renderers = systemManager.GetSet<RenderComponent>();
	auto& transforms = systemManager.GetSet<TransformComponent>();

	const int32_t screenWidth = app.m_width, screenHeight = app.m_height;

	RenderModule& module = systemManager.GetModule<RenderModule>();
	const int32_t xCameraOffset = module.m_xCameraOffset;
	const int32_t yCameraOffset = module.m_yCameraOffset;

	// Iterate over all the renderers to render them on the screen.
	const int32_t count = renderers.GetCount();
	for (int32_t i = 0; i < count; ++i)
	{
		const int32_t index = renderers.m_dense[i];
		auto& renderer = renderers.m_instances[index];
		auto& transform = transforms.m_instances[index];
		auto& texture = renderer.m_texture;

		int32_t w, h;
		SDL_QueryTexture(texture, nullptr, nullptr, &w, &h);

		int32_t x = transform.m_x + renderer.m_xOffset - xCameraOffset;
		int32_t y = transform.m_y + renderer.m_yOffset - yCameraOffset;

		const float xScaledModifier = renderer.m_xScale + transform.m_xScale - 1;
		const float yScaledModifier = renderer.m_yScale + transform.m_yScale - 1;

		const float size = w / renderer.m_count;

		const float xSize = size * xScaledModifier;
		const float ySize = h * yScaledModifier;

		const float wHalf = xSize / 2;
		const float hHalf = ySize / 2;

		if (renderer.m_xCenter)
			x -= wHalf;
		if (renderer.m_yCenter)
			y -= hHalf;

		if (x + wHalf < 0 || y + hHalf < 0)
			continue;
		if (x - wHalf > screenWidth || y - hHalf > screenHeight)
			continue;

		SDL_Rect srcRect;
		srcRect.x = size * renderer.m_index;
		srcRect.y = 0;
		srcRect.w = size;
		srcRect.h = h;

		SDL_Rect dstRect;
		dstRect.w = xSize;
		dstRect.h = ySize;
		dstRect.x = x;
		dstRect.y = y;

		const float degrees = renderer.m_degrees + transform.m_degrees;
		SDL_RenderCopyEx(screen, texture, &srcRect, &dstRect,
			degrees, nullptr, renderer.flip);
	}
}
