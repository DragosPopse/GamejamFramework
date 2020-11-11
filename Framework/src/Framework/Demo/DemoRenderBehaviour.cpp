#include <Gamejam\Core\App.hpp>
#include <Gamejam\Demo\DemoTransformComponent.h>
#include "SDL.h"
#include "Gamejam/Demo/DemoRenderBehaviour.h"

jam::demo::DemoRenderBehaviour::DemoRenderBehaviour(jecs::SystemManager& manager) :
	ISystemBehaviour<DemoRenderComponent>(manager)
{
}

void jam::demo::DemoRenderBehaviour::Update()
{
	/*
	This is a very simple version of a rendererbehaviour.
	The Example in JECS contains a slightly more complex renderer that can also
	do the basics like rotating, scaling, mirroring, multiple frames and whatever.
	*/

	// Get the screen to render on.
	SDL_Renderer* screen = App::Get().m_renderer;

	// Get the required components.
	auto& renderers = GetSet<DemoRenderComponent>();
	auto& transforms = GetSet<DemoTransformComponent>();

	// Iterate over all the renderers to render them on the screen.
	const int32_t count = renderers.GetCount();
	for (int32_t i = 0; i < count; ++i)
	{
		const int32_t index = renderers.dense[i];
		const DemoRenderComponent renderer = *renderers[i];
		const DemoTransformComponent transform = transforms.instances[index];

		// Get width and height.
		int32_t w, h;
		SDL_QueryTexture(renderer.texture, nullptr, nullptr, &w, &h);

		SDL_Rect srcRect;
		srcRect.x = 0;
		srcRect.y = 0;
		srcRect.w = w;
		srcRect.h = h;

		SDL_Rect dstRect;
		dstRect.x = transform.x;
		dstRect.y = transform.y;
		dstRect.w = w;
		dstRect.h = h;

		// Draw the renderer on the screen.
		SDL_RenderCopy(screen, renderer.texture, &srcRect, &dstRect);
	}
}
