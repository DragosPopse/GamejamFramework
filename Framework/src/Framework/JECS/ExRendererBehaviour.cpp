#include "ExRendererBehaviour.h"
#include "ExRendererModule.h"

DJ::JECS::Examples::ExRendererBehaviour::ExRendererBehaviour(
	SystemManager& manager, ExRendererModule& module) : 
	ISystemBehaviour<ExRenderer>(manager), _renderModule(module)
{

}

void DJ::JECS::Examples::ExRendererBehaviour::Update(Renderers renderers, Transforms transforms) const
{
	auto& renderer = _renderModule.GetRenderer();
	const int32_t screenWidth = _renderModule.WIDTH, screenHeight = _renderModule.HEIGHT;
	const int32_t DRAW_THRESHOLD = 64;

	const int32_t count = renderers.GetCount();
	for (int32_t i = 0; i < count; ++i)
	{
		auto& instance = *renderers[i];
		const int32_t index = renderers.dense[i];
		auto& transform = transforms.instances[index];
		auto& texture = instance.texture;

		int32_t w, h;
		SDL_QueryTexture(texture, nullptr, nullptr, &w, &h);

		int32_t x = transform.x + instance.xOffset;
		int32_t y = transform.y + instance.yOffset;

		const int32_t xSize = w / instance.count;
		const int32_t ySize = h / instance.count;

		const int32_t wHalf = xSize / 2;
		const int32_t hHalf = ySize / 2;

		if (instance.xCenter)
			x -= wHalf;
		if (instance.yCenter)
			y -= hHalf;

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

		SDL_Rect srcRect;
		srcRect.x = xSize * instance.index;
		srcRect.y = 0;
		srcRect.w = xSize;
		srcRect.h = h;

		const float scaledModifier = instance.scale - 1;
		const float xScaledOffset = scaledModifier * wHalf;
		const float yScaledOffset = scaledModifier * hHalf;

		SDL_Rect dstRect;
		dstRect.x = x - xScaledOffset / 2;
		dstRect.y = y - yScaledOffset / 2;
		dstRect.w = w + xScaledOffset;
		dstRect.h = h + yScaledOffset;

		SDL_RenderCopyEx(&renderer, texture, &srcRect, &dstRect,
			instance.angle, nullptr, instance.flip);
	}
}