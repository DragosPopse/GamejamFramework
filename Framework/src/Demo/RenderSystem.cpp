#include "Demo/ComponentSystems/RenderSystem.h"
#include "SDL.h"
#include "Gamejam/Core/App.hpp"
#include "cECSar/ECSystemManager.h"
#include "Demo/Components/RenderComponent.h"
#include "Demo/Components/TransformComponent.h"
#include "Demo/Modules/RenderModule.h"
#include <stdlib.h>
#include <stdlib.h>

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
	const int32_t xCameraOffset = module.xCameraOffset;
	const int32_t yCameraOffset = module.yCameraOffset;

	// Iterate over all the renderers to render them on the screen.
	const int32_t count = renderers.GetCount();
	for (int32_t i = 0; i < count; ++i)
	{
		const int32_t index = renderers.dense[i];
		auto& renderer = renderers.instances[index];
		auto& transform = transforms.instances[index];
		auto& texture = renderer.texture;

		int32_t w, h;
		SDL_QueryTexture(texture, nullptr, nullptr, &w, &h);

		int32_t x = transform.xPosGlobal + renderer.xOffset - xCameraOffset;
		int32_t y = transform.yPosGlobal + renderer.yOffset - yCameraOffset;

		const float xScaledModifier = renderer.xScale + transform.xScaleGlobal - 1;
		const float yScaledModifier = renderer.yScale + transform.yScaleGlobal - 1 ;

		const float size = w / renderer.count;

		const float xSize = size * xScaledModifier;
		const float ySize = h * yScaledModifier;

		const float wHalf = xSize / 2;
		const float hHalf = ySize / 2;

		if (renderer.xCenter)
			x -= wHalf;
		if (renderer.yCenter)
			y -= hHalf;

		if (x + wHalf < 0 || y + hHalf < 0)
			continue;
		if (x - wHalf > screenWidth || y - hHalf > screenHeight)
			continue;

		SDL_Rect srcRect;
		srcRect.x = size * renderer.index;
		srcRect.y = 0;
		srcRect.w = size;
		srcRect.h = h;

		SDL_Rect dstRect;
		dstRect.w = xSize;
		dstRect.h = ySize;
		dstRect.x = x;
		dstRect.y = y;

		const float degrees = renderer.degrees + transform.degreesGlobal;
		SDL_RenderCopyEx(screen, texture, &srcRect, &dstRect,
			degrees, nullptr, renderer.flip);
	}
}
