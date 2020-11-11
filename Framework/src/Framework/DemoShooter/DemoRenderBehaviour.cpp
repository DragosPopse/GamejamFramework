#include <Gamejam\Core\App.hpp>
#include <Gamejam\Demo\DemoTransformComponent.h>
#include "SDL.h"
#include "Gamejam/Demo/DemoRenderBehaviour.h"

jam::demo::DemoRenderBehaviour::DemoRenderBehaviour(jecs::SystemManager& manager) :
	ISystemBehaviour<DemoRenderComponent>(manager)
{
}

jam::demo::DemoRenderBehaviour::~DemoRenderBehaviour() = default;

void jam::demo::DemoRenderBehaviour::OnAddComponent(const int32_t index)
{
}

void jam::demo::DemoRenderBehaviour::OnRemoveComponent(const int32_t index)
{
}

void jam::demo::DemoRenderBehaviour::Update()
{
	SDL_Renderer* screen = App::Get().m_renderer;

	auto& renderers = GetSet<DemoRenderComponent>();
	auto& transforms = GetSet<DemoTransformComponent>();

	const int32_t count = renderers.GetCount();
	for (int32_t i = 0; i < count; ++i)
	{
		const int32_t index = renderers.dense[i];
		const DemoRenderComponent renderer = *renderers[i];
		const DemoTransformComponent transform = transforms.instances[i];

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

		SDL_RenderCopy(screen, renderer.texture, &srcRect, &dstRect);
	}
}
