#pragma once
#include "SDL.h"

namespace jam::demo
{
	class RenderComponent final
	{
	public:
		SDL_Texture* texture = nullptr;
		SDL_Texture* sideTexture = nullptr;

		float height = .2;

		int32_t xScale = 1;
		int32_t yScale = 1;
		float degrees = 0;

		int32_t xOffset = 0;
		int32_t yOffset = 0;

		int32_t index = 0;
		int32_t count = 1;

		bool xCenter = true;
		bool yCenter = true;
		SDL_RendererFlip flip = SDL_FLIP_NONE;
	};
}
